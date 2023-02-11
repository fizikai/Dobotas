/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        JoyStick to control Dobot Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup() 
{
    Serial.begin(115200);
    Dobot_Init();                   
    SmartKit_Init();
    Serial.println("ok");
}
void loop() 
{
    static int flag = 0;
    static int Zflag = 1;
    int x = 0, y = 0, z = 0, b1 = 0, b2 = 0, b3 = 0;
    int direction = 0;                                                //The direction of JoyStick
    x = SmartKit_JoyStickReadXYValue(AXISX);
    y = SmartKit_JoyStickReadXYValue(AXISY);
    z = SmartKit_JoyStickCheckPressState();
    b1 = SmartKit_ButtonCheckState(RED);
    b2 = SmartKit_ButtonCheckState(GREEN);
    b3 = SmartKit_ButtonCheckState(BLUE);
    if (y > 600){                                                      //JoyStick moves alongt Y-axis in the positive direction
        direction = 1;
    }
    else if (y < 400){                                                 //JoyStick moves alongt Y-axis in the negative direction
        direction = 2;
    }
    else if (x > 600){                                                 //JoyStick moves alongt X-axis in the positive direction
        direction = 3;
    }
    else if (x < 400){                                                 //JoyStick moves alongt X-axis in the negative direction
        direction = 4;
    }
    else if (b1 == 1){                                                 //press Red_Button
        direction = 5;
    }
    else if (b2 == 1){                                                 //press Green_Button
        direction = 6;
    }
    else if (b3 == 1){                                                 //press Blue_Button
        direction = 7;
    }
    else if (z == 0){                                                  //press JoyStick
        direction = 8;
    }
    switch (direction){
    case 1:
        Serial.println("forward");
        Dobot_SetPTPCmd(MOVL_INC, 20, 0, 0, 0);                       //Dobot Magician moves forward
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 2:
        Serial.println("backward");
        Dobot_SetPTPCmd(MOVL_INC, -20, 0, 0, 0);                      //Dobot Magician moves backward
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 3:
        Serial.println("right");
        Dobot_SetPTPCmd(MOVL_INC, 0, -20, 0, 0);                      //Dobot Magician turns right
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 4:
        Serial.println("left");
        Dobot_SetPTPCmd(MOVL_INC, 0, 20, 0, 0);                       //Dobot Magician turns left
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 5:
        Serial.println("down");
        Dobot_SetPTPCmd(MOVL_INC, 0, 0, -20, 0);                       //Dobot Magician moves down
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 6:
        Serial.println("up");
        Dobot_SetPTPCmd(MOVL_INC, 0, 0, 20, 0);                       //Dobot Magician moves up
        Serial.print("x=");
        Serial.println(x);
        Serial.print("y=");
        Serial.println(y);
        break;
    case 7:
        if (flag){                                               //whether Blue_Button the first time is pressed
            Dobot_SetEndEffectorSuctionCup(false);
            Serial.println("Turn off the air pump");
            flag = !flag;
        }
        else{
            Dobot_SetEndEffectorSuctionCup(true);
            Serial.println("Turn on thr air pump");
            flag = !flag;
        }
        break;
    case 8:
        if (Zflag){                                              //whether JoyStick the first time is pressed
            Dobot_SetPTPCommonParams(100, 100);
            Serial.println("Accelerate");
            Zflag = !Zflag;
        }
        else{
            Dobot_SetPTPCommonParams(20, 20);
            Serial.println("Decelerate");
            Zflag = !Zflag;
        }
        break;
    }
    delay(100);
}
