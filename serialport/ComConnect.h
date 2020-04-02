#ifndef _H_COMCONNECT_
#define _H_COMCONNECT_
#include "boost/asio.hpp"
#include "boost/thread.hpp"
#include "Connect.h"
#include <string>
typedef boost::asio::serial_port_base SPB;

using namespace std;
struct ComPara
{
	string name;
	int baud_rate;
	SPB::parity::type parity;
	SPB::flow_control::type flow_control;
	SPB::stop_bits::type stop_bits;
	int character_size;
};

class ComConnect:public Connect
{
public:
	ComConnect(ComPara pComPara);
	virtual ~ComConnect(void);
	bool Writer(const byte *buf,int len)const;
    bool write_to_serial(const string data);
	void mStopConnect();
	void mStartConnect();
protected:
	bool isCorrect;
	boost::asio::serial_port *m_Client;
	boost::asio::io_service m_IO;
	ComPara m_ComPara;
	bool StopThread;
    bool InitPort();
    void ProThread();
	void StopCom();
	virtual void ProcessChar(byte pChar);
	virtual void ConnectSuceess();
};
#endif

