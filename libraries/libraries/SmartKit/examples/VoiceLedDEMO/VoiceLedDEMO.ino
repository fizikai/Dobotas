/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        voice control LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup() {
    Serial.begin(115200);
    SmartKit_VoiceCNInit();
    SmartKit_Init();                                                                //Start to recognize
    SmartKit_VoiceCNAddCommand("kai hong deng", 0);                                 //Add command��command label (repeatable)��
    SmartKit_VoiceCNAddCommand("kai lv deng", 1);
    SmartKit_VoiceCNAddCommand("kai lan deng", 2);
    SmartKit_VoiceCNAddCommand("guan hong deng", 3);
    SmartKit_VoiceCNAddCommand("guan lv deng", 4);
    SmartKit_VoiceCNAddCommand("guan lan deng", 5);
    SmartKit_VoiceCNAddCommand("kai deng", 6);
    SmartKit_VoiceCNAddCommand("guan deng", 7);
    SmartKit_VoiceCNStart();
    Serial.println("SmartKit Init");
}

void loop() {
    if (SmartKit_VoiceCNVoiceCheck(0) == TRUE)
    {
        SmartKit_LedTurn(RED, HIGH);                                                //turn on the Red_LED
        Serial.println("turn on the red LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(1) == TRUE)
    {
        SmartKit_LedTurn(GREEN, HIGH);                                              //turn on the Green_LED
        Serial.println("turn on the green LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(2) == TRUE)
    {
        SmartKit_LedTurn(BLUE, HIGH);                                               //turn on the Blue_LED
        Serial.println("turn on the blue LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(3) == TRUE)
    {
        SmartKit_LedTurn(RED, LOW);                                                 //turn off the Red_LED
        Serial.println("turn off the red LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(4) == TRUE)
    {
        SmartKit_LedTurn(GREEN, LOW);                                               //turn off the Green_LED
        Serial.println("turn off the green LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(5) == TRUE)
    {
        SmartKit_LedTurn(BLUE, LOW);                                                //turn off the Blue_LED
        Serial.println("turn off the blue LED");
    }
    else if (SmartKit_VoiceCNVoiceCheck(6) == TRUE)
    {
        SmartKit_LedTurn(RED, HIGH);                                                //turn on the Red_LED
        SmartKit_LedTurn(GREEN, HIGH);                                              //turn on the Green_LED
        SmartKit_LedTurn(BLUE, HIGH);                                               //turn on the Blue_LED
        Serial.println("turn on the all light");
    }
    else if (SmartKit_VoiceCNVoiceCheck(7) == TRUE)
    {
        SmartKit_LedTurn(RED, LOW);                                                  //turn off the Red_LED
        SmartKit_LedTurn(GREEN, LOW);                                                //turn off the Green_LED
        SmartKit_LedTurn(BLUE, LOW);                                                 //turn off the Blue_LED
        Serial.println("turn off the all light");
    }
}


