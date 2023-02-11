/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            Led.cpp
** Latest modified date: 2019-05-15
** Latest version:       V1.0.0
** Description:          SmartKit Led API
**
**------------------------------------------------------------
** Created by:
** Created date:         2019-05-15
** Version:              V1.0.0
** Descriptions:         SmartKit Led API
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "SmartKit.h"
#include "JoyStick.h"
#include "Led.h"
#include "Button.h"
#include "VoiceRecognition.h"
#include "DobotPixy.h"
#include <SoftwareSerial.h>



JOYSTICK gJoyStick;         /* 摇杆类 */
LED      gLed;              /* 灯类 */
BUTTON   gButton;           /* 按键类 */
VoiceRecognition gVoiveCN;  /* 中文语音类 */
SoftwareSerial softSerial(SOFTSERIAL_RX_PIN,SOFTSERIAL_TX_PIN); /* 英文语音类 */
VIS gVIS;                   /* 视觉识别类 */

/*************************************************************
** Function name:	  SmartKitInit
** Descriptions:	  SmartKit初始化,初始化包括：摇杆
**                                               指示灯
**                                               按钮
**												 英文语音
**                             注意：视觉需要单独初始化
**									 中文语音需要单独初始化
** Input parameters:  no
** Output parameters: no
** Returned value:	  no
*************************************************************/
void SmartKit_Init(void)
{
    Serial.begin(115200);
    Serial.println("======Enter application======");
    Serial.println("======Version: 2.0.1======");
    gJoyStick.Init(JOYSTICK_XPIN,
                   JOYSTICK_YPIN, 
                   JOYSTICK_ZPIN);
	Serial.println("======JoyStick Init======");
    gLed.Init(LED_REDPIN,
              LED_BLUEPIN, 
              LED_GREENPIN);
	Serial.println("======Led Init======");
    gButton.Init(BUTTON_REDPIN,
                 BUTTON_BLUEPIN, 
                 BUTTON_GREENPIN);
	Serial.println("======Button Init======");
    softSerial.begin(9600);
	Serial.println("======VoiveEN Init======");
    Serial.println("======SmartKit Init======");
}

/*************************************************************
** Function name:	  SmartKit_VoiceCNInit
** Descriptions:	  中文语音初始化
**                             注意：视觉需要单独初始化
** Input parameters:  no
** Output parameters: no
** Returned value:	  no
*************************************************************/
void SmartKit_VoiceCNInit(void)
{
	Serial.begin(115200);
    gVoiveCN.init();
	Serial.println("======VoiveCN Init======");
}

/*************************************************************
** Function name:	  SmartKit_ButtonCheckState
** Descriptions:	  检查按键状态
** Input parameters:  color: 按键的颜色，
**                           可传递值BLUE,GREEN,RED
** Output parameters: no
** Returned value:	  返回按键状态，UP或DOWN
*************************************************************/

int SmartKit_ButtonCheckState(char color)
{
    return gButton.CheckState(color);
}

/*************************************************************
** Function name:	  SmartKit_JoyStickReadXYValue
** Descriptions:	  读取摇杆数值
** Input parameters:  axis坐标系,可传递AXISX，AXISY
** Output parameters: no
** Returned value:	  摇杆的数值
*************************************************************/

int SmartKit_JoyStickReadXYValue(int axis)
{
    return gJoyStick.ReadXYValue(axis);
}

/*************************************************************
** Function name:	  SmartKit_JoyStickCheckPressState
** Descriptions:	  检测摇杆按压状态
** Input parameters:  no
** Output parameters: no
** Returned value:	  按压状态，UP,DOWN
*************************************************************/

int SmartKit_JoyStickCheckPressState(void)
{
    return gJoyStick.CheckPressState();
}

/*************************************************************
** Function name:	  SmartKit_LedCheckStatu
** Descriptions:	  检测LED的状态
** Input parameters:  color: led灯的颜色，
**                           可传递值BLUE,GREEN,RED
** Output parameters: no
** Returned value:	  led的状态 ON或OFF
*************************************************************/

int SmartKit_LedCheckState(char color)
{
    return gLed.CheckState(color);
}

/*************************************************************
** Function name:	  SmartKit_LedTurn
** Descriptions:	  开关LED
** Input parameters:  color: led灯的颜色，
**                           可传递值BLUE,GREEN,RED
**					  state: led灯的状态，
**                           可传递值ON,OFF
** Output parameters: no
** Returned value:	  no
*************************************************************/

void SmartKit_LedTurn(char color, int state)
{
    gLed.Turn(color, state);
}

/*************************************************************
** Function name:	  SmartKit_VoiceCNAddCommand
** Descriptions:	  中文声音添加
** Input parameters:  *Voice: 需要添加的声音的指针
**					  num: 需要添加的声音的序列号
** Output parameters: no
** Returned value:	  no
*************************************************************/

void SmartKit_VoiceCNAddCommand(char *Voice, int num)
{
    gVoiveCN.addCommand(Voice, num);
}

/*************************************************************
** Function name:	  SmartKit_VoiceCNVoiceCheck
** Descriptions:	  中文声音检测
** Input parameters:  num: 需要检测的序号
** Output parameters: no
** Returned value:	  TRUE: 检测到; FALSE: 没有检测到
*************************************************************/

int SmartKit_VoiceCNVoiceCheck(int num)
{
    return gVoiveCN.VoiceCheck(num);
}

/*************************************************************
** Function name:	  SmartKit_VoiceCNStart
** Descriptions:	  中文声音检测开始
** Input parameters:  no
** Output parameters: no
** Returned value:	  no
*************************************************************/

void SmartKit_VoiceCNStart(void)
{
    gVoiveCN.start();
}

/*************************************************************
** Function name:	  SmartKit_VoiceENGVoiceCheck
** Descriptions:	  英文声音检测
** Input parameters:  num: 需要检测的序号
** Output parameters: no
** Returned value:	  TRUE: 检测到; FALSE: 没有检测到
*************************************************************/

int SmartKit_VoiceENGVoiceCheck(int num)
{
	static int lastNum = 0;
	int preNum = 0;
	preNum = softSerial.read();
	if (preNum > 0)
	{ 
		lastNum = preNum;
	}
	if (lastNum == num)
	{
		lastNum = 0;
		return TRUE;
	}
	return FALSE;    
}

/*************************************************************
** Function name:	  SmartKit_VoiceENGStart
** Descriptions:	  英文声音检测开始
** Input parameters:  no
** Output parameters: no
** Returned value:	  no
*************************************************************/

void SmartKit_VoiceENGStart(void)
{
    softSerial.listen();
}

/*************************************************************
** Function name:      Init
** Descriptions:       视觉初始化，
**					   默认门型抬升高度30，
**					   初始化之前需要完成颜色标定和位置标定
** Input parameters:   no
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISInit(void)
{
    gVIS.Init();
}

/*************************************************************
** Function name:      SmartKit_VISSetDobotMatrix
** Descriptions:       设置机械臂变换矩阵
** Input parameters:   x1: 方块1的x坐标
**					   y1: 方块1的y坐标
**					   x2: 方块2的x坐标
**					   y2: 方块2的y坐标
**					   x3: 方块3的x坐标
**					   y3: 方块3的y坐标
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISSetDobotMatrix(float x1, float y1,
                                float x2, float y2,
                                float x3, float y3)
{
    gVIS.SetDobotMatrix(x1, y1, x2, y2, x3, y3);
}

/*************************************************************
** Function name:      SmartKit_VISSetPixyMatrix
** Descriptions:       设置pixy变换矩阵
** Input parameters:   x1:		方块1的x坐标
**					   y1:		方块1的y坐标
**					   length1: 方块1的长
**					   weight1: 方块1的宽
**					   x2:		方块2的x坐标
**					   y2:		方块2的y坐标
**					   length2: 方块2的长
**					   weight2: 方块2的宽
**					   x3:		方块3的x坐标
**					   y3:		方块3的y坐标
**					   length3: 方块3的长
**					   weight3: 方块3的宽
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISSetPixyMatrix(
    float x1, float y1, float length1, float wide1,
    float x2, float y2, float length2, float wide2,
    float x3, float y3, float length3, float wide3)
{
    gVIS.SetPixyMatrix(
        x1, y1, length1, wide1,
        x2, y2, length2, wide2,
        x3, y3, length3, wide3);
}

/*************************************************************
** Function name:      SmartKit_VISSetGrapAreaZ
** Descriptions:       设置抓取区域z轴坐标
** Input parameters:   z: 抓取区域高度
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISSetGrapAreaZ(float z)
{
    gVIS.SetGrapAreaZ(z);
}

/*************************************************************
** Function name:      SmartKit_VISGetGrapAreaZ
** Descriptions:       获取抓取区域z轴坐标
** Input parameters:   no
** Output parameters:  no
** Returned value:     抓取区域高度
*************************************************************/

float SmartKit_VISGetGrapAreaZ(void)
{
    return gVIS.GetGrapAreaZ();
}

/*************************************************************
** Function name:      SmartKit_VISSetAT
** Descriptions:       设置机械臂视觉识别区域坐标
** Input parameters:   x:
**					   y:
**					   z:
**					   r: 旋转角度
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISSetAT(float x, float y, float z, float r)
{
    gVIS.SetAT(x, y, z, r);
}

/*************************************************************
** Function name:      SmartKit_VISSetColorSignature
** Descriptions:       设置物块颜色标识
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   signature: 物块标识
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISSetColorSignature(char color, char signature)
{
    return gVIS.SetColorSignature(color, signature);
}

/*************************************************************
** Function name:      SmartKit_VISSetBlockTA
** Descriptions:       设置各颜色物块目标区域
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   x: 物块的x坐标
**					   y: 物块的y坐标
**					   z: 物块的z坐标
**					   r: 物块的旋转角度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISSetBlockTA(char color, 
                            float x, 
                            float y, 
                            float z, 
                            float r)
{
    return gVIS.SetBlockTA(color, x, y, z, r);
}

/*************************************************************
** Function name:      SmartKit_VISGetBlockCheckNum
** Descriptions:       获取视觉检测到的不同颜色的物块数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     物块数量
*************************************************************/

char SmartKit_VISGetBlockCheckNum(char color)
{
    return gVIS.GetBlockCheckNum(color);
}

/*************************************************************
** Function name:      SmartKit_VISSetBlockPlaceNum
** Descriptions:       设置物块放置数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   placeNum: 放置的数量
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISSetBlockPlaceNum(char color, int placeNum)
{
    return gVIS.SetBlockPlaceNum(color, placeNum);
}

/*************************************************************
** Function name:      SmartKit_VISGetBlockPlaceNum
** Descriptions:       获取物块放置的数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     物块数量
*************************************************************/

char SmartKit_VISGetBlockPlaceNum(char color)
{
    return gVIS.GetBlockPlaceNum(color);
}

/*************************************************************
** Function name:      SmartKit_VISSetBlockHeight
** Descriptions:       设置物块高度
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   height: 物块高度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISSetBlockHeight(char color, float height)
{
    return gVIS.SetBlockHeight(color, height);
}

/*************************************************************
** Function name:      SmartKit_VISBlockParmCheckNumClear
** Descriptions:       清除四个颜色pixy检测到的物块数量
** Input parameters:   no
** Output parameters:  no
** Returned value:     no
*************************************************************/

void SmartKit_VISBlockParmCheckNumClear(void)
{
    gVIS.BlockParmCheckNumClear();
}

/*************************************************************
** Function name:      SmartKit_VISRun
** Descriptions:       视觉识别
** Input parameters:   no
** Output parameters:  no
** Returned value:     TRUE: 存在物块;
**					   FALSE: 原因有以下几种可能
**							  1,没有检测到物块，
**							  2,物块的颜色标记设置有误
*************************************************************/

char SmartKit_VISRun(void)
{
    return gVIS.Run();
}

/*************************************************************
** Function name:      SmartKit_VISSetGrapBlockMark
** Descriptions:       设置物块抓取标记
** Input parameters:   mark: 物块抓取标记
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

int SmartKit_VISSetGrapBlockMark(int mark)
{
    return gVIS.SetGrapBlockMark(mark);
}

/*************************************************************
** Function name:      SmartKit_VISGetGrapBlockMark
** Descriptions:       获取物块抓取标记
** Input parameters:   no
** Output parameters:  no
** Returned value:     物块抓取标记：TRUE已经抓取，
                                     FALSE，未抓取
*************************************************************/

int SmartKit_VISGetGrapBlockMark(void)
{
    return gVIS.GetGrapBlockMark();
}

/*************************************************************
** Function name:      SmartKit_VISGrabBlock
** Descriptions:       抓取物块
** Input parameters:   color: 抓取物块的颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   blockNum: 物块的编号
**					   r: 抓取旋转的角度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISGrabBlock(char color, int blockNum, float r)
{
    return gVIS.GrabBlock(color, blockNum, r);
}

/*************************************************************
** Function name:      SmartKit_VISPlaceBlock
** Descriptions:       放置物块
** Input parameters:   color: 放置物块的颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char SmartKit_VISPlaceBlock(char color)
{
    return gVIS.PlaceBlock(color);
}

