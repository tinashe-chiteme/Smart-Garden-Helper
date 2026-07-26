#include <Arduino.h>
#include "DHT.h"
#include <U8x8lib.h>


// SMART GARDEN HELPER
// Grove Beginner Kit + External Moisture Sensor

// Pin connections

#define DHTPIN 3
#define DHTTYPE DHT11

const int BUTTON_PIN = 6;
const int LIGHT_PIN = A6;
const int MOISTURE_PIN = A2;

// If the button works backwards, change HIGH to LOW.
const int BUTTON_ACTIVE_LEVEL = HIGH;

// Calibration values
// These will be updated after testing with learners.


// Light sensor raw values
const int LIGHT_DARK_RAW = 0;
const int LIGHT_BRIGHT_RAW = 740;

// Moisture sensor raw values
const int MOISTURE_DRY_RAW = 0;
const int MOISTURE_WET_RAW = 821;

// Thresholds
// These are the "meaning" rules from Day 2.
// Learners will help choose these.


const int LIGHT_LOW = 30;
const int LIGHT_HIGH = 80;

const int MOISTURE_LOW = 30;
const int MOISTURE_HIGH = 80;

const float TEMP_LOW = 15.0;
const float TEMP_HIGH = 35.0;

const float HUMIDITY_LOW = 30.0;
const float HUMIDITY_HIGH = 70.0;


// Objects

DHT dht(DHTPIN, DHTTYPE);
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);


// OLED states

int screenState = 0;
const int NUMBER_OF_SCREENS = 5;

// 0 = Overview
// 1 = Air: temperature + humidity
// 2 = Light
// 3 = Soil moisture
// 4 = Plant advice


// Sensor values

float temperature = 0.0;
float humidity = 0.0;
bool airSensorOK = false;

int rawLight = 0;
int lightPercent = 0;

int rawMoisture = 0;
int moisturePercent = 0;

// Button and timing

bool previousButtonPressed = false;

unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 250;

unsigned long lastSensorReadTime = 0;
const unsigned long sensorReadInterval = 2000;

unsigned long lastDisplayUpdateTime = 0;
const unsigned long displayUpdateInterval = 1000;

bool displayNeedsUpdate = true;

// Function declarations

void readSensors();
void handleButton();
void updateSensorsIfNeeded();
void updateDisplayIfNeeded();

const char* getAirStatus();
const char* getLightStatus();
const char* getMoistureStatus();
const char* getPlantAdvice();

void showCurrentScreen();
void showOverviewScreen();
void showAirScreen();
void showLightScreen();
void showMoistureScreen();
void showAdviceScreen();

void printToSerial();


// SETUP

void setup() {
  Serial.begin(9600);
  Serial.println("Smart Garden Helper Starting...");

  pinMode(BUTTON_PIN, INPUT);

  dht.begin();

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  u8x8.clearDisplay();
  u8x8.setCursor(0, 0);
  u8x8.print("Smart Garden");
  u8x8.setCursor(0, 2);
  u8x8.print("Starting...");
  delay(1500);

  readSensors();
  showCurrentScreen();
}


// LOOP

void loop() {
  handleButton();
  updateSensorsIfNeeded();
  updateDisplayIfNeeded();
}


// Read all sensors

void readSensors() {
  float newTemp = dht.readTemperature();
  float newHumidity = dht.readHumidity();

  if (isnan(newTemp) || isnan(newHumidity)) {
    airSensorOK = false;
  } else {
    airSensorOK = true;
    temperature = newTemp;
    humidity = newHumidity;
  }

  rawLight = analogRead(LIGHT_PIN);
  lightPercent = map(rawLight, LIGHT_DARK_RAW, LIGHT_BRIGHT_RAW, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);

  rawMoisture = analogRead(MOISTURE_PIN);
  moisturePercent = map(rawMoisture, MOISTURE_DRY_RAW, MOISTURE_WET_RAW, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  printToSerial();
}


// Update sensors every few seconds

void updateSensorsIfNeeded() {
  if (millis() - lastSensorReadTime >= sensorReadInterval) {
    readSensors();
    lastSensorReadTime = millis();
    displayNeedsUpdate = true;
  }
}


// Update OLED

void updateDisplayIfNeeded() {
  if (displayNeedsUpdate || millis() - lastDisplayUpdateTime >= displayUpdateInterval) {
    showCurrentScreen();
    lastDisplayUpdateTime = millis();
    displayNeedsUpdate = false;
  }
}


// Button changes OLED state

void handleButton() {
  bool currentButtonPressed = (digitalRead(BUTTON_PIN) == BUTTON_ACTIVE_LEVEL);

  if (currentButtonPressed && !previousButtonPressed) {
    if (millis() - lastButtonPressTime > debounceDelay) {
      screenState++;

      if (screenState >= NUMBER_OF_SCREENS) {
        screenState = 0;
      }

      displayNeedsUpdate = true;
      lastButtonPressTime = millis();
    }
  }

  previousButtonPressed = currentButtonPressed;
}


// Meaning functions
// These turn numbers into messages.

const char* getAirStatus() {
  if (!airSensorOK) {
    return "Air error";
  }
  else if (temperature > TEMP_HIGH) {
    return "Very hot";
  }
  else if (temperature < TEMP_LOW) {
    return "Quite cold";
  }
  else if (humidity < HUMIDITY_LOW) {
    return "Air dry";
  }
  else if (humidity > HUMIDITY_HIGH) {
    return "Very humid";
  }
  else {
    return "Air OK";
  }
}

const char* getLightStatus() {
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

const char* getMoistureStatus() {
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

const char* getPlantAdvice() {
  if (!airSensorOK) {
    return "Check air sensor";
  }
  else if (moisturePercent < MOISTURE_LOW) {
    return "Water plant";
  }
  else if (moisturePercent > MOISTURE_HIGH) {
    return "Too much water";
  }
  else if (lightPercent < LIGHT_LOW) {
    return "Needs light";
  }
  else if (lightPercent > LIGHT_HIGH) {
    return "Very bright";
  }
  else if (temperature > TEMP_HIGH) {
    return "Too hot";
  }
  else if (temperature < TEMP_LOW) {
    return "Too cold";
  }
  else if (humidity < HUMIDITY_LOW) {
    return "Air too dry";
  }
  else if (humidity > HUMIDITY_HIGH) {
    return "Air humid";
  }
  else {
    return "Plant OK";
  }
}


// Choose OLED screen

void showCurrentScreen() {
  u8x8.clearDisplay();

  switch (screenState) {
    case 0:
      showOverviewScreen();
      break;

    case 1:
      showAirScreen();
      break;

    case 2:
      showLightScreen();
      break;

    case 3:
      showMoistureScreen();
      break;

    case 4:
      showAdviceScreen();
      break;

    default:
      screenState = 0;
      showOverviewScreen();
      break;
  }
}


// Screen 0: Overview

void showOverviewScreen() {
  u8x8.setCursor(0, 0);
  u8x8.print("Smart Garden");

  /*u8x8.setCursor(0, 1);
  u8x8.print("Air:");
  u8x8.print(getAirStatus());

  u8x8.setCursor(0, 2);
  u8x8.print("Light:");
  u8x8.print(lightPercent);
  u8x8.print("%");

  u8x8.setCursor(0, 4);
  u8x8.print("Soil:");
  u8x8.print(moisturePercent);
  u8x8.print("%");
  */
  u8x8.setCursor(0, 1);
  u8x8.print(getPlantAdvice());

  u8x8.setCursor(0, 2);
  u8x8.print(":)");

  u8x8.setCursor(0, 3);
  u8x8.print("Btn: next");
}


// Screen 1: Air

void showAirScreen() {
  u8x8.setCursor(0, 0);
  u8x8.print("Air Conditions");

  if (!airSensorOK) {
    u8x8.setCursor(0, 2);
    u8x8.print("DHT error");
    u8x8.setCursor(0, 4);
    u8x8.print("Check sensor");
    u8x8.setCursor(0, 7);
    u8x8.print("Btn: next");
    return;
  }

  u8x8.setCursor(0, 2);
  u8x8.print("Temp:");
  u8x8.print(temperature, 1);
  u8x8.print("C");

  u8x8.setCursor(0, 3);
  u8x8.print("Hum:");
  u8x8.print(humidity, 1);
  u8x8.print("%");

  u8x8.setCursor(0, 5);
  u8x8.print(getAirStatus());

}


// Screen 2: Light

void showLightScreen() {
  u8x8.setCursor(0, 0);
  u8x8.print("Light Level");

  u8x8.setCursor(0, 2);
  u8x8.print("Raw:");
  u8x8.print(rawLight);

  u8x8.setCursor(0, 3);
  u8x8.print("Light:");
  u8x8.print(lightPercent);
  u8x8.print("%");

  u8x8.setCursor(0, 5);
  u8x8.print(getLightStatus());

}


// Screen 3: Moisture

void showMoistureScreen() {
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
  u8x8.print(getMoistureStatus());

}


// Screen 4: Advice

void showAdviceScreen() {
  u8x8.setCursor(0, 0);
  u8x8.print("Plant Advice");

  u8x8.setCursor(0, 1);
  u8x8.print(getPlantAdvice());

  u8x8.setCursor(0, 2);
  u8x8.print("Based on:");

  u8x8.setCursor(0, 3);
  u8x8.print("Air Light Soil");

}


// Serial debugging

void printToSerial() {
  Serial.print("Screen:");
  Serial.print(screenState);

  Serial.print(" | Temp:");
  if (airSensorOK) {
    Serial.print(temperature);
    Serial.print("C");
  } else {
    Serial.print("ERR");
  }

  Serial.print(" | Hum:");
  if (airSensorOK) {
    Serial.print(humidity);
    Serial.print("%");
  } else {
    Serial.print("ERR");
  }

  Serial.print(" | Light raw:");
  Serial.print(rawLight);
  Serial.print(" | Light:");
  Serial.print(lightPercent);
  Serial.print("%");

  Serial.print(" | Moist raw:");
  Serial.print(rawMoisture);
  Serial.print(" | Moist:");
  Serial.print(moisturePercent);
  Serial.println("%");
}

