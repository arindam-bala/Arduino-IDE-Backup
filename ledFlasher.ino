#include <Arduino.h> //header file

//input and output pins declaration defination
const int modePin_0 = 5;   //turning and flashing shifter
const int modePin_1 = 6;   //flasher mode changer 
const int buttonLeft = 7;   //turning left key
const int buttonRight = 8;  //turning right key
const int ledPinLeft = 3;   //controls left side led mosfet
const int ledPinRight = 4;  //controls right side led mosfet
const int alertKey = 2;     //alert on/off key
//----------------------------
 
//saved time stamp of last time button pressed
unsigned long timeStamp1 = 0;
unsigned long timeStamp2 = 0;
int i = 0;   //primary counter
int j = 0;   //secondary counter   

void setup()
{
  //pinMode setup of each led and buttons
  pinMode(ledPinLeft,OUTPUT);
  pinMode(ledPinRight,OUTPUT);
  pinMode(modePin_1,INPUT);
  pinMode(modePin_0,INPUT);
  pinMode(buttonLeft,INPUT);
  pinMode(buttonRight,INPUT);
  pinMode(alertKey,INPUT);

}

void loop(){ 
    
    static int pattern = 0;
    static int flag = 0;
    //This control is used for shifting normal turning and alert mode 
    if (digitalRead(modePin_0) &&(millis()-timeStamp2) > 1000)
    {
        timeStamp2 = millis();
        flag = (flag + 1);
        if (flag == 3)
        {
            flag = 0;
        }
        
    }
    
    //This control is used for cahnging alert flashing modes
    if(digitalRead(modePin_1) && (millis() - timeStamp1) > 1000)
    {
        timeStamp1 = millis();
        pattern = (pattern + 1);
        if(pattern == 5)
        {
            pattern = 1;    
        }
    }
    switch(flag)
    {
         case 1:
               if (digitalRead(buttonLeft))             //basic left turning indicator
               {
                   digitalWrite(ledPinLeft,HIGH);
                   delay(500);
                   digitalWrite(ledPinLeft,LOW);
                   delay(500);
               }
               if(!digitalRead(buttonLeft))
               {
                   digitalWrite(ledPinLeft,LOW);
               }

               if (digitalRead(buttonRight))            //basic right turning indicator
               {
                   digitalWrite(ledPinRight,HIGH);
                   delay(500);
                   digitalWrite(ledPinRight,LOW);
                   delay(500);
               }
               if(!digitalRead(buttonRight))
               {
                   digitalWrite(ledPinRight,LOW);
               }
               break;

        //--------------------------------------------------------
        //basic turning code ends here
        //alert flasher code begins from here 
        //--------------------------------------------------------      
        
        case 2:
                switch(pattern)
                {
                        case 1:
                              if(digitalRead(alertKey))
                              {
                                  delay(20);
                                
                                  while(i!=6)
                                  {
                                       digitalWrite(ledPinLeft,HIGH);  //1
                                       digitalWrite(ledPinRight,HIGH);
                                       delay(30);
                                       //gap
                                       digitalWrite(ledPinLeft,LOW);
                                       digitalWrite(ledPinRight,LOW);
                                       delay(30);
                                       i = i + 1;
                                  }
                                  i = 0;
                                  delay(1000);
                              }
                              
                              if(!digitalRead(alertKey))
                              {
                                  digitalWrite(ledPinRight,LOW);   
                                  digitalWrite(ledPinLeft,LOW);
                              }
                              break;
                              //-----------------------------------------
                              //End of mode one
                              //--------------------------------------------------//
                              //Begining of mode two 
                              //-----------------------------------------       
                                  
                        case 2:
                              if (digitalRead(alertKey))
                              {
                                  delay(20);
                                
                                  while (i!=2)
                                  {
                                      while (j!=4)
                                      {
                                          digitalWrite(ledPinLeft,HIGH);       //repeat 3 times
                                          delay(70);
                                          digitalWrite(ledPinLeft,LOW);
                                          delay(70);
                                          j = j + 1;
                                      }
                                      //----------------------------------------
                                      //gap 
                                      j = 0;
                                      while (j!=4)
                                      {
                                          digitalWrite(ledPinRight,HIGH);      //repeat 3 times
                                          delay(70);
                                          digitalWrite(ledPinRight,LOW);
                                          delay(70);
                                          j = j + 1;
                                      }
                                      j = 0;
                                      i = i + 1;
                                  }
                                  i = 0;
                                  //-------------------------------------------
                                  //gap
                                
                                  while (j!=3)
                                  {
                                       digitalWrite(ledPinLeft,HIGH);
                                       delay(200);
                                       digitalWrite(ledPinLeft,LOW);
                                       digitalWrite(ledPinRight,HIGH);
                                       delay(200);
                                       digitalWrite(ledPinRight,LOW);
                                       j = j + 1;
                                  }
                                  j = 0;
                                  delay(100);
                              }
                                      
                              if(!digitalRead(alertKey))
                              {
                                  digitalWrite(ledPinLeft,LOW);
                                  digitalWrite(ledPinRight,LOW);   
                              }
                              break;
                              //-----------------------------------------
                              //End of mode two
                              //--------------------------------------------------//
                              //Begining of mode three
                              //-----------------------------------------
                        case 3:
                              if(digitalRead(alertKey))
                              {
                                  delay(20);
                                
                                  while (i!=2)
                                  {
                                    
                                      while (j!=6)
                                      {
                                         digitalWrite(ledPinLeft,HIGH); // repeat 6 times
                                         digitalWrite(ledPinLeft,HIGH);
                                         delay(30);
                                        //gap
                                         digitalWrite(ledPinLeft,LOW);
                                         digitalWrite(ledPinLeft,LOW);
                                         delay(30);
                                         j = j + 1;
                                      }
                                      j = 0;
                                       while (j!=6)
                                      {
                                         digitalWrite(ledPinRight,HIGH);  // repeat 6 times
                                         digitalWrite(ledPinRight,HIGH);
                                         delay(30);
                                        //gap
                                         digitalWrite(ledPinRight,LOW);
                                         digitalWrite(ledPinRight,LOW);
                                         delay(30);
                                         j = j + 1;
                                      }
                                      j = 0;
                                      i = i + 1;
                                  }
                                  i = 0;
                              }
                              if(!digitalRead(alertKey))
                              {
                                  digitalWrite(ledPinLeft,LOW);
                                  digitalWrite(ledPinRight,LOW);   
                              }                 
                              break;
                              //End of mode three
                              //------------------------------------------
                              //Begining of mode four(normal Mode)
                              
                       case 4:
                              if (digitalRead(alertKey))
                              {
                                  delay(20);                             
                                  digitalWrite(ledPinRight,HIGH);
                                  digitalWrite(ledPinLeft,HIGH);
                                  delay(500);
                                  digitalWrite(ledPinRight,LOW);
                                  digitalWrite(ledPinLeft,LOW);;
                                  delay(500);
                              }
                              if(!digitalRead(alertKey))
                              {
                                  digitalWrite(ledPinLeft,LOW);
                                  digitalWrite(ledPinRight,LOW);   
                              }
                              break;
                              //End of mode four
                              //------------------------------------------
                              //Beginning of mode 5(random noise)
                              
                              
                }
                break;
    }
}
                                      
                                      
                                   
                                  
                                         
                                      
                                      
                                      
                                          
                                  

                                  
                                  
                                  
                                 
                                 
              
                                  
      
                                 

    
                                  
      
      
                              
    
                        
                        
