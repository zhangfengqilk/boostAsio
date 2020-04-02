#ifndef _H_BOOSTTOOL_
#define _H_BOOSTTOOL_
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"
#include "boost/bind.hpp"
#include "TypeDef.h"

#include <vector>
#include <string>
using namespace std;
#define LogTimeStamp TimeStamp::Get()->GetTimeStamp()
#define ThreadExitPoint boost::this_thread::interruption_point()
void BoostSleep(int pMSec);
int CharToInt(char c);
template<typename T> bool BufToSignType_TrueCode(T &out, const byte *buf,short len);
template<typename T> bool BufToUnSignType_TrueCode(T &out,const byte *buf,short len);
template<typename T> bool TypeToBuf_TrueCode(const T &pNum, byte *outBuf,short buflen);

//模板函数不支持分离编译

//小端对齐即直接数组低位存储了数值低位
template<typename T>
bool BufToSignType_TrueCode(T &out, const byte *buf,short len)
{
	T result;
	if(sizeof(T)<len)return false;
	T sign=buf[len-1]&0x80 ? -1 : 1;
	byte *tmpBuf=(byte*)calloc(len,sizeof(byte));;
	memcpy(tmpBuf,buf,len);
	tmpBuf[len-1]=buf[len-1]&0x7f;
	memcpy(&result,tmpBuf,len);
	result*=sign;
	out = result;
	free(tmpBuf);
	return true;
}

template<typename T>
bool BufToUnSignType_TrueCode(T &out,const byte *buf,short len)
{
	T result;
	if(sizeof(T)<len)return false;
	memcpy(&result,buf,len);
	out = result;
	return true;
}
template<typename T>
bool TypeToBuf_TrueCode(const T &pNum, byte *outBuf,short buflen)
{
	short Tsize = sizeof(T);
	if(Tsize>buflen)return false;
	if(pNum>=0)
	{
		memcpy(outBuf,&pNum,Tsize);
	}else
	{
		T tmpNum = -1*pNum;
		memcpy(outBuf,&tmpNum,Tsize);
		outBuf[Tsize-1] = outBuf[Tsize-1]|0x80;
	}
	return true;
}

double ProcessAngle(double angle);

string BufToString(const byte *pBuf,int len);
#endif
