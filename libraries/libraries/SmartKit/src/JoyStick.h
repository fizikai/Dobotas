/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            JoyStick.h
** Latest modified date: 2019-05-15
** Latest version:       V1.0.0
** Description:          SmartKit JoyStick API
**
**------------------------------------------------------------
** Created by:
** Created date:         2019-05-15
** Version:              V1.0.0
** Descriptions:         SmartKit JoyStick API
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#ifndef JoyStick_H
#define JoyStick_H

#include "Arduino.h"

class JOYSTICK
{
public:
    int Init(int joyStickPinX,  /* JoyStick 初始化 */
             int joyStickPinY,  
             int joyStickPinZ); 
    int ReadXYValue(int axis);  /* 读取X,Y轴的模拟量 */
    int CheckPressState(void);  /* 检查摇杆按下状态 */
private:
    int gJoyStickPinX;          /* 摇杆X轴引脚 */
    int gJoyStickPinY;          /* 摇杆Y轴引脚 */
    int gJoyStickPinZ;          /* 摇杆Z轴引脚 */
};

#endif /* JoyStick_H */

