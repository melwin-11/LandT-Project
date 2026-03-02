#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT Setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Light Sensor DO
#define LIGHT_PIN 27

void setup() {

  Serial.begin(115200);   // For debugging
  pinMode(LIGHT_PIN, INPUT);
  dht.begin();

  // OLED start
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not detected!");
    while(1); // Stop here if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int lightState = digitalRead(LIGHT_PIN);

  display.clearDisplay();

  display.setCursor(0,0);
  display.print("Temp: ");
  if(isnan(temp))
    display.print("Err");
  else {
    display.print(temp);
    display.println(" C");
  }

  display.setCursor(0,20);
  display.print("Humidity: ");
  if(isnan(hum))
    display.print("Err");
  else {
    display.print(hum);
    display.println(" %");
  }

  display.setCursor(0,40);
  display.print("Light: ");

  if(lightState == LOW)
    display.print("Bright");
  else
    display.print("Dark");

  display.display();

  delay(2000);
}