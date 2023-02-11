/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        JoyStick to control Dobot Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <Magician.h>

#define JoyStick_X  A7                                              //JoyStick_X connects to the A7 pin
#define JoyStick_Y  A6                                              //JoyStick_Y connects to the A6 pin
#define JoyStick_Z  A5                                              //JoyStick_Z connects to the A5 pin
#define Red_Button  A0                                              //Red_button connects to the A0 pin
#define Green_Button A2                                             //Green_button connects to the A2 pin
#define Blue_Button A4                                              //Blue_button connects to the A4 pin
                                   
int flag = 0;                                                       //Blue_Button flag
int Zflag = 1;                                                      //JoyStick_Z flag
void setup() 
{
  Dobot_Init();                                                     //Initial Dobot
  pinMode(JoyStick_Z, INPUT); 
  pinMode(Red_Button, INPUT); 
  pinMode(Green_Button, INPUT); 
  pinMode(Blue_Button, INPUT); 
  Serial.begin(115200);                                            // 115200 bps
  Dobot_SetPTPCmd(MOVJ_XYZ, 230, 0, 40, 0);                        //  设置机械臂初始位置
  Serial.println("OK");
}

void loop() 
{
  int x = 0,y = 0,z = 0,b1 = 0,b2 = 0,b3 = 0;
  int direction = 0;                                                //The direction of JoyStick
  x = analogRead(JoyStick_X);
  y = analogRead(JoyStick_Y);
  z = digitalRead(JoyStick_Z);
  b1 = digitalRead(Red_Button);
  b2 = digitalRead(Green_Button);
  b3 = digitalRead(Blue_Button);
  if(y > 600)                                                     //JoyStick moves alongt Y-axis in the positive direction
  {                                                     
    direction = 1; 
  }
  else if(y < 400)                                                //JoyStick moves alongt Y-axis in the negative direction
  {                                                 
    direction = 2;
  }
  else if(x > 600)                                                //JoyStick moves alongt X-axis in the positive direction
  {                                                 
    direction = 3;
  }
  else if(x < 400)                                                //JoyStick moves alongt X-axis in the negative direction
  {                                                 
    direction = 4;
  }
  else if(b1 == 1)                                                //press Red_Button
  {                                                 
    direction = 5;
  }
  else if(b2 == 1)                                                //press Green_Button
  {                                                 
    direction = 6;
  }
  else if(b3 == 1)                                                //press Blue_Button
  {                                                 
    direction = 7;
  }
  else if(z == 0)                                                 //press JoyStick
  {                                                  
    direction = 8;
  }
  switch(direction)
  {
    case 1:
        Serial.println("forward");
        Dobot_SetPTPCmd(MOVL_INC,20,0,0,0);                       //Dobot Magician moves forward
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 2:
        Serial.println("backward");
        Dobot_SetPTPCmd(MOVL_INC,-20,0,0,0);                      //Dobot Magician moves backward
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 3:
        Serial.println("right");
        Dobot_SetPTPCmd(MOVL_INC,0,-20,0,0);                      //Dobot Magician turns right
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 4:
        Serial.println("left");
        Dobot_SetPTPCmd(MOVL_INC,0,20,0,0);                       //Dobot Magician turns left
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 5:
        Serial.println("down");
        Dobot_SetPTPCmd(MOVL_INC,0,0,-20,0);                      //Dobot Magician moves down
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
   case 6:
        Serial.println("up");
        Dobot_SetPTPCmd(MOVL_INC,0,0,20,0);                       //Dobot Magician moves up
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 7:
            if(flag)                                      //whether Blue_Button the first time is pressed
            {                                            
              Dobot_SetEndEffectorSuctionCup(false);
              Serial.println("Turn off the air pump");
              flag = !flag;
            }
            else
            {
              Dobot_SetEndEffectorSuctionCup(true);
              Serial.println("Turn on thr air pump");
              flag = !flag;
            }
        break;
    case 8:
            if(Zflag)                                   //whether JoyStick the first time is pressed
            {                                            
              Dobot_SetPTPCommonParams(100,100);
              Serial.println("Accelerate");
              Zflag = !Zflag;
            }
            else
            {
              Dobot_SetPTPCommonParams(20,20);
              Serial.println("Decelerate");
              Zflag = !Zflag;
            }
        break;
  }
  delay(100);
}
