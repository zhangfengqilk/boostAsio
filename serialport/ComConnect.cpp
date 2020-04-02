#include "ComConnect.h"

ComConnect::ComConnect(ComPara pComPara)
{
	m_Client = nullptr;
	StopThread = true;
	isCorrect=false;
	m_ComPara = pComPara;
}

ComConnect::~ComConnect(void)
{

	mStopMoniter();
	mStopConnect();
	m_IO.stop();
	if(m_Client!=nullptr)
	{
		delete m_Client;
		m_Client = nullptr;
	}
}

bool ComConnect::Writer(const byte *buf,int len)const
{
	if(m_Client!=nullptr&&m_Client->is_open())
	{
		boost::system::error_code er;
		int sendLen = boost::asio::write(*m_Client,boost::asio::buffer(buf,len),er);
		if (!er&&sendLen ==len)
		{
			return true;
		}
	}
	return false;
}
bool ComConnect::write_to_serial(const string data)
{
    if(m_Client!=nullptr&&m_Client->is_open())
    {
        boost::system::error_code m_ec;
        size_t len = write(*m_Client, boost::asio::buffer(data),m_ec);
        //cout << len << "\t" <<  data << endl;
        return true;
    }
    return false;
}



void ComConnect::mStopConnect()
{	
    StopThread = true;
	StopCom();
	Connect::mStopConnect();	
}

void ComConnect::mStartConnect()
{	
    StopThread = false;
	Connect::mStartConnect();	
}

bool ComConnect::InitPort()
{
	try
	{
		m_Client = new boost::asio::serial_port(m_IO,m_ComPara.name);
		m_Client->set_option(SPB::baud_rate(m_ComPara.baud_rate));
		m_Client->set_option(SPB::flow_control(m_ComPara.flow_control));
		m_Client->set_option(SPB::parity(m_ComPara.parity));
		m_Client->set_option(SPB::stop_bits(m_ComPara.stop_bits));
		m_Client->set_option(SPB::character_size(m_ComPara.character_size));
		isCorrect = true;
		return true;
	}catch(exception ex)
	{
		delete m_Client;
		m_Client = nullptr;
		return false;
	}
}

void ComConnect::ProThread()
{
		while(!StopThread)
		{
			ThreadExitPoint;
			while(m_Client ==nullptr)
			{
				if(!InitPort())
				{
					RELEASE_MSG("建立串口%s连接失败",m_ComPara.name.c_str());
					BoostSleep(2000);
				}
				else
				{
					RELEASE_MSG("成功建立串口%s连接",m_ComPara.name.c_str());

				}
			}
			try{
				if(isCorrect)
				{
					if(m_Client->is_open())
					{
						byte buf;
						boost::system::error_code er;

						int len = boost::asio::read(*m_Client,boost::asio::buffer(&buf,1),er);
						if(!er && len ==1)
						{
                            ProcessChar(buf);
							isCorrect = true;
						}else
						{
							isCorrect = false;
							BoostSleep(1000);
						}

					}else
					{
						isCorrect = false;
						BoostSleep(1000);
					}

				}else
				{
					if(!m_Client->is_open())
					{
						boost::system::error_code ec;
						m_Client->open(m_ComPara.name,ec);
						if(ec)
						{
							isCorrect =false;
							BoostSleep(1000);

						}else
						{
							ConnectSuceess();
							isCorrect =true;
						}
					}else
					{
						boost::system::error_code ec;
						m_Client->close(ec);
						BoostSleep(100);
					}
				}
			}catch(exception ex)
			{
				isCorrect =false;
				BoostSleep(1000);
			}
		}		
}

void ComConnect::StopCom()
{	
		if(m_Client==nullptr)
		{			
			return;
		}		
		if(m_Client->is_open())
        {
			boost::system::error_code er;
			m_Client->close(er);			
		}
		isCorrect = false;		
}

void ComConnect::ProcessChar(byte pChar)
{
    cout<<pChar<<flush;
}

void ComConnect::ConnectSuceess()
{

}
