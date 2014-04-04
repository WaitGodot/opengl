#include "schedule.h"
#include "timer.h"
#include "MacroConfig.h"

using namespace std;

Schedule::Schedule()
{

}

Schedule::~Schedule()
{

}

void Schedule::schedule( float delay,ScheduleMethod method,void* param1 )
{
	strSchedule* ps = new strSchedule();
	ps->m_delay = delay;
	ps->m_pMethod = method;
	ps->m_param1 = param1;

	m_pSets.push_back( ps );
}

void Schedule::unSchedule( ScheduleMethod metod )
{
	// find all and remove all.
}

void Schedule::run()
{
	static timer t;
	float dt = t.elapsed() * 1000 ; // ms

	//LOG("run : %f",dt);

	strSchedule* p = NULL;
	for ( list<strSchedule*>::iterator it = m_pSets.begin();
		it != m_pSets.end() ; ++ it)
	{
		p = (*it);
		p->m_duration += dt;
		if ( p->m_duration > p->m_delay)
		{
			p->m_pMethod(p->m_param1,p->m_duration);
			p->m_duration = 0;
		}
	}
}

Schedule* Schedule::sharedSchedule()
{
	if (!sg_schedule)
	{
		sg_schedule = new Schedule();
	}
	return sg_schedule;
}

Schedule* Schedule::sg_schedule = NULL;

