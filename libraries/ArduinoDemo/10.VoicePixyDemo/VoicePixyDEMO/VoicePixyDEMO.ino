/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-3-21
** Version:             V1.1.1
** Descriptions:        Visual recognition for DOBOT Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <VoiceRecognition.h>
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

#define Signature_Red    1
#define Signature_Green  2
#define Signature_Blue   3
#define Signature_Yellow 4

#define Block_Width  30
#define Block_Height 30

#define Red_LED 9                                                                         //Red LED connects to the 9 pin
#define Green_LED A1                                                                      //Green LED connects to the A1 pin
#define Blue_LED A3                                                                       //Blue_LED connects to the A3 pin  
#define Button1 A0                                                                        //Button1 connects to the A0 pin

Pixy2I2C pixy;                                                                           // Pixy object
VoiceRecognition Voice;                                                                   // Structural variable

uint16_t blocks,flag;
uint16_t i;
int gRed = 0,gGreen = 0,gBlue = 0,gYellow = 0;                                            // blocks count

float dobotPoint[9] =        // the coordinates of three blocks for Magician
{                              
   232.39, 273, 228.4,
   0.05,  -21.7, -43.9,
   1, 1, 1
};

float pixyPoint[9] =         // the coordinates of three blocks for Pixy
{                               
   225, 181, 114,
   45, 147.5, 47,
   1, 1, 1
};

float RT[9] =                // basis matrix
{                
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

float Coordinate[2]= {0};                                                                 //The X and Y coordinates of the target block
void CalcInvMat(float *Mat, float *InvMat)                                                //Inverse matrix
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
    for (i = 0; i < 9; i++) {
        InvMat[i] = InvMat[i] / Det;
    }
}

void MatMultiMat(float *Mat1, float *Mat2, float *Result)     //matrix multiplication，A^-1*A*RT = A^-1*B => RT = A^-1*B
{
    int i = 0;
    int j = 0;
    int k = 0;
    int Value = 0;

    for (i = 0; i < 9; i++)
    {
        Result[i] = 0;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                Result[i * 3 + j] += Mat1[i * 3 + k] * Mat2[k * 3 + j];
            }
        }
    }
}

void transForm(float x, float y)                            //A^-1*A*RT = A^-1*B => RT = A^-1*B
{                                                          
  Coordinate[0] = (RT[0] * x) + (RT[1] * y) + (RT[2] * 1);  
  Coordinate[1] = (RT[3] * x) + (RT[4] * y) + (RT[5] * 1);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(Red_LED, OUTPUT);                                                                   //Set the 9 pin to OUTPUT
  pinMode(Green_LED, OUTPUT);                                                                 //Set the A1 pin to OUTPUT
  pinMode(Blue_LED, OUTPUT);                                                                  //Set the A3 pin to OUTPUT
  pinMode(Button1, INPUT);                                                                    //Set the A0 pin to INPUT
  Voice.init();                                                                               //Initial VoiceRecognition
  Serial.print("Voice Init\n");
  Dobot_Init();                                                                              
  Serial.print("Dobot Init\n");
  pixy.init();
  Serial.print("Pixy Init\n");
  
  Dobot_SetPTPJumpParams(20);              // Set up the maximum height of the magician lift
  float inv_pixy[9] =
  {
     0, 0, 0,
     0, 0, 0,
     0, 0, 0
  };
  CalcInvMat(pixyPoint, inv_pixy);
  MatMultiMat(dobotPoint, inv_pixy, RT);
  Dobot_SetPTPCommonParams(100,100);
  
  Voice.addCommand("zhua hong se",1);      // Add command（Command label (repeatable)）
  Voice.addCommand("hong se",1);  
  Voice.addCommand("zhua lv se",2);                          
  Voice.addCommand("lv se",2); 
  Voice.addCommand("zhua lan se",3);                          
  Voice.addCommand("lan se",3);                         
  Voice.addCommand("zhua huang se",4);                          
  Voice.addCommand("huang se",4); 
  /*************************     
   *需要识别的指令在此添加*
  ************************/
  Voice.start();                           // Start to recognize  
  Serial.print("Finally\n");
}

void loop() 
{
   Dobot_SetPTPCmd(MOVJ_XYZ, 228, -26, 28, 0);                       // Set the camera position
   Serial.print("Starting...\n");
    
   int val = digitalRead(Button1);                                   // get A0 Input value
   if(val == HIGH)                                                   // when the RedButton is pressed,the val is HIGH                         
   {
      digitalWrite(Red_LED, HIGH);                                    // turn on the Red_LED
      digitalWrite(Green_LED, HIGH);                                  // turn on the Green_LED
      digitalWrite(Blue_LED, HIGH);                                   // turn on the Blue_LED
      Serial.println("speak"); 
      while(val)                                                      // when val is HIGH,
     {
        val = digitalRead(Button1);
        Serial.println("Waiting...");     
        delay(50);
     }                                                 
      digitalWrite(Red_LED, LOW);                                    // turn off the Red_LED
      digitalWrite(Green_LED, LOW);                                  // turn off the Green_LED
      digitalWrite(Blue_LED, LOW);                                   // turn off the Blue_LED
      Serial.print("Get speak command: "); 
      int val = Voice.read();
      Serial.println(val);
       
    switch(val) 
    {
        case 1:
          i = 0;
          Serial.println("1_red");
          pixy.ccc.getBlocks();                                      // get the numbers of blocks
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);                                                                                           
          blocks = pixy.ccc.numBlocks;
          Serial.print("Number of blocks: ");
          Serial.println(blocks);
         //while((pixy.ccc.blocks[i].m_signature != Signature_Red ) && (i <= blocks) || (pixy.ccc.blocks[i].m_width < Block_Width || pixy.ccc.blocks[i].m_height < Block_Height))  
          while( (pixy.ccc.blocks[i].m_signature != Signature_Red ) && (i <= blocks) )     //whether the red object
          {
              i++;
          }
          Serial.print("当前i的值为： ");
          Serial.println(i);
          Serial.print("m_signature= ");
          Serial.println(pixy.ccc.blocks[i].m_signature);
          if(i>blocks)
          {
              return 0;
          }   
          transForm(pixy.ccc.blocks[i].m_x,pixy.ccc.blocks[i].m_y);                              
          Serial.print(Coordinate[0]);
          Serial.print("  ");
          Serial.print(Coordinate[1]);
          Serial.print("\n");
          //suck Point
          Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                     //Red cube position 
          Dobot_SetEndEffectorSuctionCup(true);                                                                                //Turn on air pump
          Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);                                                      //Lift a certain height
          //place Point
          Dobot_SetPTPCmd(JUMP_XYZ, Red_position_X, Red_position_Y, Red_position_Z+25*gRed, Red_position_R);                   //Coordinates that the red cube is to be placed 
          Dobot_SetEndEffectorSuctionCup(false);                                                                               //Turn off air pump
          Dobot_SetPTPCmd(JUMP_XYZ, Red_position_X, Red_position_Y, 100, 0);
          gRed++;
          Serial.print("gRed:"); 
          Serial.println(gRed);                                                                                               //The number of the red block
          break;
         
       case 2:
          i = 0;
          Serial.println("2_green");
          pixy.ccc.getBlocks();                      // get the numbers of blocks
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);   
          blocks = pixy.ccc.numBlocks;
          Serial.print("Number of blocks: ");
          Serial.println(blocks);
          while((pixy.ccc.blocks[i].m_signature != Signature_Green ) && (i <= blocks) )                                        //whether the green object
          {
             i++;
          }
          Serial.print("当前i的值为： ");
          Serial.println(i);
          Serial.print("m_signature= ");
          Serial.println(pixy.ccc.blocks[i].m_signature);
          if(i>blocks)
          {
              return 0;
          }  
          transForm(pixy.ccc.blocks[i].m_x,pixy.ccc.blocks[i].m_y);                              
          Serial.print(Coordinate[0]);
          Serial.print("  ");
          Serial.print(Coordinate[1]);
          Serial.print("\n");
          //suck Point
          Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                     //green cube position 
          Dobot_SetEndEffectorSuctionCup(true);                                                                                //Turn on air pump
          Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);                                                      //Lift a certain height
          //place Point
          Dobot_SetPTPCmd(JUMP_XYZ, Green_position_X, Green_position_Y, Green_position_Z+25*gGreen, Green_position_R);         //Coordinates that the green cube is to be placed 
          Dobot_SetEndEffectorSuctionCup(false);                                                                               //Turn off air pump
          Dobot_SetPTPCmd(JUMP_XYZ, Green_position_X, Green_position_Y, 100, 0);
          gGreen++;
          Serial.print("gGreen:"); 
          Serial.println(gGreen);                                                                                             //The number of the green block
          break;

       case 3:
          i = 0;
          Serial.println("3_blue");
          pixy.ccc.getBlocks();                      // get the numbers of blocks
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);   
          blocks = pixy.ccc.numBlocks;
          Serial.print("Number of blocks: ");
          Serial.println(blocks);
          while((pixy.ccc.blocks[i].m_signature != Signature_Blue ) && (i <= blocks) )                                        //whether the blue object
          {
             i++;
          }
          Serial.print("当前i的值为： ");
          Serial.println(i);
          Serial.print("m_signature= ");
          Serial.println(pixy.ccc.blocks[i].m_signature);
          if(i>blocks)
          {
              return 0;
          }  
          transForm(pixy.ccc.blocks[i].m_x,pixy.ccc.blocks[i].m_y);                              
          Serial.print(Coordinate[0]);
          Serial.print("  ");
          Serial.print(Coordinate[1]);
          Serial.print("\n");
          //suck Point
          Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                     //blue cube position 
          Dobot_SetEndEffectorSuctionCup(true);                                                                                //Turn on air pump
          Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);                                                      //Lift a certain height
          //place Point
          Dobot_SetPTPCmd(JUMP_XYZ, Blue_position_X, Blue_position_Y, Blue_position_Z+25*gBlue, Blue_position_R);              //Coordinates that the blue cube is to be placed 
          Dobot_SetEndEffectorSuctionCup(false);                                                                               //Turn off air pump
          Dobot_SetPTPCmd(JUMP_XYZ, Blue_position_X, Blue_position_Y, 100, 0);
          gBlue++;
          Serial.print("gBlue:"); 
          Serial.println(gBlue);                                                                                             //The number of the blue block
          break;

       case 4:
          i = 0;
          Serial.println("4_yellow");
          pixy.ccc.getBlocks();                      // get the numbers of blocks
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);
          pixy.ccc.getBlocks();
          delay(10);   
          blocks = pixy.ccc.numBlocks;
          Serial.print("Number of blocks: ");
          Serial.println(blocks);
          while((pixy.ccc.blocks[i].m_signature != Signature_Yellow ) && (i <= blocks) )                                        //whether the yellow object
          {
             i++;
          }
          Serial.print("当前i的值为： ");
          Serial.println(i);
          Serial.print("m_signature= ");
          Serial.println(pixy.ccc.blocks[i].m_signature);
          if(i>blocks)
          {
              return 0;
          }  
          transForm(pixy.ccc.blocks[i].m_x,pixy.ccc.blocks[i].m_y);                              
          Serial.print(Coordinate[0]);
          Serial.print("  ");
          Serial.print(Coordinate[1]);
          Serial.print("\n");
          //suck Point
          Dobot_SetPTPCmd(JUMP_XYZ, Coordinate[0], Coordinate[1], -45, 0);                                                     //yellow cube position 
          Dobot_SetEndEffectorSuctionCup(true);                                                                                //Turn on air pump
          Dobot_SetPTPCmd(MOVL_XYZ, Coordinate[0], Coordinate[1], 50, 0);                                                      //Lift a certain height
          //place Point
          Dobot_SetPTPCmd(JUMP_XYZ, Yellow_position_X, Yellow_position_Y, Yellow_position_Z+25*gYellow, Yellow_position_R);    //Coordinates that the yellow cube is to be placed 
          Dobot_SetEndEffectorSuctionCup(false);                                                                               //Turn off air pump
          Dobot_SetPTPCmd(JUMP_XYZ, Yellow_position_X, Yellow_position_Y, 100, 0);
          gYellow++;
          Serial.print("gYellow:"); 
          Serial.println(gYellow);                                                                                            //The number of the yellow block
          break;
     }  
  }
}
