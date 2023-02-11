/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            Button.cpp
** Latest modified date: 2019-05-15
** Latest version:       V1.0.0
** Description:          SmartKit Button API
**
**------------------------------------------------------------
** Created by:
** Created date:         2019-05-15
** Version:              V1.0.0
** Descriptions:         SmartKit Button API
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "Button.h"
#include "SmartKitType.h"

/*************************************************************
** Function name:	  ButtonInit
** Descriptions:	  按键初始化
** Input parameters:  redPin:   红色按钮连接引脚
**                    bluePin:  蓝色按钮连接引脚
**                    greenPin: 绿色按钮连接引脚
** Output parameters: no
** Returned value:	  no
*************************************************************/

void BUTTON::Init(int redPin,
                  int bluePin,
                  int greenPin)
{
    gRedPin = redPin;
    gBluePin = bluePin;
    gGreenPin = greenPin;
    pinMode(gRedPin, INPUT);
    pinMode(gGreenPin, INPUT);
    pinMode(gBluePin, INPUT);
}

/*************************************************************
** Function name:	  ReadButtonState
** Descriptions:	  读取按键状态，默认是UP状态
** Output parameters: button: 需要读取的按键
**					  ioDown: 默认按下的IO状态
** Input parameters:  no
** Returned value:	  返回按键状态，UP或DOWN
*************************************************************/

int BUTTON::ReadState(int button, int ioDown)
{
    if (digitalRead(button) == ioDown)
    {
        delay(10);							/* 按键防抖处理 */
        if (digitalRead(button) == ioDown)
        {
            return DOWN;
        }
    }
    else
    {
        return UP;
    }
}

/*************************************************************
** Function name:	  CheckButtonState
** Descriptions:	  检查按键状态
** Input parameters:  color: 按键的颜色，
**                           可传递值BLUE,GREEN,RED
** Output parameters: no
** Returned value:	  返回按键状态，UP或DOWN
*************************************************************/

int BUTTON::CheckState(int color)
{
    int down = 1;
    int statu = UP;
    switch (color)
    {
    case BLUE:
        statu = ReadState(gBluePin, down);
        break;

    case GREEN:
        statu = ReadState(gGreenPin, down);
        break;

    case RED:
        statu = ReadState(gRedPin, down);
        break;

    default:
        return UP;
    }
    return statu;
}

