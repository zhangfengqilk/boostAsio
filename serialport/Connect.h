#ifndef _H_CONNECT_
#define _H_CONNECT_
#include <iostream>
#include "boost/asio.hpp"
#include "Global.h"
using namespace std;

class ISink
{
public:
    virtual void OnNotified(string s) = 0;
};

class Connect
{
public:
	Connect(void);
	virtual ~Connect(void);
	void SetTimeOutTime(unsigned int pms);
	void SetLastTime(timeStamp pTime);
    void SetSink(ISink* psink);
	virtual void mStartConnect();
	virtual void mStopConnect();
	virtual void mStartMoniter();
	virtual void mStopMoniter();
	virtual bool mIsCorrect();
	
protected:
	boost::thread *m_Thread;
	boost::thread *m_MoniterThread;
    ISink* m_pSink;
private:
	RWmutex m_lock;
	unsigned int timeOut;
	timeStamp lastTime;
	RWmutex rwLastTime;
	virtual void ProThread()=0;
    void ProMoniterThread();

};
#endif
