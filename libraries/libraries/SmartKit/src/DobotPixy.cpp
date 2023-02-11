/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:            VIS.cpp
** Latest modified date: 2019-05-15
** Latest version:       V1.0.0
** Description:          SmartKit VIS API
**
**------------------------------------------------------------
** Created by:
** Created date:         2019-05-15
** Version:              V1.0.0
** Descriptions:         SmartKit VIS API
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "DobotPixy.h"
#include "Magician.h"
#include "Pixy2I2C.h"
#include "SmartKitType.h"


VIS::BLOCKPARM gBlockParmRed;	  /* 红色物块参数结构体 */
VIS::BLOCKPARM gBlockParmBlue;  /* 蓝色物块参数结构体 */
VIS::BLOCKPARM gBlockParmYellow;/* 黄色物块参数结构体 */
VIS::BLOCKPARM gBlockParmGreen; /* 绿色物块参数结构体 */

VIS::VISAT	gVISAT;  /* 机械臂视觉识别目标区域参数 */

VIS::MATRIXPARM gMatrixParm; /* 矩阵变换参数 */

Pixy2I2C pixy;  /* pixy object */


void VIS::CalcInvMat(float *Mat, float *InvMat)
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

//matrix multiplication，A^-1*A*RT = A^-1*B => RT = A^-1*B
void VIS::MatMultiMat(float *Mat1, float *Mat2, float *Result)
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

/*************************************************************
** Function name:      GetColorBlockParmPtr
** Descriptions:       获取不同颜色的BlockParm的指针
** Input parameters:   no
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::GetColorBlockParmPtr(int color, 
                                     PBLOCKPARM *ptr)
{
    switch (color)
    {
    case RED:
        *ptr = &gBlockParmRed;
        break;

    case BLUE:
        *ptr = &gBlockParmBlue;
        break;

    case YELLOW:
        *ptr = &gBlockParmYellow;
        break;

    case GREEN:
        *ptr = &gBlockParmGreen;
        break;

    default:
        *ptr = NULL;
        return FALSE;
    }
    return TRUE;
}

/*************************************************************
** Function name:      Init
** Descriptions:       VIS初始化，
**					   默认门型抬升高度20，
**					   初始化之前需要完成颜色标定和位置标定
** Input parameters:   no
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::Init(void)
{
    Serial.begin(115200);
    Dobot_Init();
    Serial.print("Dobot Init\n");
    pixy.init();
    pixy.setLamp(1, 1);
    Serial.print("Pixy Init\n");
    Dobot_SetPTPJumpParams(30);              
    Dobot_SetPTPCommonParams(50, 50);
    Dobot_SetEndEffectorSuctionCup(false);	 /* 松开吸盘 */
    float inv_pixy[9] =                      
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    };
    CalcInvMat(gMatrixParm.pixy, inv_pixy);
    MatMultiMat(gMatrixParm.dobot, inv_pixy, gMatrixParm.RT);
    Serial.print("Finally\n");
}

/*************************************************************
** Function name:      SetDobotMatrix
** Descriptions:       设置机械臂变换矩阵
** Input parameters:   x1: 方块1的x坐标
**					   y1: 方块1的y坐标
**					   x2: 方块2的x坐标
**					   y2: 方块2的y坐标
**					   x3: 方块3的x坐标
**					   y3: 方块3的y坐标
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::SetDobotMatrix(float x1, float y1, 
                         float x2, float y2, 
                         float x3, float y3)
{
    gMatrixParm.dobot[3] = x1;
    gMatrixParm.dobot[4] = x2;
    gMatrixParm.dobot[5] = x3;
    gMatrixParm.dobot[0] = y1;
    gMatrixParm.dobot[1] = y2;
    gMatrixParm.dobot[2] = y3;
    gMatrixParm.dobot[6] = 1;
    gMatrixParm.dobot[7] = 1;
    gMatrixParm.dobot[8] = 1;
}

/*************************************************************
** Function name:      SetPixyMatrix
** Descriptions:       设置pixy变换矩阵
** Input parameters:   x1:		方块1的x坐标
**					   y1:		方块1的y坐标
**					   length1: 方块1的长
**					   weight1: 方块1的宽
**					   x2:		方块2的x坐标
**					   y2:		方块2的y坐标
**					   length2: 方块2的长
**					   weight2: 方块2的宽
**					   x3:		方块3的x坐标
**					   y3:		方块3的y坐标
**					   length3: 方块3的长
**					   weight3: 方块3的宽
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::SetPixyMatrix(
    float x1, float y1, float length1, float wide1,
    float x2, float y2, float length2, float wide2,
    float x3, float y3, float length3, float wide3)
{
    gMatrixParm.pixy[0] = x1 + length1 / 2;
    gMatrixParm.pixy[1] = x2 + length2 / 2;
    gMatrixParm.pixy[2] = x3 + length3 / 2;
    gMatrixParm.pixy[3] = y1 + wide1 / 2;
    gMatrixParm.pixy[4] = y2 + wide2 / 2;
    gMatrixParm.pixy[5] = y3 + wide3 / 2;
    gMatrixParm.pixy[6] = 1;
    gMatrixParm.pixy[7] = 1;
    gMatrixParm.pixy[8] = 1;
}


/*************************************************************
** Function name:      SetGrapAreaZ
** Descriptions:       设置抓取区域z轴坐标
** Input parameters:   z: 放置区域高度
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::SetGrapAreaZ(float z)
{
    gGrapAreaZ = z;
}

/*************************************************************
** Function name:      GetPlacetAreaZ
** Descriptions:       获取抓取区域z轴坐标
** Input parameters:   no
** Output parameters:  no
** Returned value:     抓取区域高度
*************************************************************/

float VIS::GetGrapAreaZ(void)
{
    return gGrapAreaZ;
}

/*************************************************************
** Function name:      SetDOBOTPIXYAT
** Descriptions:       设置机械臂视觉识别区域坐标
** Input parameters:   x:
**					   y:
**					   z:
**					   r: 旋转角度
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::SetAT(float x, float y, float z, float r)
{
    gVISAT.x = x;
    gVISAT.y = y;
    gVISAT.z = z;
    gVISAT.r = r;
}

/*************************************************************
** Function name:      SetColorSignature
** Descriptions:       设置物块颜色标识
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   signature: 物块标识
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::SetColorSignature(char color, char signature)
{
    PBLOCKPARM ptr;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        ptr->signature = signature;
        return TRUE;
    }
    return FALSE;
}

/*************************************************************
** Function name:      SetBlockTA
** Descriptions:       设置各颜色物块目标区域
** Input parameters:   pBlockParm: 需要赋值的参数结构体指针
**					   x: 物块的x坐标
**					   y: 物块的y坐标
**					   z: 物块的z坐标
**					   r: 物块的旋转角度
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::SetBlockTAParm(PBLOCKPARM pBlockParm, 
                               float x, 
                               float y, 
                               float z, 
                               float r)
{
    pBlockParm->TargetX = x;
    pBlockParm->targetY = y;
    pBlockParm->targetZ = z;
    pBlockParm->targetR = r;
}

/*************************************************************
** Function name:      SetBlockTA
** Descriptions:       设置各颜色物块目标区域
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   x: 物块的x坐标
**					   y: 物块的y坐标
**					   z: 物块的z坐标
**					   r: 物块的旋转角度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::SetBlockTA(int color, 
                     float x, 
                     float y, 
                     float z, 
                     float r)
{
    PBLOCKPARM ptr;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        SetBlockTAParm(ptr, x, y, z, r);
        return	TRUE;
    }
    return FALSE;
}

/*************************************************************
** Function name:      GetBlockCheckNum
** Descriptions:       获取视觉检测到的不同颜色的物块数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     物块数量
*************************************************************/

char VIS::GetBlockCheckNum(int color)
{
    PBLOCKPARM ptr;
    int checkNum = 0;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        checkNum = ptr->checkNum;
    }
    return	checkNum;
}

/*************************************************************
** Function name:      SetBlockPlaceNum
** Descriptions:       设置物块放置数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   placeNum: 放置的数量
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::SetBlockPlaceNum(int color, int placeNum)
{
    PBLOCKPARM ptr;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        ptr->placeNum = placeNum;
        return TRUE;
    }
    return	FALSE;
}

/*************************************************************
** Function name:      GetBlockPlaceNum
** Descriptions:       获取物块放置的数量
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     物块数量
*************************************************************/

char VIS::GetBlockPlaceNum(int color)
{
    PBLOCKPARM ptr;
    int placeNum = 0;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        placeNum = ptr->placeNum;
    }
    return	placeNum;
}

/*************************************************************
** Function name:      SetBlockHeight
** Descriptions:       设置物块高度
** Input parameters:   color: 物块颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   height: 物块高度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::SetBlockHeight(int color, float height)
{
    PBLOCKPARM ptr;
    GetColorBlockParmPtr(color, &ptr);
    if (ptr != NULL)
    {
        ptr->Height = height;
        return TRUE;
    }
    return	FALSE;
}

/*************************************************************
** Function name:      BlockParmPlaceNumClear
** Descriptions:       清除四个颜色pixy检测到的物块数量
** Input parameters:   no
** Output parameters:  no
** Returned value:     no
*************************************************************/

void VIS::BlockParmCheckNumClear(void)
{
    gBlockParmRed.checkNum = 0;
    gBlockParmBlue.checkNum = 0;
    gBlockParmYellow.checkNum = 0;
    gBlockParmGreen.checkNum = 0;
}

/*************************************************************
** Function name:      transForm
** Descriptions:       转换pixy坐标成dobot坐标
** Input parameters:   pixyX: 摄像头坐标
**					   pixyY:
** Output parameters:  *pDobotX: 机械臂坐标
**					   *pDobotY
** Returned value:     no
*************************************************************/

void VIS::transForm(float pixyX,    float pixyY, 
                          float *pDobotX, float *pDobotY)
{
    *pDobotY = (gMatrixParm.RT[0] * pixyX) 
             + (gMatrixParm.RT[1] * pixyY) 
             + (gMatrixParm.RT[2] * 1);
    *pDobotX = (gMatrixParm.RT[3] * pixyX) 
             + (gMatrixParm.RT[4] * pixyY) 
             + (gMatrixParm.RT[5] * 1);

#ifdef __DEBUG
    Serial.print("pixy  x,y:");
    Serial.print(pixyX);
    Serial.print(" , ");
    Serial.println(pixyY);

    Serial.print("coordinate  x,y:");
    Serial.print(*pDobotX);
    Serial.print(" , ");
    Serial.println(*pDobotY);
#endif /* __DEBUG */

}

/*************************************************************
** Function name:      FloatEqual
** Descriptions:       检查浮点型是否相等
** Input parameters:   data1: 数据1
**					   data2: 数据2
**					   precision: 精确度,多少以内视为相等
** Output parameters:  no
** Returned value:     返回TRUE, FALSE，移动成功或者失败
*************************************************************/

int VIS::FloatEqual(float data1, 
                          float data2, 
                          float precision)
{
    if (fabs(data1 - data2) <= precision)
    {
        return TRUE;
    }
    return FALSE;
}

/*************************************************************
** Function name:      DobotMove
** Descriptions:       机械臂移动，检查移动是否成功
** Input parameters:   Model，移动的方式，查看Dobot_SetPTPCmd文档定义
**					   x:
**					   y:
**					   z:
**					   r: 旋转角度
** Output parameters:  no
** Returned value:     返回TRUE, FALSE，移动成功或者失败
*************************************************************/

int VIS::DobotMove(uint8_t Model, 
                         float x, 
                         float y, 
                         float z, 
                         float r)
{
    Pose p;
    Dobot_SetPTPCmd(Model, x, y, z, r);     // The position of a target object
    delay(500);
    GetPose(&p);
#ifdef __DEBUG
    Serial.print("move: ");
    Serial.print(x);
    Serial.print(" , ");
    Serial.println(y);
    Serial.print(" , ");
    Serial.println(z);

    Serial.print("pose: ");
    Serial.print(p.x);
    Serial.print(" , ");
    Serial.println(p.y);
    Serial.print(" , ");
    Serial.println(p.z);
#endif /* __DEBUG */
    if (FloatEqual(p.x, x, 0.01) == TRUE && FloatEqual(p.y, y, 0.01) == TRUE && FloatEqual(p.z, z, 0.01) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
    delay(500);
}

/*************************************************************
** Function name:      DOBOTPIXYRun
** Descriptions:       视觉识别
** Input parameters:   no
** Output parameters:  no
** Returned value:     TRUE: 存在物块;
**					   FALSE: 原因有以下几种可能
**							  1,没有检测到物块，
**							  2,物块的颜色标记设置有误
*************************************************************/

char VIS::Run(void)
{
    int signature = 0;
    Pose p;
    PBLOCKPARM ptr = NULL;
    GetPose(&p);
    delay(500);
    if (FloatEqual(p.x, gVISAT.x, 0.01) == FALSE || FloatEqual(p.y, gVISAT.y, 0.01) == FALSE || FloatEqual(p.z, gVISAT.z, 0.01) == FALSE)		/* 判断当前坐标 */
    {
        while (DobotMove(JUMP_XYZ, gVISAT.x, gVISAT.y, gVISAT.z, gVISAT.r) != TRUE);       /* 设置起始位置 */
    }
    Serial.print("Starting...\n");
    if (pixy.ccc.getBlocks() != 0)
    {
        delay(1500);
        pixy.ccc.getBlocks();																			 /* 获取物块 */
    }
    Serial.print("Number of blocks: ");
    Serial.println(pixy.ccc.numBlocks);
    delay(200);
    if (pixy.ccc.numBlocks == 0)																	 /* 判断没有物块 */
    {
        return FALSE;
    }
    else
    {
        BlockParmCheckNumClear();																	 /* 物块放置数量清除 */
        for (int cir = 0; cir < pixy.ccc.numBlocks; cir++)
        {

            signature = pixy.ccc.blocks[cir].m_signature;
            if (signature == gBlockParmRed.signature)					 /* 判断物块标记是否一致，并且判断物块数量是否超过最大数量限制 */
            {
                GetColorBlockParmPtr(RED, &ptr);
            }

            else if (signature == gBlockParmBlue.signature)
            {
                GetColorBlockParmPtr(BLUE, &ptr);
            }

            else if (signature == gBlockParmYellow.signature)
            {
                GetColorBlockParmPtr(YELLOW, &ptr);
            }

            else if (signature == gBlockParmGreen.signature)
            {
                GetColorBlockParmPtr(GREEN, &ptr);
            }

            if (ptr != NULL)
            {
                if (ptr->checkNum < BlockMaxNum)						/* 判断是否超出最大数量 */
                {
                    transForm(pixy.ccc.blocks[cir].m_x,
                        pixy.ccc.blocks[cir].m_y,
                        &ptr->coordinate[ptr->checkNum][0],
                        &ptr->coordinate[ptr->checkNum][1]);
                    ptr->checkNum++;
                }

            }
            else
            {
                return FALSE;											/* 指针为空，返回错误信息 */
            }
        }
    }
    if (gBlockParmRed.checkNum == 0 && gBlockParmBlue.checkNum == 0 && gBlockParmYellow.checkNum == 0 && gBlockParmGreen.checkNum)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*************************************************************
** Function name:      DelBlockCoordinate
** Descriptions:       删除指定颜色指定位置物块坐标
** Input parameters:   no
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::DelBlockCoordinate(int color, int num)
{
    PBLOCKPARM ptr = NULL;
    GetColorBlockParmPtr(color, &ptr);							/* 获取颜色指针 */
    if (ptr != NULL && num != 0)								/* 判断指针是否为空 */
    {
        if (num <= ptr->checkNum && ptr->checkNum != 0)
        {
            for (int i = num; i < ptr->checkNum; i++)
            {
                ptr->coordinate[i - 1][0] = ptr->coordinate[i][0];
                ptr->coordinate[i - 1][1] = ptr->coordinate[i][1];
#ifdef __DEBUG
                Serial.print("moveX:");
                Serial.print(ptr->coordinate[i - 1][0]);
                Serial.print("     moveY:");
                Serial.println(ptr->coordinate[i - 1][1]);
                Serial.print(ptr->checkNum);
                Serial.print(" , ");
                Serial.println(i);
#endif /* __DEBUG */
            }
            ptr->checkNum--;											/* 物块数量减1 */
            return TRUE;
        }
    }
    return FALSE;
}

/*************************************************************
** Function name:      SetGrapBlockMark
** Descriptions:       设置物块抓取标记
** Input parameters:   mark: 物块抓取标记
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

int VIS::SetGrapBlockMark(int mark)
{
    if (mark == TRUE || mark == FALSE)
    {
        gGrabMark = mark;
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/*************************************************************
** Function name:      GetGrapBlockMark
** Descriptions:       获取物块抓取标记
** Input parameters:   no
** Output parameters:  no
** Returned value:     物块抓取标记，TRUE已经抓取，FALSE，未抓取
*************************************************************/

int VIS::GetGrapBlockMark(void)
{
    return gGrabMark;
}

/*************************************************************
** Function name:      GrabBlock
** Descriptions:       抓取物块
** Input parameters:   color: 抓取物块的颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
**					   blockNum: 物块的编号
**					   r: 抓取旋转的角度
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::GrabBlock(int color, int blockNum, float r)
{
    PBLOCKPARM ptr = NULL;
    GetColorBlockParmPtr(color, &ptr);					  /* 获取颜色指针 */
    if (ptr != NULL && GetGrapBlockMark() == FALSE && blockNum != 0)		  /* 判断空指针以及物块抓取标记 */
    {
        if (ptr->checkNum >= blockNum)					  /* 判断当前是否有这个物块 */
        {
#ifdef __DEBUG
            Serial.print("coordinateX:");
            Serial.print(ptr->coordinate[blockNum - 1][0]);
            Serial.print("     coordinateY:");
            Serial.println(ptr->coordinate[blockNum - 1][1]);
#endif /* __DEBUG */
            while (DobotMove(JUMP_XYZ,								/* 移动机械臂 */
                ptr->coordinate[blockNum - 1][0],
                ptr->coordinate[blockNum - 1][1],
                gGrapAreaZ + ptr->Height,
                r)
                != TRUE);
            Dobot_SetEndEffectorSuctionCup(true);
            DelBlockCoordinate(color, blockNum);		  /* 删除物块坐标 */
            SetGrapBlockMark(TRUE);						  /* 物块抓取标记 */
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    return FALSE;
}

/*************************************************************
** Function name:      PlaceBlock
** Descriptions:       放置物块
** Input parameters:   color: 放置物块的颜色，
**                            可传递值:RED,BLUE,YELLOW,GREEN
** Output parameters:  no
** Returned value:     TRUE: 成功; FALSE: 失败
*************************************************************/

char VIS::PlaceBlock(int color)
{
    PBLOCKPARM ptr = NULL;
    GetColorBlockParmPtr(color, &ptr);		/* 获取颜色指针 */
    if (ptr != NULL && GetGrapBlockMark() == TRUE)	/* 物块未抓取的时候报错 */
    {
        while (DobotMove(JUMP_XYZ,				/* 移动到物块放置区域 */
            ptr->TargetX,
            ptr->targetY,
            ptr->targetZ + ptr->placeNum*ptr->Height + ptr->Height,
            ptr->targetR)
            != TRUE);
        Dobot_SetEndEffectorSuctionCup(false);	/* 松开吸盘 */
        ptr->placeNum++;
        SetGrapBlockMark(FALSE);
        return TRUE;
    }
    return FALSE;
}

