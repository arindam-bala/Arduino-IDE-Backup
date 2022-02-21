//LAST UPPDATED BUG FREE
//WITHOUT BATTERY CODE
//WITHOUT ON/OFF CODE
//WITHOUT DISPLAY UNIT
#include <Wire.h>
#include <EEPROM.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define ACTIVATED LOW
#define ANALOG_IN_PIN A0

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

//BUTTONS
const int playPause = 2;
const int fastNext = 3;
const int fastPrev = 4;
const int volUp = 5;
const int volDn = 6 ;
const int eqMode = 7;

// VOLTAGE STORAGES
float adc_voltage = 0.0;
float in_voltage = 0.0;
int qPerc;

// RESISTOR VALUES
float R1 = 9800.0;
float R2 = 9800.0; 

// INTERNAL REFERENCE
float ref_voltage = 5.0;

// INTEGER VALUE OF Vin(A0)
int adc_value = 0;

//FLAGS
boolean playFlag = true;
boolean fastFlag = false;
//int eqFlag = 0;

//DATA_HOLDERS
int fileCount;
int currFile = EEPROM.read(1);
int copyTrack;
int currTrack;
int volIndex = EEPROM.read(2);
int eqIndex = EEPROM.read(3);

//COUNTERS
int i; //Track counter

void BMS();

void setup(){
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  Serial.println("DIGITAL AUDIO PLAYER");
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("ERROR!->REBOOT");
    while(true);
  }
  Serial.println(F("READY TO PLAY"));

  //DEFAULT SETUP
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  fileCount = myDFPlayer.readFileCounts();
  myDFPlayer.enableDAC();

  //PINMODE SETUP
  pinMode(playPause, INPUT_PULLUP);
  pinMode(fastNext, INPUT_PULLUP);
  pinMode(fastPrev, INPUT_PULLUP);
  pinMode(volUp, INPUT_PULLUP);
  pinMode(volDn, INPUT_PULLUP);
  pinMode(eqMode, INPUT_PULLUP);
  

  //DEFAULT FILE ADJUSTMENT
  currTrack = currFile;

  //DEFAULT VOLUME ADJUSTMENT
  if((volIndex <= 30) && (volIndex >= 0)){
    volIndex = 15;
    EEPROM.write(2, volIndex);
  }

  //DEFAULT EQUILIZER ADJUSTMENT
  if(eqIndex == 0){
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    Serial.println("NORMAL");
  }
  if(eqIndex == 2){
    myDFPlayer.EQ(DFPLAYER_EQ_POP);
    Serial.println("ROCK");
  }
  if(eqIndex == 3){
    myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
    Serial.println("SOFT-BASS");
  }
  if(eqIndex == 4){
    myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
    Serial.println("MID");
  }
  if(eqIndex == 5){
    myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
    Serial.println("VOCAL");
  }
  if(eqIndex == 6){
    myDFPlayer.EQ(DFPLAYER_EQ_BASS);
    Serial.println("LOUD");
  }
  myDFPlayer.volume(volIndex);  //Set volume value (15)

   myDFPlayer.play(currFile);
   delay(200);
   Serial.println(currFile);
   playFlag = true;
  
}
void loop(){
  if((digitalRead(playPause) == ACTIVATED) && playFlag == false){
    delay(300);
    Serial.println("PLAYING");
    myDFPlayer.start();
    delay(10);
    playFlag = true;
  }
  
  if((digitalRead(playPause) == ACTIVATED) && playFlag == true){
    delay(300);
    Serial.println("PAUSED");
    myDFPlayer.pause();
    delay(10);
    playFlag = false;
  }

  if(digitalRead(fastNext) == ACTIVATED){
    delay(300);
    currTrack = currTrack + 1;
    for(i = currTrack; i < (currTrack+1); ++i){
      if(i > fileCount){
        currTrack = 1;
        copyTrack = 1;
      }else{
        copyTrack = i;
      }
      currFile = copyTrack;
      fastFlag = true;
      Serial.println(currFile);
      EEPROM.write(1, currFile);
    }
  } 

  if(digitalRead(fastPrev) == ACTIVATED){
    delay(300);
    currTrack = currTrack - 1;
    for(i = currTrack; i > (currTrack-1); --i){
      if(i < 1){
        currTrack = fileCount;
        copyTrack = fileCount;
      }else{
        copyTrack = i;  
      }
    }
    currFile = copyTrack;
    fastFlag = true;
    Serial.println(currFile);
    EEPROM.write(1, currFile);
  }

  if((digitalRead(fastNext)!= ACTIVATED) && (digitalRead(fastPrev)!= ACTIVATED) && fastFlag == true){
    delay(100);
    myDFPlayer.play(currFile);
    fastFlag = false;
  }
  
  
  if(digitalRead(volUp) == ACTIVATED){
    delay(300);
    if(volIndex <=30){
      volIndex = volIndex + 1;
      if(volIndex > 20){
        if(volIndex > 30){
          volIndex = 0;
        }
        Serial.println("HI-VOLUME");  
      }
    }
    myDFPlayer.volume(volIndex);
    delay(10);
    Serial.println(volIndex);
    EEPROM.write(2,volIndex); 
  }
  if(digitalRead(volDn) == ACTIVATED){
    delay(300);
    if((volIndex <= 30) && (volIndex > 0)){
      volIndex = volIndex - 1;
       myDFPlayer.volume(volIndex);
       delay(10);
       if(volIndex == 0){
          volIndex = 15;
          myDFPlayer.volume(volIndex);
       }
    }
    Serial.println(volIndex);
    EEPROM.write(2, volIndex);
  }

  if(digitalRead(eqMode) == ACTIVATED){
    delay(300);
    if((eqIndex > 0) && (eqIndex < 6)){
      eqIndex = eqIndex + 1;  
    }
    switch(eqIndex){
      case 2:
         myDFPlayer.EQ(DFPLAYER_EQ_POP);
         Serial.println("ROCK");
         EEPROM.write(3, eqIndex);
         break;
      case 3:
         myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
         Serial.println("SOFT-BASS");
         EEPROM.write(3, eqIndex);
         break;
      case 4:
         myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
         Serial.println("MID");
         EEPROM.write(3, eqIndex);
         break;
      case 5:
         myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
         Serial.println("VOCAL");
         EEPROM.write(3, eqIndex);
         break;
      case 6:
         myDFPlayer.EQ(DFPLAYER_EQ_BASS);
         Serial.println("LOUD");
         EEPROM.write(3, eqIndex);
         eqIndex = 0;
         break;
      case 0:
         myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
         Serial.println("NORMAL");
         EEPROM.write(3, eqIndex);
         eqIndex = eqIndex + 1;
         break;

      default:
          break;         
    }
  }
  delay(50);
}
void BMS(){
   adc_value = analogRead(ANALOG_IN_PIN);
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   in_voltage = adc_voltage / (R2/(R1+R2)); 
   qPerc = ((in_voltage - 7.20)/0.80)*100;
   if(qPerc < 0){
    display.clearDisplay();
    display.print("LOW BATTERY");
   }
  displaydata();
  delay(200);
}
