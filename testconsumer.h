#ifndef TESTCONSUMER_H
#define TESTCONSUMER_H
#include "serialport/CodeScannerComConnect.h"

class testConsumer : public ISink
{
public:
    testConsumer();
    void sendstr(string str);

    // ISink interface
public:
    virtual void OnNotified(string s) override;
    CodeScannerComConnect* cscc;
};

#endif // TESTCONSUMER_H
