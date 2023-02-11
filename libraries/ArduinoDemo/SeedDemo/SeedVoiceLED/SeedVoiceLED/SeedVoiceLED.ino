/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**--------------------------------------------------------------------------------------------------------
** Modify by:           
** Modified date:       2019-3-21
** Version:             V1.1.1
** Descriptions:        
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <SoftwareSerial.h>

#define SOFTSERIAL_RX_PIN  A11                            //connect to the A11 pin                                                   
#define SOFTSERIAL_TX_PIN  14                             //connect to the 14 pin
#define Red_LED 9                                         //Red LED connects to the 9 pin
#define Green_LED A1                                      //Green LED connects to the A1 pin
#define Blue_LED A3                                       //Blue LED connects to the A3 pin

SoftwareSerial softSerial(SOFTSERIAL_RX_PIN,SOFTSERIAL_TX_PIN);

const char *voiceBuffer[] =
{
    "Turn on the light",                                  //return 1
    "Turn off the light",                                 //return 2
    "Play music",                                         //return 3
    "Pause",                                              //return 4
    "Next",                                               //return 5
    "Previous",                                           //return 6
    "Up",                                                 //return 7
    "Down",                                               //return 8
    "Turn on the TV",                                     //return 9
    "Turn off the TV",                                    //return 10
    "Increase temperature",                               //return 11
    "Decrease temperature",                               //return 12
    "What's the time",                                    //return 13
    "Open the door",                                      //return 14
    "Close the door",                                     //return 15
    "Left",                                               //return 16
    "Right",                                              //return 17
    "Stop",                                               //return 18
    "Start",                                              //return 19
    "Mode 1",                                             //return 20
    "Mode 2",                                             //return 21
    "Go",                                                 //return 22
};

void setup()
{
    Serial.begin(115200);
    softSerial.begin(9600);
	  pinMode(Red_LED,OUTPUT);                              
    pinMode(Green_LED,OUTPUT);                           
    pinMode(Blue_LED,OUTPUT);                            
    digitalWrite(Red_LED,LOW);                            
    digitalWrite(Green_LED,LOW);                          
    digitalWrite(Blue_LED,LOW);
	
    softSerial.listen();
    Serial.println("ok");
}

void loop()
{
    char cmd;
    if(softSerial.available())
    {
        cmd = softSerial.read();
        switch(cmd)
        {
    			case 1:                                                                     
    				digitalWrite(Red_LED,HIGH);                      //turn on the Red_LED
    				digitalWrite(Green_LED,HIGH);                    //turn on the Green_LED
    				digitalWrite(Blue_LED,HIGH);                     //turn on the Blue_LED
    				Serial.println("turn on the all light");                  
    				break;
    			case 2:                                                                    
    				digitalWrite(Red_LED,LOW);                       //turn off the Red_LED
    				digitalWrite(Green_LED,LOW);                     //turn off the Green_LED
    				digitalWrite(Blue_LED,LOW);                      //turn off the Blue_LED
    				Serial.println("turn off the all light");                 
    				break; 
    			default:
    				Serial.println("Error!");                 
    				break;   
        }
    }
	delay(100);
}
