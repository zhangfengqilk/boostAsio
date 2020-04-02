#ifndef _ICDFRAME_H
#define _ICDFRAME_H
#include <queue>
#include "Global.h"
using namespace std;

const short ICDControlCarFrameLen = 10;
const short CarStatusFrameDataLen = 16;
const short CarMileageFrameDataLen = 20;
const byte HeadChar = 0xEE;
const byte CarStatusFrameFlag = 0x61;
const byte CarMileageFrameFlag = 0x63;
struct CodeScannerFrame
{
	unsigned short carPower; //  1%
	short speed;//  mm/s
	short angularSpeed;//  0.01deg/s
	unsigned int Mileage;//  mm
	timeStamp time;
	bool isCharging;
	bool isMoving;
	bool isBreakDown;    //驱动故障
	bool obstacle_Front; //超声避障标志
	bool obstacle_Back;
	bool battery_breakdown;//电池故障标志
	bool drop_flag;//跌落标志
    CodeScannerFrame():carPower(0),speed(0),angularSpeed(0),Mileage(0),time(0),isCharging(false),isMoving(false),isBreakDown(false)
		,obstacle_Front(false),obstacle_Back(false),battery_breakdown(false),drop_flag(false)
	{

	}
};

//speed mm/s;angularSpeed 0.01deg/s;obstacleClosed TRUE-关；beginCharge true-是；stopCharge true-停；
struct ICDControlCarFrame
{
	short speed;
	short angularSpeed;
	bool obstacleClosed;//避障
	bool beginCharge;
	bool stopCharge;
	ICDControlCarFrame():speed(0),angularSpeed(0),obstacleClosed(false),beginCharge(false),stopCharge(false){}
	void Init(void)
	{
		speed=0;
		angularSpeed=0;
		obstacleClosed=false;
		beginCharge=false;
		stopCharge=false;
	};

	//buf需要保证>10的长度
    void CovernToBuf(byte *buf)const
	{
		/* Buf[6] 含义  1（有效）0(无效)
		0x01    | 0x02   |  0x04  | 0x08   |  0x10            
		———————————————————————————
		Bit0    | Bit1   |  Bit2  | Bit3   |  Bit4             
		———————————————————————————
		超声使能|跌落使能|充电使能|停止充电|TIM310雷达检测开关
		*/
		memset(buf,0,ICDControlCarFrameLen);
		buf[0]=0xE1;
		buf[1]=0x61;
		short tmpSpeed = -speed;
		TypeToBuf_TrueCode(tmpSpeed,&buf[2],2);
		short tmpAngularSpeed = angularSpeed*-1;
		TypeToBuf_TrueCode(tmpAngularSpeed,&buf[4],2);
		buf[6]=0x00;
		//if(obstacleClosed)buf[6]=buf[6]|0x01; 
		if(beginCharge)buf[6]=buf[6]|0x04; //开始充电使能位
		if(stopCharge)buf[6]=buf[6]|0x08;  //停止充电使能位
		buf[6] = buf[6] | 0x10;
		byte sumCheck=0x00;
		byte xorCheck = 0x00;
		for(int i=0;i<8;i++)
		{
			sumCheck+=buf[i];
			xorCheck^=buf[i];
		}
		buf[8]=sumCheck;
		buf[9]=xorCheck;
	};
};
enum ICDFrameStatus
{
	ICDheadFirstEnum,
	ICDheadFrameFlagEnum,
	ICDCarStatusFrameEnum,
	ICDCarMileageFrameEnum,
};

void LOGICDCarStatusFrame(const CodeScannerFrame &pCarStatusFrame,LOGTYPE plogType );
void LOGICDCarBuf(const byte* pRecievedBuf,int len,LOGTYPE plogType);
void LOGICDControlCarFrame(const ICDControlCarFrame &pICDControlCarFrame,LOGTYPE plogType);
#endif
