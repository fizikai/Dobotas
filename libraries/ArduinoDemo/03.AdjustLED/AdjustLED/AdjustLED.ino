 /****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        Adjust the brightness of LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#define LED 9                                    // Red_LED connects to the 9 pin
#define JoyStick_X  A7                           // JoyStick X connects to the A7 pin
float i = 0;

void setup() 
{
   pinMode(LED,OUTPUT);
   Serial.begin(115200);      
}

void loop() 
{
  int x = analogRead(JoyStick_X); 
  Serial.println(x);                                            
  if(x > 520)                                   // JoyStick moves along X-axis in the positive direction
    i = i + 10;
  else if(x < 500)                              // JoyStick moves along X-axis in negative direction
    i = i - 10;
  if(i >= 255)                                  // The brightness range of LED is from 0 to 255
    i = 255;
  else if(i < 0)
    i = 0;
  else
    i = i;
  analogWrite(LED,i);                           // Adjust the brightness of the LED indicator
  Serial.println(i);
  delay(100);
}
