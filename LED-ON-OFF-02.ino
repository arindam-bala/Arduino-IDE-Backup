//New and improved button press formula

const int LED = 3;
const int BUTTON = 2;

int val = 0;
int old_val = 0;
int state = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}
void loop(){
  val = digitalRead(BUTTON);
  Serial.println(val);

  if((val == HIGH)&&(old_val == LOW)){
    Serial.print("val = ");
    Serial.println(val);
    Serial.print("old_val = ");
    Serial.println(old_val);
    state = 1-state;
    Serial.print("state = ");
    Serial.println(state);
   
  delay(100);
  }
  old_val = val;
//  Serial.print("old_val after assigning = ");
//  Serial.println(old_val);
  if(state == 1){
     digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }
}
