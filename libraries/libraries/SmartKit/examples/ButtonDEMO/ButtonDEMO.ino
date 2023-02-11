/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        button control LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup() {
    Serial.begin(115200);
    SmartKit_Init();
    Serial.println("SmartKit Init...");
}

void loop(){
    int color = 0;
    
    color = RED;
    if (SmartKit_ButtonCheckState(color) == TRUE)
    {
        SmartKit_LedTurn(color, ON);
    }
    else
    {
        SmartKit_LedTurn(color, OFF);
    }

    color = GREEN;
    if (SmartKit_ButtonCheckState(color) == TRUE)
    {
        SmartKit_LedTurn(color, ON);
    }
    else
    {
        SmartKit_LedTurn(color, OFF);
    }

    color = BLUE;
    if (SmartKit_ButtonCheckState(color) == TRUE)
    {
        SmartKit_LedTurn(color, ON);
    }
    else
    {
        SmartKit_LedTurn(color, OFF);
    }
}
