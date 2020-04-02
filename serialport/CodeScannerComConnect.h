#ifndef _H_ICDCOMCONNECT_
#define _H_ICDCOMCONNECT_
#include "CodeScannerFrame.h"
#include "ABCodeScannerComConnect.h"
class CodeScannerComConnect :public ABCodeScannerComConnect
{
public:
    CodeScannerComConnect(ComPara pComPara);
    ~CodeScannerComConnect(void);
    void GetCodeInfo(CodeScannerFrame &pICDCarStatusFrame);
	bool SendICDControlCarFrame(const ICDControlCarFrame &pICDControlCarFrame)const;
	bool ISCorrect();
	void StartConnect();
	void StopConnect();
	void StartMoniter();
	void StopMoniter();

protected:
	void ProcessChar(byte pChar);
private:
	RWmutex rwmutex_CarStatusFrame;
	RWmutex rwmutex_CarMileageFrame;
	ICDFrameStatus status;
    struct CodeScannerFrame m_ICDCarStatusFrame;
	int readFrameDataIndex;
	byte *receiveBuf;
	void ConvertBufToCarStatusFrame();
	void ConvertBufToCarMileageFrame();
	int MaxSavedCount;

};
#endif
