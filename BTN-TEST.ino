/*This is a tactile pushbutton code for bistable latch (led on/off) circuit
with 300 millisecond functional delay for prevent debouncing and we use
internal pullup resitors for greater efficiency and a 0.1uf ceramic capacitor 
for smoothing the mechanical vibration and spark
we also can use a 1meg ohm resistor parallely with the button to prevent the 
nano vibrations depending on load fluctuations (provides greater stability to the
circuit*/

#define ACTIVATED LOW

const int ledPin = 2;
const int buttonPin = 3;
boolean flag = false;  //default value


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); //activated input pullup resistors
  
}

void loop() {
  if((digitalRead(buttonPin) == ACTIVATED) && flag == false){
    delay(300);
    digitalWrite(ledPin, HIGH);
    flag = true;
  }
  if((digitalRead(buttonPin) == ACTIVATED) && flag == true){
    delay(300);
    digitalWrite(ledPin, LOW);
    flag = false;
  }

}
