#include "AVVideo.h"
#include "AVVideoDecode.h"
#include "MacroConfig.h"
#include "AVVideoSampler.h"

#include "texture/Texture.h"
#include "texture/Sprite.h"
#include "texture/Image.h"
#include "timer/schedule.h"

AVVideo::AVVideo():
m_fps(0),m_pDecode(0),m_isPlaying(false)
	,m_isStop(true),m_bit(0),m_width(0)
	,m_height(0),m_pVideoFrame(NULL)
{

}

AVVideo::~AVVideo()
{
	DELETE_SAFE(m_pDecode);
	DELETE_SAFE(m_pVideoFrame);
}

void AVVideo::play()
{
	if(!m_pVideoFrame->m_pTexture)
	{
		return ;
	}

	static Sprite* sg_sprite = new Sprite();

	sg_sprite->setTexture(m_pVideoFrame->m_pTexture);
	sg_sprite->draw();
}

void AVVideo::resume()
{

}

void AVVideo::stop()
{

}

void AVVideo::openSampler( AVVideoSampler* sampler )
{

	//INIT decode
	if (!m_pDecode)
	{
		m_pDecode = new AVVideoDecode();
	}
	if (!m_pVideoFrame)
	{
		m_pVideoFrame = new AVVideoFrame();
		m_pVideoFrame->m_pFrame = NULL;
		m_pVideoFrame->m_pTexture = NULL;
	}

	AVFormatContext *pFormatCtx = NULL;
	if( avformat_open_input(&pFormatCtx, sampler->_fileName.c_str(), NULL, NULL) != 0 )
		return ;
	if( avformat_find_stream_info(pFormatCtx, NULL ) < 0 )
		return ;

	av_dump_format(pFormatCtx, -1, sampler->_fileName.c_str(), 0);
	int videoStream = -1;
	for( int i = 0; i < pFormatCtx->nb_streams; i++ )
	{
		if( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
		if( videoStream == -1 )
			return ;
	}
	AVCodecContext* pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	
	m_fps = pCodecCtx->time_base.den / pCodecCtx->time_base.num;
	m_bit = pCodecCtx->bit_rate  ;
	m_width = pCodecCtx->width;
	m_height = pCodecCtx->height;

	sgSchedule()->schedule(1/(float)m_fps*1000,AVVideo::scheduleVido,this);

	m_pDecode->decode(sampler);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	
}

void AVVideo::scheduleVido( void* self,float dt )
{
	AVVideo* pAV = (AVVideo*)self;
	// to 
	AVFrame* frame = pAV->m_pDecode->getFrontAVFrame();
	if(!frame){
		return;
	}

	pAV->m_pVideoFrame->setNewAVFrame(frame);
}


Texture* saveToTexture(AVFrame *pFrame, int width, int height)
{
	return Texture::create(Image::createWithRGBData(pFrame->data[0],width,height));
}

static void free_AVVFrame(AVFrame* frame)
{
	if (frame->data)
	{
		for (int i = 0 ; i < AV_NUM_DATA_POINTERS ; i++)
		{
			if (frame->data[i])
			{
				av_free(frame->data[i]);
				frame->data[i] = NULL;
			}
		}
	}
	av_frame_free(&frame);
}

void AVVideo::AVVideoFrame::setNewAVFrame( AVFrame* frame )
{
	if (frame == m_pFrame)
	{
		return ;
	}

	if (m_pFrame)
	{
		free_AVVFrame(m_pFrame);
	}
	m_pFrame = frame;
	DELETE_SAFE(m_pTexture);

	m_pTexture = saveToTexture(m_pFrame,m_pFrame->width,m_pFrame->height);
	
}
