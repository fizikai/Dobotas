/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-03-21
** Version:             V1.1.1
** Descriptions:        Visual recognition for DOBOT Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <Magician.h>
#include "Pixy2I2C.h"

// Point position coordinate
#define Red_position_X 201                                                                // X-coordinate of red cube that is to be placed     
#define Red_position_Y -200                                                               // Y-coordinate of red cube that is to be placed   
#define Red_position_Z -42                                                                // Z-coordinate of red cube that is to be placed   
#define Red_position_R 0                                                                  // R-coordinate of red cube that is to be placed      

#define Green_position_X 156                                                              // X-coordinate of green cube that is to be placed        
#define Green_position_Y -200                                                             // Y-coordinate of green cube that is to be placed        
#define Green_position_Z -42                                                              // Z-coordinate of green cube that is to be placed        
#define Green_position_R 0                                                                // R-coordinate of green cube that is to be placed        

#define Blue_position_X 111                                                               // X-coordinate of blue cube that is to be placed     
#define Blue_position_Y -201                                                              // Y-coordinate of blue cube that is to be placed
#define Blue_position_Z -42                                                               // Z-coordinate of blue cube that is to be placed
#define Blue_position_R 0                                                                 // R-coordinate of blue cube that is to be placed

#define Yellow_position_X 70                                                              // X-coordinate of yellow cube that is to be placed     
#define Yellow_position_Y -200                                                            // Y-coordinate of yellow cube that is to be placed
#define Yellow_position_Z -42                                                             // Z-coordinate of yellow cube that is to be placed
#define Yellow_position_R 0                                                               // R-coordinate of yellow cube that is to be placed

Pixy2I2C pixy;                                        // Pixy object

uint16_t blocks,signature,width,height;
int gRed = 0, gGreen = 0, gBlue = 0, gYellow = 0;      // blocks count

float dobotPoint[9] =         //the coordinates of three blocks for Magician
{                              
   232.39,  273,  228.4,
   0.05,   -21.7, -43.9,
   1, 1, 1
};

float pixyPoint[9] =         //the coordinates of three blocks for Pixy
{                               
   225, 181,  114,
   45, 147.5, 47,
   1, 1, 1
};

float RT[9] =                //basis matrix
{                                      
   0, 0, 0,
   0, 0, 0,
   0, 0, 0
};

float Coordinate[2] = {0};                            //The X and Y coordinates of the target block
void CalcInvMat(float *Mat, float *InvMat)            //Inverse matrix
{
    int i = 0;
    double Det = 0.0;
    Det = Mat[0] * (Mat[4] * Mat[8] - Mat[5] * Mat[7]) - Mat[3] * (Mat[1] * Mat[8] - Mat[2] * Mat[7]) + Mat[6] * (Mat[1] * Mat[5] - Mat[2] * Mat[4]);
    InvMat[0] = Mat[4] * Mat[8] - Mat[5] * Mat[7];
    InvMat[1] = Mat[2] * Mat[7] - Mat[1] * Mat[8];
    InvMat[2] = Mat[1] * Mat[5] - Mat[2] * Mat[4];
    InvMat[3] = Mat[5] * Mat[6] - Mat[3] * Mat[8];
    InvMat[4] = Mat[0] * Mat[8] - Mat[2] * Mat[6];
    InvMat[5] = Mat[3] * Mat[2] - Mat[0] * Mat[5];
    InvMat[6] = Mat[3] * Mat[7] - Mat[4] * Mat[6];
    InvMat[7] = Mat[1] * Mat[6] - Mat[7] * Mat[0];
    InvMat[8] = Mat[0] * Mat[4] - Mat[3] * Mat[1];
    for (i = 0; i < 9; i++) 
    {
        InvMat[i] = InvMat[i] / Det;
    }
}

void MatMultiMat(float *Mat1, float *Mat2, float *Result)    //matrix multiplication，A^-1*A*RT = A^-1*B => RT = A^-1*B
{
    int i = 0;
    int j = 0;
    int k = 0;
    int Value = 0;
    for (i = 0; i < 9; i++) 
    {
        Result[i] = 0;
    }
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 3; k++) 
            {
                Result[i * 3 + j] += Mat1[i * 3 + k] * Mat2[k * 3 + j];
            }
        }
    }
}

void transForm(float x, float y) 
{                                                         
   Coordinate[0] = (RT[0] * x) + (RT[1] * y) + (RT[2] * 1);
   Coordinate[1] = (RT[3] * x) + (RT[4] * y) + (RT[5] * 1);
}

void setup()
{ 
  Serial.begin(115200);
  Dobot_Init();                
  Serial.print("Dobot Init\n");
  pixy.init();                 
  Serial.print("Pixy Init\n");
  
  Dobot_SetPTPJumpParams(20);              //Set up the maximum height of the magician lift
  float inv_pixy[9] =                      //Initialization inverse matrix
  {                                 
     0, 0, 0,
     0, 0, 0,
     0, 0, 0
  };
  CalcInvMat(pixyPoint, inv_pixy);
  MatMultiMat(dobotPoint, inv_pixy, RT);
  Dobot_SetPTPCommonParams(100,100);
  Serial.print("Finally\n");
}

void loop() 
{
    Dobot_SetPTPCmd(MOVJ_XYZ, 228, -26, 28, 0);     // Set the camera position 
    Serial.print("Starting...\n");
    pixy.ccc.getBlocks();                           // get the numbers of blocks
    delay(10);
    pixy.ccc.getBlocks();
    delay(10);
    pixy.ccc.getBlocks();
    delay(10);            
    blocks = pixy.ccc.numBlocks;
    Serial.print("Number of blocks: ");
    Serial.println(blocks);
    delay(200);

    if(pixy.ccc.numBlocks == 0)
    {
       Dobot_SetPTPCmd(MOVJ_XYZ, 228, -26, 28, 0);   // Initialization position
       return 0;
    }
    if (blocks)
    {
       transForm(pixy.ccc.blocks[0].m_x, pixy.ccc.blocks[0].m_y); 
       signature = pixy.ccc.blocks[0].m_signature;
       width     = pixy.ccc.blocks[0].m_width;
       height    = pixy.ccc.blocks[0].m_height;
       Serial.print(Coordinate[0]);
       Serial.print("  ");
       Serial.println(Coordinate[1]);
       Serial.print("width= ");
       Serial.println(width);
       Serial.print("height= ");
       Serial.println(height);
       Serial.print("signature= ");
       Serial.println(signature);
       Serial.print("\n");
       
      switch(signature) 
      {
        case 1:
              if((width > 20) || (height > 20))                                                                                  // Exclude the error pixel point
              {
                 printf("1_red\n");
                 //suck Point
                 Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                // The position of a target object
                 Dobot_SetEndEffectorSuctionCup(true);                                                                           // Turn on air pump
                 Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);       
                 //place Point
                 if(gRed == 0)
                 {
                      Dobot_SetPTPCmd(JUMP_XYZ, Red_position_X, Red_position_Y, Red_position_Z, Red_position_R);                 // Move to the setting position
                 }
                 else
                 {
                      Dobot_SetPTPCmd(JUMP_XYZ, Red_position_X, Red_position_Y, Red_position_Z + 25*gRed, Red_position_R);       // Multiple cubes are piled when placing
                 }
                Dobot_SetEndEffectorSuctionCup(false);                                                                           // Turn off air pump
                Dobot_SetPTPCmd(JUMP_XYZ, Red_position_X, Red_position_Y, 100, 0);                                               // Lift to a certain height
                gRed++;
                Serial.print("gRed:"); 
                Serial.println(gRed);                                                                                           // The number of the red block
                break;
              }
              else
                break;
         case 2:
             if((width > 20) || (height > 20))                                                                                   // Exclude the error pixel point
              {
                 printf("2_green\n");
                 //suck Point
                 Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                  // The position of a target object
                 Dobot_SetEndEffectorSuctionCup(true);                                                                             // Turn on air pump
                 Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);       
                 //place Point
                 if(gGreen == 0)
                 {
                    Dobot_SetPTPCmd(JUMP_XYZ, Green_position_X, Green_position_Y, Green_position_Z, Green_position_R);             // Move to the setting position
                 }
                 else
                 {
                    Dobot_SetPTPCmd(JUMP_XYZ, Green_position_X, Green_position_Y, Green_position_Z + 25*gGreen, Green_position_R); // Multiple cubes are piled when placing
                 }
                Dobot_SetEndEffectorSuctionCup(false);                                                                             // Turn off air pump
                Dobot_SetPTPCmd(JUMP_XYZ, Green_position_X, Green_position_Y, 100, 0);                                             // Lift to a certain height
                gGreen++;
                Serial.print("gGreen:"); 
                Serial.println(gGreen);                                                                                           // The number of the green block
                break;
              }
              else
                break;
        case 3:
              if((width > 20) || (height > 20))                                                                                    // Exclude the error pixel point
              {
                 printf("3_blue\n");
                 //suck Point
                 Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                 // The position of a target object
                 Dobot_SetEndEffectorSuctionCup(true);                                                                            // Turn on air pump
                 Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);       
                 //place Point
                 if(gBlue == 0)
                 {
                      Dobot_SetPTPCmd(JUMP_XYZ, Blue_position_X, Blue_position_Y, Blue_position_Z, Blue_position_R);              // Move to the setting position
                 }
                 else
                 {
                      Dobot_SetPTPCmd(JUMP_XYZ, Blue_position_X, Blue_position_Y, Blue_position_Z + 25*gBlue, Blue_position_R);   // Multiple cubes are piled when placing
                 }
                Dobot_SetEndEffectorSuctionCup(false);                                                                            // Turn off air pump
                Dobot_SetPTPCmd(JUMP_XYZ, Blue_position_X, Blue_position_Y, 100, 0);                                              // Lift to a certain height
                gBlue++;
                Serial.print("gBlue:"); 
                Serial.println(gBlue);                                                                                           // The number of the blue block
                break;
              }
              else
                break;
        case 4:
              if((width > 20) || (height > 20))                                                                                          // Exclude the error pixel point
              {
                 printf("4_yellow\n");
                 //suck Point
                 Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                        // The position of a target object
                 Dobot_SetEndEffectorSuctionCup(true);                                                                                   // Turn on air pump
                 Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);       
                 //place Point
                 if(gYellow == 0)
                 {
                    Dobot_SetPTPCmd(JUMP_XYZ, Yellow_position_X, Yellow_position_Y, Yellow_position_Z, Yellow_position_R);               // Move to the setting position
                 }
                 else
                 {
                    Dobot_SetPTPCmd(JUMP_XYZ, Yellow_position_X, Yellow_position_Y, Yellow_position_Z + 25*gYellow, Yellow_position_R);  // Multiple cubes are piled when placing
                 }
                Dobot_SetEndEffectorSuctionCup(false);                                                                                   // Turn off air pump
                Dobot_SetPTPCmd(JUMP_XYZ, Yellow_position_X, Yellow_position_Y, 100, 0);                                                 // Lift to a certain height
                gYellow++;
                Serial.print("gYellow:"); 
                Serial.println(gYellow);                                                                                                // The number of the yellow block
                break;
              }
              else
                break;
      }
   }
}
