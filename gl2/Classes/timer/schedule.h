#ifndef _SCHEDULE_H
#define _SCHEDULE_H



#include <list>
typedef void (*ScheduleMethod)(void* param1,float dt);

class Schedule
{
public:
	Schedule();
	~Schedule();

	void schedule(float delay,ScheduleMethod method,void* param1);
	void unSchedule(ScheduleMethod metod);

	//////////////////////////////////////////////////////////////////////////
	void run();

	static Schedule* sharedSchedule();
private:

	class strSchedule
	{
	public:
		ScheduleMethod m_pMethod;
		float m_delay;// ms
		float m_duration;//ms

		void* m_param1;

		strSchedule():
		m_pMethod(NULL),m_delay(0),m_duration(0)
		{

		}
	};


	std::list<strSchedule*> m_pSets;

	static Schedule* sg_schedule;
};

#define sgSchedule() Schedule::sharedSchedule()

#endif