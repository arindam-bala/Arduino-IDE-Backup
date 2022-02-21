#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define ANALOG_IN_PIN A0                                  //Define Analog Input Pin
#define ACTIVATED LOW                                     //Manual Override Charging Mode  
#define DEACTIVATED HIGH                                  //Manual Override off

float adc_voltage = 0.0;                                  //Floats for ADC and Input Voltage
float in_voltage = 0.0;

float R1 = 32800.0;                                        //Resistance values 10k, 33k
float R2 = 9900.0;

float ref_voltage = 5.0;                                  //Float for reference voltage
int adc_value = 0;                                        //Integer for ADC value

const int batt_onPin = 5;
const int relay_pin = 2;
const int manual_overridePin = 4; 
boolean flag = 0;


void setup() {
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("WiFi-POWER");
  lcd.setCursor(0,1);
  lcd.print("INITIALIZING...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BATT-VOLTS: ");
  lcd.setCursor(10,1);
  lcd.print("STD-BY");
  lcd.setCursor(0,1);
  lcd.print("B+PWR:ON/");
  pinMode(batt_onPin, INPUT_PULLUP);
  pinMode(relay_pin, OUTPUT);
  pinMode(manual_overridePin, INPUT_PULLUP);
  delay(2000);
  lcd.clear();
}

void loop() {
  adc_value = analogRead(ANALOG_IN_PIN);                    //Read Analog Input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;        //Determine Voltage at ADC Input 
  in_voltage = adc_voltage / (R2/(R1+R2));                  //Calculate voltage at divider input

  lcd.setCursor(0,0);
  lcd.print("BATT-VOLTS: ");
  lcd.setCursor(12,0);
  lcd.print(in_voltage);
//  lcd.setCursor(0,1);
//  lcd.print("B+PWR:ON/");
  //----------------------------------------------------------------------------------------------
  if((in_voltage < 11.10) && (digitalRead(manual_overridePin) == DEACTIVATED) && (flag == 0)) {
    digitalWrite(relay_pin, HIGH);    //charging on
    lcd.setCursor(10,1);
    lcd.print("ATOCHG");
    delay(1000);
  }
  if((in_voltage >= 12.75) && (digitalRead(manual_overridePin) == DEACTIVATED) && (flag == 0)){
    digitalWrite(relay_pin, LOW);     //charging off
    lcd.setCursor(10,1);
    lcd.print("STD-BY");
    delay(1000);
  }
  //-----------------------------------------------------------------------------------------------
  if((digitalRead(manual_overridePin) == ACTIVATED) && flag == 0) {
    delay(300);
    flag = 1;
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(10,1);
    lcd.print("MOVCHG");
    delay(1000);
  }
  if((in_voltage >= 12.75) && (flag == 1)) {
      digitalWrite(relay_pin, LOW);
      lcd.setCursor(10,1);
      lcd.print("STD-BY");
      flag = 0;
      delay(1000);
  }
  if((digitalRead(manual_overridePin) == ACTIVATED) && flag == 1) {
    delay(300);
    flag = 0;
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(10,1);
    lcd.print("MOVOFF");
    delay(1000);
    lcd.setCursor(10,1);
    lcd.print("STD-BY");
    delay(1000);
  }
  //---------------------------------------------------------------------
 

  //---------------------------------------------------------------------
  {
    if(digitalRead(batt_onPin) == HIGH){
      lcd.setCursor(0,1);
      lcd.print("B+PWR:ON/");
      delay(300);
    }
    if(digitalRead(batt_onPin) == LOW){
      lcd.setCursor(0,1);
      lcd.print("B+PWR:OFF/");
      delay(300);
    }
  }
  //---------------------------------------------------------------------
  

   delay(2000);                                             //delay for stability
}
