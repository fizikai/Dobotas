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
#include "Led.h"
#include "SmartKitType.h"

/*************************************************************
** Function name:	  LedInit
** Descriptions:	  led初始化
** Output parameters: redPin:   红色灯连接引脚
**                    bluePin:  蓝色灯连接引脚
**                    greenPin: 绿色灯连接引脚
** Input parameters:  no
** Returned value:	  no
*************************************************************/

void LED::Init(int redPin, 
                  int bluePin, 
                  int greenPin)
{
    gRedPin = redPin;
    gBluePin = bluePin;
    gGreenPin = greenPin;
    pinMode(gRedPin, OUTPUT);
    pinMode(gBluePin, OUTPUT);
    pinMode(gGreenPin, OUTPUT);
}

/*************************************************************
** Function name:	  CheckLedState
** Descriptions:	  检测LED的状态
** Input parameters:  color: led灯的颜色，
**                           可传递值BLUE,GREEN,RED
** Output parameters: no
** Returned value:	  led的状态 ON或OFF
*************************************************************/

int LED::CheckState(int color)
{
    int statu = 0;
    switch (color)
    {
    case BLUE:
        statu = digitalRead(gBluePin);
        break;

    case GREEN:
        statu = digitalRead(gGreenPin);
        break;

    case RED:
        statu = digitalRead(gRedPin);
        break;

    default:
        return 0;
    }
    return statu;
}

/*************************************************************
** Function name:	  TurnLed
** Descriptions:	  开关LED
** Input parameters:  color: led灯的颜色，
**                           可传递值BLUE,GREEN,RED
**					  state: led灯的状态，
**                           可传递值ON,OFF
** Output parameters: no
** Returned value:	  摇杆的数值
*************************************************************/

int LED::Turn(int color, int state)
{
    switch (color)
    {
    case BLUE:
        digitalWrite(gBluePin, state);
        break;

    case GREEN:
        digitalWrite(gGreenPin, state);
        break;

    case RED:
        digitalWrite(gRedPin, state);
        break;

    default:
        return TRUE;
    }
    return FALSE;
}




