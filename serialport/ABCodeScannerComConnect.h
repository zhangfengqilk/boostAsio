#ifndef _H_ABICDCOMCONNECT_
#define _H_ABICDCOMCONNECT_
#include "CodeScannerFrame.h"
#include "ComConnect.h"
class ABCodeScannerComConnect:public ComConnect
{
public:
    ABCodeScannerComConnect(ComPara pComPara);
    virtual ~ABCodeScannerComConnect(void);
    virtual void GetCodeInfo(CodeScannerFrame &pCodeScannerFrame)=0;
	virtual bool ISCorrect()=0;
	virtual void StartConnect()=0;
	virtual void StopConnect()=0;
	virtual void StartMoniter()=0;
	virtual void StopMoniter()=0;
};
#endif

