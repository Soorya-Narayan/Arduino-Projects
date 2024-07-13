int sensor = 2;
int led = 13;
boolean is_on = false;

void setup(){
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop(){
  int data = digitalRead(sensor);

  if(data == 1){
    if(is_on == true){
      digitalWrite(led, LOW);
      is_on = false;
    }
    else{
      digitalWrite(led, HIGH);
      is_on = true;
    }
  }
}