/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        AlarmLED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#define Red_LED 9                                                    //Red_LED connects to the 9 pin
#define Green_LED A1                                                 //Green_LED connects to the A1 pin
#define Blue_LED A3                                                  //Blue_LED connects to the A3 pin

void setup() 
{
  pinMode(Red_LED,OUTPUT);                                           //Set the 9 pin to OUTPUT
  pinMode(Green_LED,OUTPUT);                                         //Set the A1 pin to OUTPUT
  pinMode(Blue_LED,OUTPUT);                                          //Set the A3 pin to OUTPUT
  digitalWrite(Red_LED,LOW);                                         //Set the 9 pin to LOW
  digitalWrite(Green_LED,LOW);                                       //Set the A1 pin to LOW
  digitalWrite(Blue_LED,LOW);                                        //Set the A3 pin to LOW    
}

void loop() 
{
  digitalWrite(Red_LED,HIGH);
  delay(300);
  digitalWrite(Red_LED,LOW);
  digitalWrite(Green_LED,HIGH);
  delay(300);
  digitalWrite(Green_LED,LOW);
  digitalWrite(Blue_LED,HIGH);
  delay(300);
  digitalWrite(Blue_LED,LOW);
}
