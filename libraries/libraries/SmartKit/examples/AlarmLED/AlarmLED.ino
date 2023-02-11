/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        AlarmLED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup() {
    SmartKit_Init();
    SmartKit_LedTurn(RED, OFF);    //关闭LED指示灯
    SmartKit_LedTurn(BLUE, OFF);
    SmartKit_LedTurn(GREEN, OFF);
}

void loop() {
    SmartKit_LedTurn(RED, ON);
    delay(300);
    SmartKit_LedTurn(RED, OFF);
    SmartKit_LedTurn(GREEN, ON);
    delay(300);
    SmartKit_LedTurn(GREEN, OFF);
    SmartKit_LedTurn(BLUE, ON);
    delay(300);
    SmartKit_LedTurn(BLUE, OFF);
}
