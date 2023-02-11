
/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:      2019-06-05
** Version:             V2.0.0
** Descriptions:       voice to control dobot magician 
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup() {
    Serial.begin(115200);
    Dobot_Init();                                         //Initial Dobot
    SmartKit_VoiceCNInit();
    SmartKit_Init();
    SmartKit_VoiceCNAddCommand("shang sheng",0);                    //Add command (Command label (repeatable))
    SmartKit_VoiceCNAddCommand("shang",0);
    SmartKit_VoiceCNAddCommand("sheng",0);
    SmartKit_VoiceCNAddCommand("xia jiang",1);
    SmartKit_VoiceCNAddCommand("xia",1);
    SmartKit_VoiceCNAddCommand("jiang",1);
    SmartKit_VoiceCNAddCommand("zuo yi",2);
    SmartKit_VoiceCNAddCommand("zuo",2);
    SmartKit_VoiceCNAddCommand("you zhuan",3);
    SmartKit_VoiceCNAddCommand("you",3);
    SmartKit_VoiceCNAddCommand("qian jin",4);
    SmartKit_VoiceCNAddCommand("qian",4);
    SmartKit_VoiceCNAddCommand("hou tui",5);
    SmartKit_VoiceCNAddCommand("hou",5);
    SmartKit_VoiceCNAddCommand("da kai qi beng",6);
    SmartKit_VoiceCNAddCommand("guan bi qi beng",7);
    /**************************************************
     *The instructions to be identified here are added*
     **************************************************/
    SmartKit_VoiceCNStart();                                        //Start to recognize
    Serial.println("start！");
}

void loop() {

    if (SmartKit_VoiceCNVoiceCheck(0) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, 0, 0, 30, 0);             //Dobot Magician moves up 30mm
        Serial.println("up");
    }
    else if (SmartKit_VoiceCNVoiceCheck(1) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, 0, 0, -30, 0);            //Dobot Magician moves down 30mm
        Serial.println("down");
    }
    else if (SmartKit_VoiceCNVoiceCheck(2) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, 0, 30, 0, 0);             //Dobot Magician turns left 30mm
        Serial.println("turn left");
    }
    else if (SmartKit_VoiceCNVoiceCheck(3) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, 0, -30, 0, 0);            //Dobot Magician turns right 30mm
        Serial.println("turn right");
    }
    else if (SmartKit_VoiceCNVoiceCheck(4) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, 30, 0, 0, 0);             //Dobot Magician moves forward 30mm
        Serial.println("forward");
    }
    else if (SmartKit_VoiceCNVoiceCheck(5) == TRUE)
    {
        Dobot_SetPTPCmd(MOVL_INC, -30, 0, 0, 0);            //Dobot Magician moves backward 30mm
        Serial.println("backward");
    }
    else if (SmartKit_VoiceCNVoiceCheck(6) == TRUE)
    {
        Dobot_SetEndEffectorSuctionCup(true);           //Turn on thr air pump
        Serial.println("Turn on thr air pump");
    }
    else if (SmartKit_VoiceCNVoiceCheck(7) == TRUE)
    {
        Dobot_SetEndEffectorSuctionCup(false);          //Turn off the air pump
        Serial.println("Turn off the air pump");
    }
}



