int ledpin = 13;        // LED connected to digital pin 13
int on_time = 3000;     // Time (in milliseconds) the LED remains ON
int off_time = 3000;    // Time (in milliseconds) the LED remains OFF

void setup() {
  pinMode(ledpin, OUTPUT);  // Set the LED pin as an output
}

void loop() {
  digitalWrite(ledpin, HIGH);  // Turn the LED on
  delay(on_time);              // Wait for the specified ON time
  digitalWrite(ledpin, LOW);   // Turn the LED off
  delay(off_time);             // Wait for the specified OFF time
}
