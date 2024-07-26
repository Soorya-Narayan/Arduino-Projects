#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance of the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int menuIndex = 0;
const int menuLength = 3;
const char* menuItems[] = {"Option 1", "Option 2", "Option 3"};

// Buzzer module pin
const int buzzerPin = 10;

void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C is the I2C address of the OLED
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Menu System");
  display.display();
  delay(1000);

  // Initialize the buzzer pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'A': // Up
        menuIndex = (menuIndex - 1 + menuLength) % menuLength;
        playTone(261);  // Play C4 (261 Hz)
        break;
      case 'B': // Down
        menuIndex = (menuIndex + 1) % menuLength;
        playTone(293);  // Play D4 (293 Hz)
        break;
      case 'C': // Select
        handleSelection(menuIndex);
        playTone(329);  // Play E4 (329 Hz)
        break;
      case 'D': // Play tune
        playTune();
        break;
    }
    displayMenu();
  }
}

void displayMenu() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Menu:");
  for (int i = 0; i < menuLength; i++) {
    if (i == menuIndex) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Inverse
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(0, 10 + i * 10);
    display.println(menuItems[i]);
    display.setTextColor(SSD1306_WHITE); // Reset to normal
  }
  display.display();
}

void handleSelection(int index) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Selected: ");
  display.println(menuItems[index]);
  display.display();
  delay(1000);
}

void playTone(int frequency) {
  tone(buzzerPin, frequency);  // Play the specified frequency
  delay(200);                  // Wait for 200 ms
  noTone(buzzerPin);           // Stop the tone
}

void playTune() {
  int melody[] = {
    262, 294, 330, 349, 392, 440, 494, 523  // Frequencies for a simple melody
  };
  int duration[] = {
    300, 300, 300, 300, 300, 300, 300, 300  // Duration for each note
  };
  
  for (int i = 0; i < 8; i++) {
    tone(buzzerPin, melody[i]);
    delay(duration[i]);
    noTone(buzzerPin);
    delay(50); // Short pause between notes
  }
}
