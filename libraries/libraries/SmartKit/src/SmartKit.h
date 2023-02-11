/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            Led.h
** Latest modified date: 2019-05-15
** Latest version:       V1.0.0
** Description:          SmartKit API
**
**------------------------------------------------------------
** Created by:
** Created date:         2019-05-15
** Version:              V1.0.0
** Descriptions:         SmartKit API
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#ifndef SmartKit_H
#define SmartKit_H

#include "Arduino.h"
#include "SmartKitType.h"
#include "Magician.h"

#define JOYSTICK_XPIN   7    /* JoyStick X轴连接的引脚 */
#define JOYSTICK_YPIN   6    /* JoyStick Y轴连接的引脚 */
#define JOYSTICK_ZPIN   A5   /* JoyStick Z轴连接的引脚 */

#define LED_REDPIN      9    /* 红色灯连接引脚 */
#define LED_GREENPIN    A1   /* 绿色灯连接引脚 */
#define LED_BLUEPIN     A3   /* 蓝色灯连接引脚 */

#define BUTTON_REDPIN   A0   /* 红色按钮连接引脚 */
#define BUTTON_GREENPIN A2   /* 绿色按钮连接引脚 */
#define BUTTON_BLUEPIN  A4   /* 蓝色按钮连接引脚 */

#define SOFTSERIAL_RX_PIN  A11    /* 英文语音RX引脚 */
#define SOFTSERIAL_TX_PIN  14     /* 英文语音TX引脚 */

/*************************************************************
  Init: 初始化
*************************************************************/

extern void SmartKit_Init(void);

/*************************************************************
  Button: 按钮
*************************************************************/

extern int SmartKit_ButtonCheckState(char color);

/*************************************************************
  JoyStick: 摇杆
*************************************************************/

extern int SmartKit_JoyStickReadXYValue(int axis);
extern int SmartKit_JoyStickCheckPressState(void);

/*************************************************************
  Led: 指示灯
*************************************************************/

extern int SmartKit_LedCheckState(char color);
extern void SmartKit_LedTurn(char color, int state);

/*************************************************************
  VoiceCN: 中文语音
*************************************************************/

extern void SmartKit_VoiceCNInit(void);
extern void SmartKit_VoiceCNAddCommand(char *Voice, int num);
extern int SmartKit_VoiceCNVoiceCheck(int num);
extern void SmartKit_VoiceCNStart(void);

/*************************************************************
  VoiceENG: 英文语音
*************************************************************/

extern int SmartKit_VoiceENGVoiceCheck(int num);
extern void SmartKit_VoiceENGStart(void);

/*************************************************************
  VIS: 视觉识别
*************************************************************/
extern void SmartKit_VISInit(void);
extern void SmartKit_VISSetDobotMatrix(
                float x1, float y1,
                float x2, float y2,
                float x3, float y3);
extern void SmartKit_VISSetPixyMatrix(
                float x1, float y1, float length1, float wide1,
                float x2, float y2, float length2, float wide2,
                float x3, float y3, float length3, float wide3);
extern void SmartKit_VISSetGrapAreaZ(float z);
extern float SmartKit_VISGetGrapAreaZ(void);
extern void SmartKit_VISSetAT(
                float x, 
                float y, 
                float z, 
                float r);
extern char SmartKit_VISSetColorSignature(
                char color,                                
                char signature);
extern char SmartKit_VISSetBlockTA(
                char color,
                float x,
                float y,
                float z,
                float r);
extern char SmartKit_VISGetBlockCheckNum(char color);
extern char SmartKit_VISSetBlockPlaceNum(char color, int placeNum);
extern char SmartKit_VISGetBlockPlaceNum(char color);
extern char SmartKit_VISSetBlockHeight(char color, float height);
extern void SmartKit_VISBlockParmCheckNumClear(void);
extern char SmartKit_VISRun(void);
extern int  SmartKit_VISSetGrapBlockMark(int mark);
extern int  SmartKit_VISGetGrapBlockMark(void);
extern char SmartKit_VISGrabBlock(
                char color, 
                int blockNum, 
                float r);
extern char SmartKit_VISPlaceBlock(char color);

#endif /* SmartKit_H */
