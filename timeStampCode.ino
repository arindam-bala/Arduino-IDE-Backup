unsigned long timeStamp1 = 0;
const int btn = 2;

void setup() {
  
  pinMode(btn, INPUT_PULLUP);
//  digitalWrite(btn, HIGH);
  Serial.begin(9600);

}

void loop() {
  
  if(digitalRead(btn) == LOW){
    
    timeStamp1 = millis();
    Serial.println(timeStamp1);
    delay(300);
 } 
  
}
    
