/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-06-05
** Version:             V2.0.0
** Descriptions:        Visual recognition for DOBOT Magician
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "SmartKit.h"

void setup()
{
    Serial.begin(115200);
    SmartKit_VISSetAT(197.2155, 0.0679, 61.0561, 25.5385);		
    SmartKit_VISSetPixyMatrix(11, 153, 44, 45, 135, 91, 45, 46, 260, 11, 47, 43);	
    SmartKit_VISSetColorSignature(RED, 1);									
    SmartKit_VISSetColorSignature(GREEN, 2);
    SmartKit_VISSetColorSignature(BLUE, 3);
    SmartKit_VISSetDobotMatrix(245.1905, -61.6963, 214.2730, 1.5698, 169.7256, 67.9938);	
    SmartKit_VISSetGrapAreaZ(-65);									
    SmartKit_VISSetBlockTA(RED, 120, -135.9563, -66.9085, 0);		
    SmartKit_VISSetBlockTA(GREEN, 180, -135.9563, -66.9085, 0);
    SmartKit_VISSetBlockTA(BLUE, 240, -135.9563, -66.9085, 0);
    SmartKit_VISSetBlockHeight(RED, 26);								
    SmartKit_VISSetBlockHeight(GREEN, 26);
    SmartKit_VISSetBlockHeight(BLUE, 26);
    SmartKit_VISInit();
    SmartKit_Init();
    Serial.println("Smart Init...");
}

void loop()
{
    int color;
    Dobot_SetPTPJumpParams(0);  
    SmartKit_VISRun();

    color = GREEN;
    Dobot_SetPTPJumpParams(10);       
    while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);      
        SmartKit_VISPlaceBlock(color);
    }
    SmartKit_VISSetBlockPlaceNum(color, 0);

    color = RED;
    Dobot_SetPTPJumpParams(10);         
    while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);      
        SmartKit_VISPlaceBlock(color);
    }
    SmartKit_VISSetBlockPlaceNum(color, 0);

    color = BLUE;
    Dobot_SetPTPJumpParams(10);        
    while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);         
        SmartKit_VISPlaceBlock(color);
    }
    SmartKit_VISSetBlockPlaceNum(color, 0);

    color = YELLOW;
    Dobot_SetPTPJumpParams(10);          
    while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
    {
        Dobot_SetPTPJumpParams(30);       
        SmartKit_VISPlaceBlock(color);
    }
    SmartKit_VISSetBlockPlaceNum(color, 0);

}


