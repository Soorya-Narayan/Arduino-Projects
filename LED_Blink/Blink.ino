int ledpin = 13;
int on_time = 3000;
int off_time = 3000;

void setup(){
  pinMode(ledpin,OUTPUT);
}

void loop(){
  digitalWrite(ledpin,HIGH);
  delay(on_time);
  digitalWrite(ledpin,LOW);
  delay(off_time);
}