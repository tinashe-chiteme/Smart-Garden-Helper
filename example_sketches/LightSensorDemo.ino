#include <Arduino.h>
#include <U8x8lib.h>

const int LIGHT_PIN = A6;

// Start with these, then update after testing.
const int LIGHT_DARK_RAW = 0;
const int LIGHT_BRIGHT_RAW = 740;

const int LIGHT_LOW = 30;
const int LIGHT_HIGH = 80;

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const char* getLightStatus(int lightPercent);

void setup() {
  Serial.begin(9600);

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  u8x8.clearDisplay();
  u8x8.setCursor(0, 0);
  u8x8.print("Light Sensor");
}

void loop() {
  int rawLight = analogRead(LIGHT_PIN);

  int lightPercent = map(rawLight, LIGHT_DARK_RAW, LIGHT_BRIGHT_RAW, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);

  Serial.print("Raw Light: ");
  Serial.print(rawLight);
  Serial.print(" | Light: ");
  Serial.print(lightPercent);
  Serial.print("% | Status: ");
  Serial.println(getLightStatus(lightPercent));

  u8x8.clearDisplay();

  u8x8.setCursor(0, 0);
  u8x8.print("Light Sensor");

  u8x8.setCursor(0, 2);
  u8x8.print("Raw:");
  u8x8.print(rawLight);

  u8x8.setCursor(0, 3);
  u8x8.print("Light:");
  u8x8.print(lightPercent);
  u8x8.print("%");

  u8x8.setCursor(0, 5);
  u8x8.print(getLightStatus(lightPercent));

  delay(500);
}

const char* getLightStatus(int lightPercent) {
  if (lightPercent < LIGHT_LOW) {
    return "Too dark";
  }
  else if (lightPercent > LIGHT_HIGH) {
    return "Very bright";
  }
  else {
    return "Light OK";
  }
}
