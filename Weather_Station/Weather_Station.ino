#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display TWI address
#define OLED_ADDR   0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 Sensor settings
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 Gas Sensor
#define MQ2_PIN A0

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Weather Station");
  display.display();
  delay(2000);

  // Initialize DHT sensor
  dht.begin();
  Serial.println(F("DHTxx test!"));
}

void loop() {
  // Read humidity and temperature values from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read gas sensor value
  int gasValue = analogRead(MQ2_PIN);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display Temperature on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather Station");
  display.setCursor(0, 25); // Move the text further down
  display.print("Temp: ");
  display.print(temperature);
  display.println(" *C");
  display.display();
  delay(2000);

  // Display Humidity on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather Station");
  display.setCursor(0, 25); // Move the text further down
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  display.display();
  delay(2000);

  // Display Gas Value on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather Station");
  display.setCursor(0, 25); // Move the text further down
  display.print("Gas: ");
  display.print(gasValue);
  display.println(" ppm");
  display.display();
  delay(2000);

  // Print values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, ");
  Serial.print("Gas: ");
  Serial.print(gasValue);
  Serial.println(" ppm");

  // Wait a few seconds between measurements.
  delay(2000);
}
