unsigned long myTime;
const int ledPin = LED_BUILTIN;
void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop(){
  Serial.print("Time:");
  myTime = millis();
  Serial.println(myTime);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
