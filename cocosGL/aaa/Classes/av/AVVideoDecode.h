#ifndef _AV_VIDEO_DECODE_H
#define _AV_VIDEO_DECODE_H

#include <queue>


extern "C"{
#define __STDC_CONSTANT_MACROS
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/mem.h>
}


class AVVideoSampler;

#define OUTPUT_QUEUE_FRAME_SIZE 1024

class AVVideoDecode
{
public:
	
	AVVideoDecode(AVCodecID  codeId = AV_CODEC_ID_NONE);
	~AVVideoDecode();

	void decode(AVVideoSampler* sampler);

	AVFrame* getFrontAVFrame();
	//std::queue<>
private:

	std::queue< AVFrame* > m_outputFrame;
	std::queue< AVVideoSampler* > m_samplerQueue;

	AVCodecID m_avCodecId;
	AVCodec * m_pCodec;
	AVCodecContext* m_pCodeContext;

	//thread part
	bool m_threadRunning;
	static void* decodeProcess(void* pa);

	class DecodeThread
	{

		AVVideoDecode* m_pDecode;
		bool m_threadSleeping;
	public:
		DecodeThread(AVVideoDecode* pdecode);
		~DecodeThread();

		static void threadProc(void* pa);
		int decodeSampler(AVVideoSampler* sampler);
	};
	
	DecodeThread* m_pDecodeThread;
};







#endif