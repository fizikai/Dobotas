/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            Led.h
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
#ifndef Led_H
#define Led_H

#include "Arduino.h"

class LED
{
public:
    void Init(int redPin,           /* Led 初始化 */
                 int bluePin, 
                 int greenPin);
    int CheckState(int color);      /* 检测各颜色灯的状态 */
    int Turn(int color, int state); /* 开关各颜色灯 */
private:
    int gRedPin;                       /* 红色灯连接引脚 */
    int gBluePin;                      /* 蓝色灯连接引脚 */
    int gGreenPin;                     /* 绿色灯连接引脚 */
};

#endif /* Led_H */
