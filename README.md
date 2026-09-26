# Smart Garden Helper

Arduino-based environmental monitoring and decision-support system developed
for **JCP Sensor School 2026**, partnered with the **Department of EECE** from the University of Pretoria (as our community partner) at **Moja Gabedi**.

The Smart Garden Helper integrates multiple environmental sensors into a single
embedded system that measures temperature, humidity, ambient light and soil
moisture. The system interprets these measurements using configurable
threshold-based logic and presents the resulting information and plant advice
through a multi-screen OLED interface.

This repository serves as the technical record for **Version 1.0.0**, including
the final implementation, component-level test sketches, system documentation,
engineering decisions, diagrams, images and selected project media.

---

## Overview

The Smart Garden Helper was developed as part of the JCP Sensor School 2026
community-engagement project at Moja Gabedi.

The project demonstrates how fundamental embedded-systems concepts can be
combined into a practical environmental monitoring system. Rather than simply
displaying raw sensor measurements, the system processes the measurements and
converts them into information that can be interpreted by a user.

The system monitors:

- Air temperature
- Relative humidity
- Ambient light intensity
- Soil moisture

These measurements are processed by an Arduino-compatible microcontroller and
presented through a state-based OLED interface.

The project was designed with two objectives:

1. To provide a functional embedded environmental monitoring system.
2. To demonstrate embedded-systems concepts in a form suitable for educational
   outreach.

The final implementation prioritises modularity, readability, maintainability
and practical understanding of the underlying engineering concepts.

---

## Features

- Temperature and humidity monitoring using the DHT11 sensor
- Ambient light monitoring using the Grove light sensor
- Soil moisture monitoring using the DFRobot Gravity Analog Soil Moisture
  Sensor V2
- Threshold-based environmental interpretation
- Plant advice generated from multiple environmental conditions
- Five-state OLED interface
- Push-button navigation between display states
- Software button debouncing
- Periodic sensor sampling using `millis()`
- Serial Monitor output for debugging and development
- Raw sensor readings retained alongside interpreted percentages where useful
- Modular software architecture
- Component-level testing before system integration
- Basic sensor error handling
- Experimental sensor calibration
- Version-controlled technical documentation

---

## Hardware

The final Version 1.0.0 implementation uses the following hardware:

| Component | Role | Interface / Pin |
|---|---|---|
| Seeed Studio Grove Beginner Kit for Arduino | Main embedded platform | Arduino-compatible |
| DHT11 | Temperature and humidity measurement | D3 |
| Grove Light Sensor | Ambient light measurement | A6 |
| DFRobot Gravity Analog Soil Moisture Sensor V2 | Soil moisture measurement | A2 |
| Grove OLED Display | User interface | I²C |
| Grove Push Button | OLED screen navigation | D6 |

The Grove Beginner Kit provides the primary embedded platform and integrates
several of the sensors and peripherals used by the system. The external
DFRobot soil moisture sensor extends the system with direct soil-condition
measurement.

The final hardware configuration is documented in greater detail in:

`docs/03_Hardware.md`

---

## Final Implementation

The final Version 1.0.0 implementation is located at:

`Final_Code/Implementation.ino`

The program is structured around several major responsibilities:

- Hardware initialisation
- Sensor acquisition
- Sensor data conversion
- Button handling
- OLED state management
- Environmental status interpretation
- Plant advice generation
- Periodic display and sensor updates

The main OLED interface contains five display states:

| State | Screen |
|---:|---|
| 0 | Overview |
| 1 | Air Temperature & Humidity |
| 2 | Light |
| 3 | Soil Moisture |
| 4 | Plant Advice |

A single button advances through the display states. Software debouncing is
used to prevent one physical button press from being interpreted as multiple
presses.

Sensor measurements are sampled periodically rather than continuously, while
display updates are managed independently. This allows the interface to remain
responsive while avoiding unnecessary repeated sensor reads and display
refreshes.

The system uses threshold-based decision logic to convert numerical
measurements into qualitative conditions such as:

- Air OK
- Too Hot
- Too Cold
- Air Dry
- Very Humid
- Light OK
- Too Dark
- Very Bright
- Soil OK
- Needs Water
- Too Wet

The final Plant Advice screen combines these interpreted conditions into a
higher-level recommendation.

---

## Repository Structure

```text
Smart-Garden-Helper/
│
├── Final_Code/
│   └── Implementation.ino
│
├── example_sketches/
│   ├── LightSensorDemo.ino
│   ├── Soil_Moisture_Sensor.ino
│   ├── Temp_and_Humidity_Sensor.ino
│   └── Button_and_OLED_Test.ino
│
├── docs/
│   ├── 01_Project_Overview.md
│   ├── 02_System_Architecture.md
│   ├── 03_Hardware.md
│   ├── 04_Software_Architecture.md
│   ├── 05_Modularity.md
│   ├── 06_Sensor_Calibration.md
│   ├── 07_Threshold_Logic.md
│   ├── 08_OLED_State_Logic.md
│   ├── 09_Testing_And_Debugging.md
│   ├── 10_Engineering_Decisions.md
│   ├── 11_Lessons_Learned.md
│   ├── 12_Future_Work.md
│   ├── 13_Project_History.md
│   ├── 14_Architecture_Evolution.md
│   ├── Development_Timeline.md
│   └── From_Monitoring_To_Decision_Support.md
│
├── diagrams/
│   └── System and program diagrams
│
├── images/
│   └── Project photographs and supporting images
│
├── media_files/
│   └── Selected demonstration and project media
│
├── .gitignore
├── LICENSE
└── README.md
