#include <Arduino.h>
#include <U8x8lib.h>

const int BUTTON_PIN = 6;
const int BUTTON_ACTIVE_LEVEL = HIGH;

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

int screenState = 0;
const int NUMBER_OF_SCREENS = 4;

bool previousButtonPressed = false;
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 250;

void showScreen();

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  showScreen();
}

void loop() {
  bool currentButtonPressed = (digitalRead(BUTTON_PIN) == BUTTON_ACTIVE_LEVEL);

  if (currentButtonPressed && !previousButtonPressed) {
    if (millis() - lastButtonPressTime > debounceDelay) {
      screenState++;

      if (screenState >= NUMBER_OF_SCREENS) {
        screenState = 0;
      }

      showScreen();
      lastButtonPressTime = millis();

      Serial.print("Screen state: ");
      Serial.println(screenState);
    }
  }

  previousButtonPressed = currentButtonPressed;
}

void showScreen() {
  u8x8.clearDisplay();

  u8x8.setCursor(0, 0);
  u8x8.print("State Test");

  u8x8.setCursor(0, 2);

  if (screenState == 0) {
    u8x8.print("Overview");
  }
  else if (screenState == 1) {
    u8x8.print("Air Screen");
  }
  else if (screenState == 2) {
    u8x8.print("Light Screen");
  }
  else if (screenState == 3) {
    u8x8.print("Soil Screen");
  }

  u8x8.setCursor(0, 7);
  u8x8.print("Press button");
}
