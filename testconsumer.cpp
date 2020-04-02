#include "testconsumer.h"

testConsumer::testConsumer()
{
    ComPara comPara;
    comPara.name= "/dev/pts/8";
    comPara.baud_rate= 115200;
    comPara.character_size = 8;
    comPara.flow_control = SPB::flow_control::type::none;
    comPara.parity = SPB::parity::type::none;
    comPara.stop_bits = SPB::stop_bits::type::one;
    this->cscc=new CodeScannerComConnect(comPara);
    this->cscc->SetSink(this);
    this->cscc->StartConnect();
}

void testConsumer::sendstr(string str)
{
    this->cscc->write_to_serial(str);
}

void testConsumer::OnNotified(string s)
{
    std::cout<<"我被回调了: "<<s<<std::endl;
}
