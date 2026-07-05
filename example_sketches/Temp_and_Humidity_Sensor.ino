#include <Arduino.h>
#include "DHT.h"
#include <U8x8lib.h>

#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const float TEMP_LOW = 15.0;
const float TEMP_HIGH = 35.0;

const float HUMIDITY_LOW = 30.0;
const float HUMIDITY_HIGH = 70.0;

const char* getAirStatus(float temp, float humi);

void setup() {
  Serial.begin(9600);
  dht.begin();

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  u8x8.clearDisplay();
  u8x8.setCursor(0, 0);
  u8x8.print("Air Sensor");
}

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  u8x8.clearDisplay();
  u8x8.setCursor(0, 0);
  u8x8.print("Air Sensor");

  if (isnan(temp) || isnan(humi)) {
    Serial.println("DHT sensor error");

    u8x8.setCursor(0, 2);
    u8x8.print("Sensor error");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C | Humidity: ");
  Serial.print(humi);
  Serial.print(" % | Status: ");
  Serial.println(getAirStatus(temp, humi));

  u8x8.setCursor(0, 2);
  u8x8.print("Temp:");
  u8x8.print(temp, 1);
  u8x8.print("C");

  u8x8.setCursor(0, 3);
  u8x8.print("Hum:");
  u8x8.print(humi, 1);
  u8x8.print("%");

  u8x8.setCursor(0, 5);
  u8x8.print(getAirStatus(temp, humi));

  delay(2000);
}

const char* getAirStatus(float temp, float humi) {
  if (temp > TEMP_HIGH) {
    return "Very hot";
  }
  else if (temp < TEMP_LOW) {
    return "Quite cold";
  }
  else if (humi < HUMIDITY_LOW) {
    return "Air dry";
  }
  else if (humi > HUMIDITY_HIGH) {
    return "Very humid";
  }
  else {
    return "Air OK";
  }
}
