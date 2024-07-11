#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop() {
  scrollText("Welcome to", 0, 300, 500);
  scrollText("Arduino World", 1, 300, 500);
  delay(1000);
  lcd.clear();

  scrollText("Have a great", 0, 300, 500);
  scrollText("day!", 1, 300, 500);
  delay(1000);
  lcd.clear();
}

void scrollText(String message, int row, int scrollDelay, int charDelay) {
  // Print the entire message at once and wait before scrolling
  lcd.setCursor(0, row);
  lcd.print(message);
  delay(charDelay);

  // Scroll the text until it disappears from the screen
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.scrollDisplayLeft();
    delay(scrollDelay);
  }

  // Clear the display after scrolling
  lcd.clear();
}
