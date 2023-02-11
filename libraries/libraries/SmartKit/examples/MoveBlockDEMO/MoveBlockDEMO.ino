/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        Move Blocks
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"


//Coordinates of A point
#define block_position_X 263                                                                            //X-coordinate of A point
#define block_position_Y 3                                                                              //Y-coordinate of A point
#define block_position_Z -40                                                                            //Z-coordinate of A point
#define block_position_R 0                                                                              //R-coordinate of A point

//Coordinates of B point
#define Des_position_X 207                                                                              //X-coordinate of B point
#define Des_position_Y -171                                                                             //Y-coordinate of B point 
#define Des_position_Z -46                                                                              //Z-coordinate of B point
#define Des_position_R 0                                                                                //R-coordinate of B point

void setup() {
    Serial.begin(115200);
    Dobot_Init();
    Serial.println("start...");
    Dobot_SetPTPCmd(MOVJ_XYZ, 178, -4, 40, 0);
}

int count = 4;

void loop() {
    while (count > 0)
    {
        Dobot_SetPTPCmd(JUMP_XYZ, block_position_X, block_position_Y, block_position_Z, block_position_R);  //Move to point A
        Dobot_SetEndEffectorSuctionCup(true);                                                               //Turn on air pump to pick up cube
        Dobot_SetPTPCmd(MOVL_XYZ, block_position_X, block_position_Y, -4, block_position_R);                //Lift a certain height                                            
        Dobot_SetPTPCmd(JUMP_XYZ, Des_position_X, Des_position_Y, Des_position_Z, Des_position_R);          //Move to point B
        Dobot_SetEndEffectorSuctionCup(false);                                                              //Turn off air pump to place cube
        Dobot_SetPTPCmd(MOVL_XYZ, Des_position_X, Des_position_Y, -20, Des_position_R);                     //Lift a certain height
        Dobot_SetPTPCmd(MOVJ_XYZ, 178, -4, 40, 0);                                                          //Move back to the initial position
        Dobot_SetPTPCmd(JUMP_XYZ, Des_position_X, Des_position_Y, Des_position_Z, Des_position_R);          //Move to point B                                              
        Dobot_SetEndEffectorSuctionCup(true);                                                               //Turn on air pump to pick up cube
        Dobot_SetPTPCmd(MOVL_XYZ, Des_position_X, Des_position_Y, -10, Des_position_R);                     //Lift a certain height
        Dobot_SetPTPCmd(JUMP_XYZ, block_position_X, block_position_Y, block_position_Z, block_position_R);  //Move to point A
        Dobot_SetEndEffectorSuctionCup(false);                                                              //Turn off air pump to place cube
        Dobot_SetPTPCmd(MOVJ_XYZ, 178, -4, 40, 0);                                                          //Move back to the initial position
        count--;
    }
}
