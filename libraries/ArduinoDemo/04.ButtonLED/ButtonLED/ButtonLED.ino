/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        button control LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#define Red_LED 9                                //Red LED connects to the 9 pin
#define Green_LED A1                             //Green LED connects to the A1 pin
#define Blue_LED A3                              //Blue LED connects to the A3 pin

#define Red_Button A0                            //Red_button connects to the A0 pin
#define Green_Button A2                          //Green_button connects to the A2 pin
#define Blue_Button A4                           //Blue_button connects to the A4 pin

void setup() 
{
  pinMode(Red_LED, OUTPUT);                       //Set the 9 pin to OUTPUT
  pinMode(Green_LED, OUTPUT);                     //Set the A1 pin to OUTPUT 
  pinMode(Blue_LED, OUTPUT);                      //Set the A3 pin to OUTPUT
  pinMode(Red_Button, INPUT);                     //Set the A0 pin to INPUT
  pinMode(Green_Button, INPUT);                   //Set the A2 pin to INPUT
  pinMode(Blue_Button, INPUT);                    //Set the A4 pin to INPUT
}

void loop()
{
  int val1 = digitalRead(Red_Button);             //Get the value of the A0 pin
  int val2 = digitalRead(Green_Button);           //Get the value of the A2 pin
  int val3 = digitalRead(Blue_Button);            //Get the value of the A4 pin
  if (val1 == 1)                                  //Press the Red button
  {                                                    
     digitalWrite(Red_LED, 1);                    //turn on the Red LED
  } 
  else 
  {
     digitalWrite(Red_LED, 0);                    //turn off the Red LED
  }
  if (val2 == 1)                                  //Press the Green button
  {                                                    
     digitalWrite(Green_LED, 1);                  //turn on the Green LED
  } 
  else 
  {
     digitalWrite(Green_LED, 0);                  //turn off the Green LED
  }
  if (val3 == 1)                                  //Press the Blue button
  {                                                  
     digitalWrite(Blue_LED, 1);                   //turn on the Blue LED
  } 
  else 
  {
     digitalWrite(Blue_LED, 0);                   //turn off the Blue LED
  }
}
