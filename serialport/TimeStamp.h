#ifndef _H_TIMESTAMP
#define _H_TIMESTAMP
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/shared_ptr.hpp"
using namespace  boost::posix_time;
using namespace boost::gregorian;
typedef unsigned long timeStamp;
typedef boost::mutex Lock;
class TimeStamp
{
public:
	~TimeStamp();
	static TimeStamp* Get();
	timeStamp GetTimeStamp();
	void SetBeingTime(date pBeginTime);
private:

	boost::shared_ptr<ptime> epoch;
	TimeStamp();
	
	class GC
	{
		~GC()
		{
			if(TimeStamp::instance)
			{
				delete TimeStamp::instance;
			}
		}
	};
	static Lock lock;
	static GC gc;
	static TimeStamp* instance;
};
#endif