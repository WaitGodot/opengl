#ifndef _DECODE_THREAD_H
#define _DECODE_THREAD_H


class DecodeThread
{
public:

	void startThread();
	static void* threadRun(void * p);
};

class DecodeSteam
{
public:
	DecodeSteam();
	~DecodeSteam();

	class DMAVSteam
	{
	public:
		void* data;
		unsigned long lenght;

	};
	int decode();

private:
	DecodeThread* m_pDecodeThread;
};



#endif