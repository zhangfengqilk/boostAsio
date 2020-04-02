#include "CodeScannerComConnect.h"


CodeScannerComConnect::CodeScannerComConnect(ComPara pComPara):ABCodeScannerComConnect(pComPara)
{
	readFrameDataIndex = 0;
	status = ICDheadFirstEnum;	

	m_ICDCarStatusFrame.time = 0;
	receiveBuf = (byte*)calloc(max(CarMileageFrameDataLen,CarStatusFrameDataLen),sizeof(byte));
	SetTimeOutTime(2000);
}

CodeScannerComConnect::~CodeScannerComConnect(void)
{
	StopMoniter();
	StopConnect();
	free(receiveBuf);
	receiveBuf=nullptr;
}

void CodeScannerComConnect::GetCodeInfo(CodeScannerFrame &pICDCarStatusFrame)
{
	if(LogTimeStamp-m_ICDCarStatusFrame.time>1000)
	{
		pICDCarStatusFrame.time=0;
	}
	else
	{
		readLock lock(rwmutex_CarStatusFrame);
		pICDCarStatusFrame = m_ICDCarStatusFrame;
	}	
}

bool CodeScannerComConnect::SendICDControlCarFrame(const ICDControlCarFrame &pICDControlCarFrame)const
{
    //LOGICDControlCarFrame(pICDControlCarFrame,LOGREALESE);
	byte *buf= (byte*)calloc(ICDControlCarFrameLen,sizeof(byte));
	pICDControlCarFrame.CovernToBuf(buf);
	bool result = Writer(buf,ICDControlCarFrameLen);
	free(buf);
	return result;
}

bool CodeScannerComConnect::ISCorrect()
{
	/*bool result  =false;
	{
		readLock lock(rwmutex_CarStatusFrame);
		timeStamp dif = LogTimeStamp - m_ICDCarStatusFrame.time;
		if(dif<1000)
		{
			result = true;
		}
	}
	return result;*/
	return mIsCorrect();
}

void CodeScannerComConnect::StartConnect()
{	
    cout<<"start ICDCOM"<<endl;
	mStartConnect();
    if(false)
	{
		StartMoniter();
	}	
}

void CodeScannerComConnect::StopConnect()
{	
    mStopConnect();
	cout<<"stop ICDCOM"<<endl;	
}

void CodeScannerComConnect::StartMoniter()
{	
    mStartMoniter();
}

void CodeScannerComConnect::StopMoniter()
{	
    mStopMoniter();
}

void CodeScannerComConnect::ProcessChar(byte pChar)
{
    std::cout<<pChar<<std::flush;
    this->m_pSink->OnNotified("收到新的消息");

//	switch (status)
//	{
//	case ICDheadFirstEnum:
//		{
//			if (HeadChar == pChar)
//			{
//				status = ICDheadFrameFlagEnum;
//				receiveBuf[0] = pChar;
//			}
//			break;
//		}
//	case ICDheadFrameFlagEnum:
//		{
//			if(CarStatusFrameFlag == pChar)
//			{
//				status = ICDCarStatusFrameEnum;
//				receiveBuf[1] = pChar;
//				readFrameDataIndex = 2;
//			}
//			else if(CarMileageFrameFlag==pChar)
//			{
//				status = ICDCarMileageFrameEnum;
//				receiveBuf[1] = pChar;
//				readFrameDataIndex = 2;
//			}else if(HeadChar == pChar)
//			{
//				status = ICDheadFrameFlagEnum;
//			}
//			else
//			{
//				status = ICDheadFirstEnum;
//			}
//			break;
//		}
//	case ICDCarStatusFrameEnum:
//		{
//			receiveBuf[readFrameDataIndex] = pChar;
//			readFrameDataIndex++;
//			if(readFrameDataIndex >= CarStatusFrameDataLen)
//			{
//				ConvertBufToCarStatusFrame();
//				status = ICDheadFirstEnum;
//			}
//			break;
//		}
//	case ICDCarMileageFrameEnum:
//		{
//			receiveBuf[readFrameDataIndex] = pChar;
//			readFrameDataIndex++;
//			if(readFrameDataIndex >= CarMileageFrameDataLen)
//			{
//				ConvertBufToCarMileageFrame();
//				status = ICDheadFirstEnum;
//			}
//			break;
//		}
//	}
}

void CodeScannerComConnect::ConvertBufToCarStatusFrame()
{

}

void CodeScannerComConnect::ConvertBufToCarMileageFrame()
{

}
