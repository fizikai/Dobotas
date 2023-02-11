 /****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-06
** Version:             V2.0.0
** Descriptions:        Adjust the brightness of LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include"SmartKit.h"

void setup() {
    Serial.begin(115200);
    SmartKit_Init();
    Serial.println("SmartKit Init...");
}

void loop() {
    int value;
    double xValueTOAnalogScale = 1023/255;
    value = SmartKit_JoyStickReadXYValue(AXISX);
    value = value / xValueTOAnalogScale;
    analogWrite(LED_REDPIN, value);
}
