/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        flicker LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

int LED1 = 9;                                           //LED connects to the 9 pin

void setup()
{
   pinMode(LED1,OUTPUT);                                //Set the 9 pin to OUTPUT
}

void loop()
{
  digitalWrite(LED1,HIGH);                              //turn on the LED1
  delay(500);                                           //delay
  digitalWrite(LED1,LOW);                               //turn off the LED1
  delay(500);                                           //delay
}
