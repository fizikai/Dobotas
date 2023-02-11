/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        flicker LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup(){
    Serial.begin(115200);
    SmartKit_Init();
    Serial.println("SmartKit Init...");
}


void loop(){
    SmartKit_LedTurn(RED, ON);
    delay(500);
    SmartKit_LedTurn(RED, OFF);
    delay(500);
}

