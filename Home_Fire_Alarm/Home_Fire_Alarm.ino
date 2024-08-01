#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define pins
#define MQ2_PIN A0
#define FLAME_PIN 2
#define BUZZER_PIN 8

// OLED display TWI address
#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize MQ-2 sensor
  pinMode(MQ2_PIN, INPUT);

  // Initialize flame sensor
  pinMode(FLAME_PIN, INPUT);

  // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);  // Make sure buzzer is off initially

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int gasSensorValue = analogRead(MQ2_PIN);
  int flameSensorValue = digitalRead(FLAME_PIN);
  float voltage = gasSensorValue * (5.0 / 1023.0);

  // Display heading and sensor values on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Home Fire Alarm");

  display.setCursor(0, 16);
  display.print("Gas Reading:");
  display.setCursor(80, 16);
  display.print(gasSensorValue);

  display.setCursor(0, 32);
  display.print("Voltage:");
  display.setCursor(80, 32);
  display.print(voltage, 2); // Display voltage with 2 decimal places

  display.setCursor(0, 48);
  display.print("Flame:");
  display.setCursor(80, 48);
  display.print(flameSensorValue == HIGH ? "No" : "Yes");

  display.display();

  // Check if gas level or flame is detected
  if (gasSensorValue > 50 || flameSensorValue == LOW) { // Adjust threshold for gas sensor as needed
    tone(BUZZER_PIN, 1000); // Play tone at 1000 Hz
  } else {
    noTone(BUZZER_PIN); // Turn off tone
  }

  delay(1000); // Adjust delay as needed
}
