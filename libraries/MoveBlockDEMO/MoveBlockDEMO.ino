/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        Move Blocks
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <Magician.h>
int count = 3;

//Coordinates of A point
#define block_position_X 254                            //X-coordinate of A point
#define block_position_Y -2                             //Y-coordinate of A point
#define block_position_Z -42                            //Z-coordinate of A point
#define block_position_R 0                              //R-coordinate of A point

//Coordinates of B point
#define Des_position_X 170                              //X-coordinate of B point
#define Des_position_Y -190                             //Y-coordinate of B point 
#define Des_position_Z -42                              //Z-coordinate of B point
#define Des_position_R 0                                //R-coordinate of B point

void setup() 
{
  Serial.begin(115200);
  Dobot_Init();
  Serial.println("start...");
  Dobot_SetPTPCmd(MOVJ_XYZ, 230, 0, 40, 0);
}

void loop() 
{
  while(count > 0)
  {
    Dobot_SetPTPCmd(JUMP_XYZ, block_position_X, block_position_Y, block_position_Z, block_position_R);  //Move to point A
    Dobot_SetEndEffectorSuctionCup(true);                                                               //Turn on air pump to pick up cube
    Dobot_SetPTPCmd(MOVL_XYZ, block_position_X, block_position_Y, -4, block_position_R);                //Lift a certain height                                            
    Dobot_SetPTPCmd(JUMP_XYZ, Des_position_X, Des_position_Y, Des_position_Z, Des_position_R);          //Move to point B
    Dobot_SetEndEffectorSuctionCup(false);                                                              //Turn off air pump to place cube
    Dobot_SetPTPCmd(MOVL_XYZ, Des_position_X, Des_position_Y, -20, Des_position_R);                     //Lift a certain height
    Dobot_SetPTPCmd(MOVJ_XYZ, 230, -4, 40, 0);                                                          //Move back to the initial position
    
    delay(500);
    Dobot_SetPTPCmd(JUMP_XYZ, Des_position_X, Des_position_Y, Des_position_Z, Des_position_R);          //Move to point B                                              
    Dobot_SetEndEffectorSuctionCup(true);                                                               //Turn on air pump to pick up cube
    Dobot_SetPTPCmd(MOVL_XYZ, Des_position_X, Des_position_Y, -10, Des_position_R);                     //Lift a certain height
    Dobot_SetPTPCmd(JUMP_XYZ, block_position_X, block_position_Y, block_position_Z, block_position_R);  //Move to point A
    Dobot_SetEndEffectorSuctionCup(false);                                                              //Turn off air pump to place cube
    Dobot_SetPTPCmd(MOVJ_XYZ, 230, -4, 40, 0);                                                          //Move back to the initial position
    count--;
  }
}
