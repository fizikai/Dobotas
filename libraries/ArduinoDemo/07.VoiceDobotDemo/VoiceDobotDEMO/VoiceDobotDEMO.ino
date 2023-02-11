/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:      2019-1-24
** Version:             V1.1.1
** Descriptions:       voice to control dobot magician 
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <Magician.h>
#include <VoiceRecognition.h>

VoiceRecognition Voice;                                   //Structural variable
void setup() 
{
    Serial.begin(115200);
    Dobot_Init();                                         //Initial Dobot
    Voice.init();                                         //Initial VoiceRecognition
    Voice.addCommand("shang sheng",0);                    //Add command (Command label (repeatable))                                              
    Voice.addCommand("xia jiang",1);                                                                      
    Voice.addCommand("zuo yi",2);                                                  
    Voice.addCommand("you yi",3);                                             
    Voice.addCommand("xiang qian",4);                                               
    Voice.addCommand("xiang hou",5);                                                 
    Voice.addCommand("da kai qi beng",6);   
    Voice.addCommand("guan bi qi beng",7);            
    /**************************************************     
     *The instructions to be identified here are added*
     **************************************************/
    Voice.start();                                        //Start to recognize
    Serial.println("start！");  
}

void loop() 
{
  switch(Voice.read())                                   //Check rcognition contengs
  {
    case 0:                                               
        Dobot_SetPTPCmd(MOVL_INC,0,0,30,0);             //Dobot Magician moves up 30mm
        Serial.println("up");
        break;
    case 1:                                               
        Dobot_SetPTPCmd(MOVL_INC,0,0,-30,0);            //Dobot Magician moves down 30mm
        Serial.println("down");
        break;   
    case 2:                                               
        Dobot_SetPTPCmd(MOVL_INC,0,30,0,0);             //Dobot Magician turns left 30mm
        Serial.println("turn left");
        break;   
    case 3:                                               
        Dobot_SetPTPCmd(MOVL_INC,0,-30,0,0);            //Dobot Magician turns right 30mm
        Serial.println("turn right");
        break;   
    case 4:                                               
        Dobot_SetPTPCmd(MOVL_INC,30,0,0,0);             //Dobot Magician moves forward 30mm
        Serial.println("forward");
        break;   
    case 5:                                               
        Dobot_SetPTPCmd(MOVL_INC,-30,0,0,0);            //Dobot Magician moves backward 30mm
        Serial.println("backward");
        break;   
    case 6:                                               
        Dobot_SetEndEffectorSuctionCup(true);           //Turn on thr air pump
        Serial.println("Turn on thr air pump");
        break;  
    case 7:                                               
        Dobot_SetEndEffectorSuctionCup(false);          //Turn off the air pump
        Serial.println("Turn off the air pump");
        break; 
     default:
        Serial.println("Error");
        break;
     /*********************************************     
     *The actions corresponding to the instructions 
     that need to be identified are added here*
     **********************************************/
  }
  delay(100);
}
