
## Soil Moisture Detector


This project is a Soil Moisture Detector built using an Arduino Uno, a moisture sensor, jumper cables, an LCD display, and Arduino IDE code. The detector measures the moisture level in the soil and displays the readings on the LCD screen. It is a simple and efficient way to monitor the soil moisture content for gardening and agricultural purposes.


## Components Needed

- Arduino board (e.g., Uno, Nano, etc.)
- Soil Moisture Sensor
- LCD Display (16x2)
- Breadboard
- Jumper wires
- Arduino IDE (Software)
## Arduino Code

**Upload the following Arduino code to your Arduino Uno:**

```cpp
#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Soil moisture sensor pin
int sensorPin = A0;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD
  lcd.print("Soil Moisture");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read the soil moisture sensor value
  int sensorValue = analogRead(sensorPin);
  // Convert the analog value to percentage
  int moisturePercent = map(sensorValue, 0, 1023, 0, 100);
  
  // Display the moisture level on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%");
  
  delay(1000);
}

```


## How to Use

1. Connect the Arduino Uno to your computer using a USB cable.
2. Open the Arduino IDE and copy the code into a new sketch.
3. Select the appropriate board and port from the Tools menu.
4. Upload the code to the Arduino.
5. Once the code is uploaded, the LCD display will show the soil moisture level as a percentage.
6. Insert the soil moisture sensor into the soil to get real-time readings.



## 🔗 Links

[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](www.linkedin.com/in/sooryanarayan)
[![twitter](https://img.shields.io/badge/twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://x.com/knowsoorya)
[![Medium](https://img.shields.io/badge/Medium-12100E?style=for-the-badge&logo=medium&logoColor=white)](https://medium.com/@sooryah)
[![Instagram](https://img.shields.io/badge/Instagram-%23E4405F.svg?style=for-the-badge&logo=Instagram&logoColor=white)](https://www.instagram.com/sooryeahhh/)
