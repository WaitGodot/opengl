#include "AVVideoDecode.h"
#include "pthread.h"
#include "semaphore.h"
#include "MacroConfig.h"
#include "AVVideoSampler.h"
#include "sched.h"

using namespace std;

AVVideoDecode::AVVideoDecode(AVCodecID  codeId):
m_avCodecId(codeId),m_pCodec(NULL),m_pCodeContext(NULL),
	m_threadRunning(false),m_pDecodeThread(NULL)
{
	//init av 
	av_register_all();
}

AVVideoDecode::~AVVideoDecode()
{
	if (m_pCodeContext)
	{
		avcodec_close(m_pCodeContext);
		av_free(m_pCodeContext);
	}
	DELETE_SAFE(m_pDecodeThread);
}

static pthread_t sgDecodeThread;
static pthread_mutex_t sgDecodeMutex;
static pthread_mutex_t sgFrameMutex;
static sem_t sgDecodeSem;

void AVVideoDecode::decode( AVVideoSampler* sampler )
{
	do 
	{
		BREAK_IF(!sampler);
		//start thread.
		if (!m_threadRunning)
		{
			//init
			pthread_mutex_init(&sgDecodeMutex,NULL);
			pthread_mutex_init(&sgFrameMutex,NULL);
			int rt = sem_init(&sgDecodeSem,0,0);
			BREAK_IF(rt<0);
			rt = pthread_create(&sgDecodeThread,NULL,AVVideoDecode::decodeProcess,this);
			BREAK_IF(rt<0);
			m_threadRunning = true;
			m_pDecodeThread = new DecodeThread(this);
		}

		pthread_mutex_lock(&sgDecodeMutex);
		m_samplerQueue.push(sampler);
		pthread_mutex_unlock(&sgDecodeMutex);
		sem_post(&sgDecodeSem);

	} while (0);
}

void* AVVideoDecode::decodeProcess( void* pa )
{
	AVVideoDecode* pDecode = (AVVideoDecode*)pa;
	AVVideoSampler* sampler;
	while(1)
	{
		int rt = sem_wait(&sgDecodeSem);
		//BREAK_IF(rt<0);
		
		pthread_mutex_lock(&sgDecodeMutex);// get async struct from queue
		if (pDecode->m_samplerQueue.empty())
		{
			pthread_mutex_unlock(&sgDecodeMutex);
			sched_yield();
			continue;
		}
		else
		{
			sampler = pDecode->m_samplerQueue.front();
			pDecode->m_samplerQueue.pop();
			pthread_mutex_unlock(&sgDecodeMutex);
		}   

		pDecode->m_pDecodeThread->decodeSampler(sampler);
	}


	return NULL;
}

AVFrame* AVVideoDecode::getFrontAVFrame()
{
	AVFrame* rt = NULL;
	pthread_mutex_lock(&sgFrameMutex);
	if ( m_outputFrame.empty())
	{
		pthread_mutex_unlock(&sgFrameMutex);
		return rt;
	}
	
	rt = m_outputFrame.front();
	m_outputFrame.pop();
	pthread_mutex_unlock(&sgFrameMutex);

	LOG("output frame size %d",m_outputFrame.size());
	return rt;
}

int AVVideoDecode::DecodeThread::decodeSampler( AVVideoSampler* sampler )
{
	AVFormatContext *pFormatCtx = NULL;
	int             i, videoStream;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame         *pFrame;
	AVFrame         *pFrameRGB;
	AVPacket        packet;
	int             frameFinished;
	int             numBytes;
	uint8_t         *buffer;

	queue<AVFrame* >* m_outputFrame = &m_pDecode->m_outputFrame;

	if( avformat_open_input(&pFormatCtx, sampler->_fileName.c_str(), NULL, NULL) != 0 )
		return -1;

	if( avformat_find_stream_info(pFormatCtx, NULL ) < 0 )
		return -1;

	av_dump_format(pFormatCtx, -1, sampler->_fileName.c_str(), 0);
	videoStream = -1;
	for( i = 0; i < pFormatCtx->nb_streams; i++ )
		if( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
		if( videoStream == -1 )
			return -1;

		pCodecCtx = pFormatCtx->streams[videoStream]->codec;

		pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
		if( pCodec == NULL )
			return -1;

		if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 )
			return -1;

		numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
			pCodecCtx->height);

		
		pFrame = avcodec_alloc_frame();
		if( pFrame == NULL )
			return -1;
		//thread.
		while(1 ) 
		{
			
			if (m_threadSleeping)
			{
				if (m_outputFrame->size() <= OUTPUT_QUEUE_FRAME_SIZE /2){
					m_threadSleeping = false;
				}
				//SLEEP.
				sched_yield();
				continue;
			}

			if (av_read_frame(pFormatCtx, &packet) < 0)
			{
				break;
			}

			if( packet.stream_index == videoStream )
			{
				avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
				//LOG("pts : %ld",packet.pts);
				if( frameFinished )
				{
					//LOG("width : %d,height : %d",pFrame->width,pFrame->height);
					static struct SwsContext *img_convert_ctx = 
						sws_getContext( pCodecCtx->width,
						pCodecCtx->height, pCodecCtx->pix_fmt,
						pCodecCtx->width, pCodecCtx->height,
						PIX_FMT_RGB24, SWS_BICUBIC,
						NULL, NULL, NULL);
					if( !img_convert_ctx ) {
						LOG_ERROR("Cannot initialize sws conversion context!!");
						exit(1);
					}
					pFrameRGB = avcodec_alloc_frame();
					if( pFrameRGB == NULL )
						return -1;

					buffer = (uint8_t*)av_malloc(numBytes);
					if (buffer == NULL)
					{
						continue;
					}

					avpicture_fill( (AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,pCodecCtx->width, pCodecCtx->height);
					int rt = sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data,
						pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
						pFrameRGB->linesize);

					pFrameRGB->width = pFrame->width;
					pFrameRGB->height = pFrame->height;
					pFrameRGB->key_frame = pFrame->key_frame;
					pFrameRGB->pts = pFrame->pts;
					pFrameRGB->pict_type = pFrame->pict_type;
					pFrameRGB->format = pFrame->format = pCodecCtx->pix_fmt;


					pthread_mutex_lock(&sgFrameMutex);
					m_outputFrame->push(pFrameRGB);
					pthread_mutex_unlock(&sgFrameMutex);

					if (m_outputFrame->size() > OUTPUT_QUEUE_FRAME_SIZE)
					{
						m_threadSleeping = true;
					}
				}
			}

		}
		av_free_packet(&packet);
		//av_free(buffer);
		av_free(pFrameRGB);
		av_free(pFrame);
		avcodec_close(pCodecCtx);
		avformat_close_input(&pFormatCtx);

		return 0;
}

AVVideoDecode::DecodeThread::DecodeThread( AVVideoDecode* pdecode ):
m_threadSleeping(false),m_pDecode(pdecode)
{

}

AVVideoDecode::DecodeThread::~DecodeThread()
{

}

void AVVideoDecode::DecodeThread::threadProc( void* pa )
{

}
