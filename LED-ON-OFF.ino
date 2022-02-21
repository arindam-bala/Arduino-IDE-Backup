const int LED = 3;
const int BUTTON = 2;

int val = 0;
int state = 0;
//This is not a good code
//Logic is not good
void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}
void loop(){
  val = digitalRead(BUTTON);
  if(val == HIGH){
    state = 1-state; //this is a flag(states between (0) and (1)
      
  }
  if(state == 1){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
