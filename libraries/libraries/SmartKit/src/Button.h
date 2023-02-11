/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            Button.h
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
#ifndef Button_H
#define Button_H

#include "Arduino.h"

class BUTTON
{
public:
    void Init(int redPin,        /* Button初始化 */
                    int bluePin,
                    int greenPin);
    int CheckState(int color);   /* 检测Button状态 */
private:

    int gRedPin;                 /* 红色按钮连接引脚 */
    int gBluePin;                /* 蓝色按钮连接引脚 */
    int gGreenPin;               /* 绿色按钮连接引脚 */

    int ReadState(int button, int ioDown);
};

#endif /* Button_H */
