#include "Connect.h"

Connect::Connect(void)
{
	m_Thread = nullptr;
	m_MoniterThread = nullptr;
	{
		readLock lock(rwLastTime);
		lastTime = LogTimeStamp;
	}
	timeOut=8000;
}

Connect::~Connect(void)
{
	mStopMoniter();
	mStopConnect();
}

void Connect::mStartConnect()
{
    {
		writeLock lock(m_lock);
		if(m_Thread==nullptr)
		{
			m_Thread = new boost::thread(boost::bind(&Connect::ProThread,this));
		}else if(!m_Thread->joinable())
		{
			delete m_Thread;
			m_Thread = new boost::thread(boost::bind(&Connect::ProThread,this));
		}
	}	
}

void Connect::mStopConnect()
{	
	{
		writeLock lock(m_lock);
		if(m_Thread!=nullptr)
		{
			if(m_Thread->joinable())
			{
				m_Thread->interrupt();
				m_Thread->join();
			}
			delete m_Thread;
			m_Thread = nullptr;
		}
	}	
}

void Connect::mStartMoniter()
{	
	{
		writeLock lock(m_lock);
		if(m_MoniterThread==nullptr)
		{
			m_MoniterThread = new boost::thread(boost::bind(&Connect::ProMoniterThread,this));
		}else if(!m_MoniterThread->joinable())
		{
			delete m_MoniterThread;
			m_MoniterThread = new boost::thread(boost::bind(&Connect::ProMoniterThread,this));
		}
	}	
}

void Connect::mStopMoniter()
{	
	{
		writeLock lock(m_lock);
		if(m_MoniterThread!=nullptr)
		{
			if(m_MoniterThread->joinable())
			{
				m_MoniterThread->interrupt();
				m_MoniterThread->join();
			}
			delete m_MoniterThread;
			m_MoniterThread = nullptr;
		}
	}	
}

bool Connect::mIsCorrect()
{
	readLock lock(rwLastTime);
	return (LogTimeStamp - lastTime < timeOut);
}

void Connect::SetTimeOutTime(unsigned int pms)
{
	timeOut = pms;
}

void Connect::SetLastTime(timeStamp pTime)
{
	writeLock lock(rwLastTime);
    lastTime = pTime;
}

void Connect::SetSink(ISink* psink)
{
    this->m_pSink=psink;
}

void Connect::ProMoniterThread()
{
    ThreadExitPoint;
	int tmpTimeOut = timeOut*2;
	for (int i=0;i<tmpTimeOut/500;i++)
	{
		BoostSleep(500);
	}

	while(true)
	{

		timeStamp dif;
		{
			timeStamp nowTime = LogTimeStamp;
			readLock lock(rwLastTime);
			dif = nowTime-lastTime;
		}

        if(dif>(timeStamp)tmpTimeOut)
		{
			if(m_Thread!=nullptr)
			{
				mStopConnect();
			}
			mStartConnect();
			for (int i=0;i<tmpTimeOut/1000;i++)
			{
				BoostSleep(500);
			}
		}
		for (int i=0;i<tmpTimeOut/1000;i++)
		{
			BoostSleep(500);
		}
	}
	
}
