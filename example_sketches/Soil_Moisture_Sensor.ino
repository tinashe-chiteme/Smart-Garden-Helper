#include <Arduino.h>
#include <U8x8lib.h>

const int MOISTURE_PIN = A2;

const int MOISTURE_DRY_RAW = 0;
const int MOISTURE_WET_RAW = 821;

const int MOISTURE_LOW = 30;
const int MOISTURE_HIGH = 80;

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const char* getMoistureStatus(int moisturePercent);

void setup() {
  Serial.begin(9600);

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  u8x8.clearDisplay();
  u8x8.setCursor(0, 0);
  u8x8.print("Moisture Test");
}

void loop() {
  int rawMoisture = analogRead(MOISTURE_PIN);

  int moisturePercent = map(rawMoisture, MOISTURE_DRY_RAW, MOISTURE_WET_RAW, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw Moisture: ");
  Serial.print(rawMoisture);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% | Status: ");
  Serial.println(getMoistureStatus(moisturePercent));

  u8x8.clearDisplay();

  u8x8.setCursor(0, 0);
  u8x8.print("Soil Moisture");

  u8x8.setCursor(0, 2);
  u8x8.print("Raw:");
  u8x8.print(rawMoisture);

  u8x8.setCursor(0, 3);
  u8x8.print("Moist:");
  u8x8.print(moisturePercent);
  u8x8.print("%");

  u8x8.setCursor(0, 5);
  u8x8.print(getMoistureStatus(moisturePercent));

  delay(500);
}

const char* getMoistureStatus(int moisturePercent) {
  if (moisturePercent < MOISTURE_LOW) {
    return "Needs water";
  }
  else if (moisturePercent > MOISTURE_HIGH) {
    return "Too wet";
  }
  else {
    return "Soil OK";
  }
}
