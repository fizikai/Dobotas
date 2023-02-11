
/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-1-24
** Version:             V1.1.1
** Descriptions:        voice control LED
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <VoiceRecognition.h>
VoiceRecognition Voice;                                   //Structural variable

#define Red_LED 9                                         //Red LED connects to the 9 pin
#define Green_LED A1                                      //Green LED connects to the A1 pin
#define Blue_LED A3                                       //Blue LED connects to the A3 pin

void setup() 
{
    Serial.begin(115200);
    pinMode(Red_LED,OUTPUT);                              //Set the 9 pin to OUTPUT
    pinMode(Green_LED,OUTPUT);                            //Set the A1 pin to OUTPUT
    pinMode(Blue_LED,OUTPUT);                             //Set the A3 pin to OUTPUT
    digitalWrite(Red_LED,LOW);                            
    digitalWrite(Green_LED,LOW);                          
    digitalWrite(Blue_LED,LOW);                                 
    
    Voice.init();                                         //VoiceRecognition Initialization 
    Voice.addCommand("kai hong deng",0);                  //Add command（command label (repeatable)）
    Voice.addCommand("kai lv deng",1);
    Voice.addCommand("kai lan deng",2);
    Voice.addCommand("guan hong deng",3);     
    Voice.addCommand("guan lv deng",4); 
    Voice.addCommand("guan lan deng",5);   
    Voice.addCommand("kai deng",6);
    Voice.addCommand("guan deng",7);                                     
    Voice.start();                                        //Start to recognize
    Serial.println("start！");  
}

void loop() 
{
  switch(Voice.read())                                   //check recognition contents
  {
    case 0:                                                                     
        digitalWrite(Red_LED,HIGH);                      //turn on the Red_LED
        Serial.println("turn on the red LED");                  
        break;
    case 1:                                                                     
        digitalWrite(Green_LED,HIGH);                    //turn on the Green_LED
        Serial.println("turn on the green LED");                  
        break;
    case 2:                                                                     
        digitalWrite(Blue_LED,HIGH);                     //turn on the Blue_LED
        Serial.println("turn on the blue LED");                  
        break;
    case 3:                                                                     
        digitalWrite(Red_LED,LOW);                       //turn off the Red_LED
        Serial.println("turn off the red LED");                  
        break;
    case 4:                                                                     
        digitalWrite(Green_LED,LOW);                     //turn off the Green_LED
        Serial.println("turn off the green LED");                  
        break;
    case 5:                                                                     
        digitalWrite(Blue_LED,LOW);                      //turn off the Blue_LED
        Serial.println("turn off the blue LED");                  
        break;
    case 6:                                                                     
        digitalWrite(Red_LED,HIGH);                      //turn on the Red_LED
        digitalWrite(Green_LED,HIGH);                    //turn on the Green_LED
        digitalWrite(Blue_LED,HIGH);                     //turn on the Blue_LED
        Serial.println("turn on the all light");                  
        break;
    case 7:                                                                    
        digitalWrite(Red_LED,LOW);                       //turn off the Red_LED
        digitalWrite(Green_LED,LOW);                     //turn off the Green_LED
        digitalWrite(Blue_LED,LOW);                      //turn off the Blue_LED
        Serial.println("turn off the all light");                 
        break; 
    default:
        Serial.println("Error!");                 
        break;   
  }
  delay(100);
}
