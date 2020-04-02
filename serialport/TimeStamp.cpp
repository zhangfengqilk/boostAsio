#include "TimeStamp.h"
using namespace  boost::posix_time;
using namespace boost::gregorian;
Lock TimeStamp::lock;
TimeStamp *TimeStamp::instance = nullptr;
TimeStamp* TimeStamp::Get() 
{
	if (instance == nullptr)
	{
		lock.lock();
		if(instance == nullptr)
		{
			instance = new TimeStamp();
		}
	}
	return instance;
}
TimeStamp::TimeStamp()
{
	this->epoch = boost::shared_ptr<ptime>(new ptime(date(2015,boost::gregorian::Jan,1)));
}
TimeStamp::~TimeStamp()
{
	
}
timeStamp TimeStamp::GetTimeStamp()
{
	time_duration timeFromEpoch = microsec_clock::local_time()-*(this->epoch);
	return timeFromEpoch.total_milliseconds();
}
void TimeStamp::SetBeingTime(date pBeginTime)
{
	this->epoch = boost::shared_ptr<ptime>(new ptime(pBeginTime));
}
