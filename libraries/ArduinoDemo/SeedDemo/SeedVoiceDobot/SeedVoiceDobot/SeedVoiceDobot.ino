/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-3-21
** Version:             V1.1.1
** Descriptions:        
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <SoftwareSerial.h>
#include <Magician.h>

#define SOFTSERIAL_RX_PIN  A11                                                        //connect to the A11 pin                                                   
#define SOFTSERIAL_TX_PIN  14                                                         //connect to the 14 pin

SoftwareSerial softSerial(SOFTSERIAL_RX_PIN,SOFTSERIAL_TX_PIN);

const char *voiceBuffer[] =
{
    "Turn on the light",                                                              //return 1
    "Turn off the light",                                                             //return 2
    "Play music",                                                                     //return 3
    "Pause",                                                                          //return 4
    "Next",                                                                           //return 5
    "Previous",                                                                       //return 6
    "Up",                                                                             //return 7
    "Down",                                                                           //return 8
    "Turn on the TV",                                                                 //return 9
    "Turn off the TV",                                                                //return 10
    "Increase temperature",                                                           //return 11
    "Decrease temperature",                                                           //return 12
    "What's the time",                                                                //return 13
    "Open the door",                                                                  //return 14
    "Close the door",                                                                 //return 15
    "Left",                                                                           //return 16
    "Right",                                                                          //return 17
    "Stop",                                                                           //return 18
    "Start",                                                                          //return 19
    "Mode 1",                                                                         //return 20
    "Mode 2",                                                                         //return 21
    "Go",                                                                             //return 22
};

void setup()
{
    Serial.begin(115200);
    softSerial.begin(9600);
    Dobot_Init();                                                                     //Dobot initialization
    softSerial.listen();
    Serial.println("ok");
}

void loop()
{
    char cmd;
    if(softSerial.available())
    {
        cmd = softSerial.read();
        switch(cmd)
        {
          case 7:
                Dobot_SetPTPCmd(MOVL_INC,0,0,30,0);                                  //magician moves upward
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 8:
                Dobot_SetPTPCmd(MOVL_INC,0,0,-30,0);                                 //magician moves downward
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 16:
                Dobot_SetPTPCmd(MOVL_INC,0,30,0,0);                                  //magician turns left
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 17:
                Dobot_SetPTPCmd(MOVL_INC,0,-30,0,0);                                 //magician turns right
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 18:
                Dobot_SetEndEffectorSuctionCup(false);                               //turn off the air pump
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 19:
                Dobot_SetEndEffectorSuctionCup(true);                                //turn on the air pump
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 20:
                Dobot_SetPTPCmd(MOVL_INC,30,0,0,0);                                  //magician moves forward
                Serial.println(voiceBuffer[cmd - 1]);
                break;
          case 21:
                Dobot_SetPTPCmd(MOVL_INC,-30,0,0,0);                                 //magician moves backward
                Serial.println(voiceBuffer[cmd - 1]);
                break;
        }
    }
}
