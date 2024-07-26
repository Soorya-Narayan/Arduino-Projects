# Menu System with OLED Display, Keypad, and Buzzer

## Overview

This Arduino project demonstrates a menu system using an OLED display, a 4x4 matrix keypad, and a buzzer. The menu system allows users to navigate through options, select them, and play a simple melody using the buzzer.

## Components

- **Arduino Board** (e.g., Arduino Uno)
- **OLED Display** (SSD1306, 128x64 pixels)
- **4x4 Keypad**
- **Buzzer**
- **Jumper Wires**
- **Breadboard** (optional)

## Libraries Used

- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Keypad](https://github.com/Chris--A/Keypad)

## Connections

### OLED Display
- **SDA** to Arduino **A4**
- **SCL** to Arduino **A5**
- **VCC** to Arduino **5V**
- **GND** to Arduino **GND**

### Keypad
- **Rows** to Arduino pins **9, 8, 7, 6**
- **Columns** to Arduino pins **5, 4, 3, 2**

### Buzzer
- **Pin** to Arduino pin **10**

## Usage

1. **Up/Down Navigation**: Use the 'A' and 'B' keys on the keypad to navigate through the menu options.
2. **Select Option**: Press the 'C' key to select an option. The selected option will be displayed on the OLED.
3. **Play Tune**: Press the 'D' key to play a simple melody on the buzzer.

## Code

The code initializes the OLED display and keypad, handles menu navigation, displays selected options, and plays tones using the buzzer. 

To run the code, upload the `Menu_System_OLED_Keypad_Buzzer.ino` file to your Arduino board using the Arduino IDE.



