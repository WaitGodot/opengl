#ifndef _AV_VIDEO_H
#define _AV_VIDEO_H




class AVVideoDecode;
class AVVideoSampler;
class AVFrame;
class Texture;

class AVVideo 
{

public:

	AVVideo();
	~AVVideo();


	void play();
	void resume();
	void stop();

	void openSampler(AVVideoSampler* sampler);
private:
	int m_fps;
	int m_bit;
	int m_width;
	int m_height;

	AVVideoDecode* m_pDecode;
	bool m_isPlaying;
	bool m_isStop;

	static void scheduleVido(void* self,float dt);

	class AVVideoFrame
	{
	public:
		AVFrame* m_pFrame;
		Texture* m_pTexture;

		void setNewAVFrame(AVFrame* frame);
	};

	AVVideoFrame* m_pVideoFrame;
};



#endif