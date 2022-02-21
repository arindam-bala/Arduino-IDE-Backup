#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Define analog input
#define ANALOG_IN_PIN A0

//Function Prototype
void displaydata();

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
int qPerc;

// Floats for resistor values in divider (in ohms)
float R1 = 9800.0;
float R2 = 9800.0; 

// Float for Reference Voltage
float ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;

void setup(){
   // Setup Serial Monitor
   //Serial.begin(9600);
   //Serial.println("DC Voltage Test");
   display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
}

void loop(){
   // Read the Analog Input
   adc_value = analogRead(ANALOG_IN_PIN);
   
   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
   // Calculate voltage at divider input
   in_voltage = adc_voltage / (R2/(R1+R2)); 

   //Calculate battery charge 
   qPerc = ((in_voltage - 7.20)/0.80)*100;
   if(qPerc < 0){
    display.clearDisplay();
    display.print("LOW BATTERY");
   }
   
  // Print results to Serial Monitor to 2 decimal places
  //Serial.print("Input Voltage = ");
  //Serial.println(in_voltage, 2);
  displaydata();

  // Short delay
  delay(200);
}

void displaydata() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(qPerc);
  display.print(" %");
 
  display.display();
}
