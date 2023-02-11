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
    SmartKit_VISSetAT(197.2155, 0.0679, 61.0561, 25.5385);					/* 设置视觉识别区域坐标 */
    SmartKit_VISSetPixyMatrix(11, 153, 44, 45, 135, 91, 45, 46, 260, 11, 47, 43);	/* 设置pixy变换矩阵 */
    SmartKit_VISSetColorSignature(RED, 1);											/* 设置颜色标识 */
    SmartKit_VISSetColorSignature(GREEN, 2);
    SmartKit_VISSetColorSignature(BLUE, 3);
    SmartKit_VISSetColorSignature(YELLOW, 4);
    SmartKit_VISSetDobotMatrix(245.1905, -61.6963, 214.2730, 1.5698, 169.7256, 67.9938);		/* 设置机械臂变换矩阵 */
    SmartKit_VISSetGrapAreaZ(-65);												/* 设置抓取平面z轴坐标 */
    SmartKit_VISSetBlockTA(RED, 120, -135.9563, -66.9085, 0);			/* 设置物块目标区域 */
    SmartKit_VISSetBlockTA(GREEN, 160, -135.9563, -66.9085, 0);
    SmartKit_VISSetBlockTA(BLUE, 200, -135.9563, -66.9085, 0);
    SmartKit_VISSetBlockTA(YELLOW, 240, -135.9563, -66.9085, 0);
    SmartKit_VISSetBlockHeight(RED, 26);										/* 设置物块高度 */
    SmartKit_VISSetBlockHeight(GREEN, 26);
    SmartKit_VISSetBlockHeight(BLUE, 26);
    SmartKit_VISSetBlockHeight(YELLOW, 26);
    SmartKit_VISInit();
    SmartKit_VoiceCNInit();
    SmartKit_Init();
    SmartKit_VoiceCNAddCommand("hong se",1);
    SmartKit_VoiceCNAddCommand("lan se",2);
    SmartKit_VoiceCNAddCommand("lv se",3);
    SmartKit_VoiceCNAddCommand("huang se",4);
    SmartKit_VoiceCNStart();
    Serial.println("Smart Init...");
}

void loop()
{
    int color;
    Dobot_SetPTPJumpParams(0);              //Set up the maximum height of the magician lift
    if(SmartKit_ButtonCheckState(RED)==DOWN)
    {
        SmartKit_LedTurn(RED, ON);
        SmartKit_LedTurn(BLUE, ON);
        SmartKit_LedTurn(GREEN, ON);
        if (SmartKit_VoiceCNVoiceCheck(3) == TRUE)
        {
            color = GREEN;
            SmartKit_LedTurn(RED, OFF);
            SmartKit_LedTurn(BLUE, OFF);
            SmartKit_LedTurn(GREEN, OFF);
            while(SmartKit_VISRun() == TRUE)
            {
                Dobot_SetPTPJumpParams(10);              //Set up the maximum height of the magician lift
                while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
                {
                    Dobot_SetPTPJumpParams(30);              //Set up the maximum height of the magician lift
                    SmartKit_VISPlaceBlock(color);
                }
            }
            SmartKit_VISSetBlockPlaceNum(color, 0);
        }
    
        if (SmartKit_VoiceCNVoiceCheck(1) == TRUE)
        {
            color = RED;
            SmartKit_LedTurn(RED, OFF);
            SmartKit_LedTurn(BLUE, OFF);
            SmartKit_LedTurn(GREEN, OFF);
            SmartKit_VISRun();
            while(SmartKit_VISRun() == TRUE)
            {
                Dobot_SetPTPJumpParams(10);              //Set up the maximum height of the magician lift
                while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
                {
                    Dobot_SetPTPJumpParams(30);              //Set up the maximum height of the magician lift
                    SmartKit_VISPlaceBlock(color);
                }
            }
            SmartKit_VISSetBlockPlaceNum(color, 0);
        }
    
        if (SmartKit_VoiceCNVoiceCheck(2) == TRUE)
        {
            color = BLUE;
            SmartKit_LedTurn(RED, OFF);
            SmartKit_LedTurn(BLUE, OFF);
            SmartKit_LedTurn(GREEN, OFF);
            while(SmartKit_VISRun() == TRUE)
            {
                Dobot_SetPTPJumpParams(10);              //Set up the maximum height of the magician lift
                while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
                {
                    Dobot_SetPTPJumpParams(30);              //Set up the maximum height of the magician lift
                    SmartKit_VISPlaceBlock(color);
                }
            }
            SmartKit_VISSetBlockPlaceNum(color, 0);
        }
    
        if (SmartKit_VoiceCNVoiceCheck(4) == TRUE)
        {
            color = YELLOW;
            SmartKit_LedTurn(RED, OFF);
            SmartKit_LedTurn(BLUE, OFF);
            SmartKit_LedTurn(GREEN, OFF);
            while(SmartKit_VISRun() == TRUE)
            {
                Dobot_SetPTPJumpParams(10);              //Set up the maximum height of the magician lift
                while (SmartKit_VISGrabBlock(color, 1, 0) == TRUE)
                {
                    Dobot_SetPTPJumpParams(30);              //Set up the maximum height of the magician lift
                    SmartKit_VISPlaceBlock(color);
                }
            }
            SmartKit_VISSetBlockPlaceNum(color, 0);
        }
    }
    else
    {
        SmartKit_LedTurn(RED, OFF);
        SmartKit_LedTurn(BLUE, OFF);
        SmartKit_LedTurn(GREEN, OFF);  
    }
}
