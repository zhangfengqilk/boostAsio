#include "CustomTool.h"
#include <vector>
#include <string>
using namespace std;
void BoostSleep(int pMSec)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(pMSec));
}

int CharToInt(char c)
{
	if(c<='9'&&c>='0') return c-'0';
	if(c>='a' && c<='f') return c-87;
	if(c>='A' && c<='F') return c-55; 
	return -1;
}

string BufToString(const byte *pBuf,int len)
{
	string outStr;
	char temp[16];
	for (int i=0;i<len;i++)
	{
		sprintf(temp,"[%.2d]%.2x",i,(uint8_t)pBuf[i]);
		
		outStr.append(temp,6);
	}
	return outStr;
}

double ProcessAngle(double angle)
{
	if (angle>=180)
	{
		angle-=360;
	}
	else if (angle<=-180)
	{
		angle+=360;
	}
	return angle;
}
