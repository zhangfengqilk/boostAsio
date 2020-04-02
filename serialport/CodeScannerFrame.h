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
	bool isBreakDown;    //��������
	bool obstacle_Front; //�������ϱ�־
	bool obstacle_Back;
	bool battery_breakdown;//��ع��ϱ�־
	bool drop_flag;//�����־
    CodeScannerFrame():carPower(0),speed(0),angularSpeed(0),Mileage(0),time(0),isCharging(false),isMoving(false),isBreakDown(false)
		,obstacle_Front(false),obstacle_Back(false),battery_breakdown(false),drop_flag(false)
	{

	}
};

//speed mm/s;angularSpeed 0.01deg/s;obstacleClosed TRUE-�أ�beginCharge true-�ǣ�stopCharge true-ͣ��
struct ICDControlCarFrame
{
	short speed;
	short angularSpeed;
	bool obstacleClosed;//����
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

	//buf��Ҫ��֤>10�ĳ���
    void CovernToBuf(byte *buf)const
	{
		/* Buf[6] ����  1����Ч��0(��Ч)
		0x01    | 0x02   |  0x04  | 0x08   |  0x10            
		������������������������������������������������������
		Bit0    | Bit1   |  Bit2  | Bit3   |  Bit4             
		������������������������������������������������������
		����ʹ��|����ʹ��|���ʹ��|ֹͣ���|TIM310�״��⿪��
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
		if(beginCharge)buf[6]=buf[6]|0x04; //��ʼ���ʹ��λ
		if(stopCharge)buf[6]=buf[6]|0x08;  //ֹͣ���ʹ��λ
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
