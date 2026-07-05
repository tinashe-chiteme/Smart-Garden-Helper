## System Architecture
# Overview

The Smart Garden Helper follows a modular embedded systems architecture designed around the flow of information from the physical environment to the user.

Rather than simply collecting sensor readings, the system continuously monitors environmental conditions, processes those measurements into meaningful information, and presents the results through a simple user interface.

The overall system can be viewed as five major stages:

1. Environmental Inputs
2. Data Acquisition
3. Decision Making
4. User Interface
5. User Interaction

Separating the system into these stages makes the software easier to understand, test, maintain and expand.

---

# High-Level Architecture

             Physical Environment
                     │
                     ▼
     ┌────────────────────────────────┐
     │            Sensors             │
     │                                │
     │ • Temperature & Humidity       │
     │ • Light                        │
     │ • Soil Moisture                │
     └────────────────────────────────┘
                     │
                     ▼
         Arduino (Grove Beginner Kit)
                     │
                     ▼
         Sensor Reading Functions
                     │
                     ▼
          Threshold Decision Logic
                     │
                     ▼
         OLED Display State Manager
                     ▲
                     │
              Push Button Input
                     │
                     ▼
                  End User

---

# Information Flow

The Smart Garden Helper operates as a continuous embedded monitoring system.

Unlike a desktop application that runs once and exits, the Arduino repeatedly executes the loop() function, allowing the system to monitor the environment continuously.

Each iteration of the program follows the same sequence:

Read Inputs

↓

Process Measurements

↓

Interpret Sensor Values

↓

Update OLED Display

↓

Wait

↓

Repeat


This repeated execution allows the Smart Garden Helper to respond whenever environmental conditions change.

---

# Stage 1: Environmental Inputs

The first stage of the system is the physical environment.

Unlike software applications that receive keyboard or mouse input, an embedded system interacts directly with the real world through sensors.

The Smart Garden Helper monitors four environmental quantities:

| Quantity          | Sensor                                         |
| ----------------- | ---------------------------------------------- |
| Air Temperature   | Grove Temperature & Humidity Sensor            |
| Relative Humidity | Grove Temperature & Humidity Sensor            |
| Ambient Light     | Grove Light Sensor                             |
| Soil Moisture     | DFRobot Gravity Analog Soil Moisture Sensor V2 |

Each sensor continuously observes one physical property and converts it into an electrical signal that can be measured by the Arduino.

The Arduino itself cannot directly detect light, moisture or temperature.

Instead, the sensors perform this conversion, allowing the microcontroller to receive digital or analogue values representing the surrounding environment.

---

# Stage 2: Data Acquisition

Once the sensors have produced electrical signals, the Arduino reads each sensor individually.

Each sensor has its own dedicated helper function responsible for acquiring data.

Conceptually, the process is:

Temperature Sensor

↓

Read Temperature

↓

Store Temperature

↓

Repeat for Remaining Sensors

---

# Stage 3: Decision Making

Raw sensor values have little meaning to most users.

For example, 'Moisture = 486' does not immediately tell someone whether the plant needs watering.

To solve this problem, the Smart Garden Helper applies threshold-based decision logic.

Each sensor reading is compared against configurable threshold values.

For example, the logic for the soil moisture sensor follows as:
Read Moisture

↓

Convert to Percentage

↓

Compare Against Thresholds

↓

Needs Water

or

Soil OK

or

Too Wet

The same principle is applied to the remaining sensors.

This stage transforms raw measurements into meaningful information that can assist the user.

---

# Stage 4: OLED Display Manager

The OLED display serves as the primary output device.

Due to the limited display size, the system does not attempt to display every sensor simultaneously.

Instead, information is divided into multiple display states.

Each display state focuses on one aspect of the garden.

In essence,
| OLED State             | Purpose                  |
| ---------------------- | ------------------------ |
| Overview               | Summary of system status |
| Temperature & Humidity | Air conditions           |
| Light                  | Ambient brightness       |
| Soil Moisture          | Soil condition           |
| Plant Advice           | Overall recommendation   |

This design keeps each screen uncluttered while making navigation straightforward.

---

# Stage 5: User Interaction

The user interacts with the Smart Garden Helper through a single push button.

Rather than controlling sensors directly, the button changes the OLED display state.

Each button press advances the interface to the next screen.

The navigation sequence is:

Overview

↓

Temperature & Humidity

↓

Light

↓

Soil Moisture

↓

Plant Advice

↓

Overview

This circular navigation pattern allows the user to access all system information with a single input device.

---

# Why a State-Based Display?

Displaying all sensor readings simultaneously would make the OLED crowded and difficult to read.

Instead, the Smart Garden Helper uses a finite state approach.

Each screen becomes one "state" of the user interface.

Benefits include:

Cleaner presentation
Easier code organisation
Simpler navigation
Improved scalability
Introduction to state-based embedded programming

Future versions could easily add additional display states without redesigning the rest of the software.

---

# Modularity within the Architecture

One of the primary design goals of the project was modularity.

Rather than writing all functionality inside a single loop(), the software was divided into helper functions responsible for specific tasks.

Conceptually, the program structure resembles:

loop()

│

├── Handle Button

├── Read Temperature & Humidity

├── Read Light Sensor

├── Read Soil Moisture

├── Process Threshold Logic

└── Update OLED Display

Each module performs one well-defined responsibility.

This separation improves maintainability and allows individual modules to be tested independently during development.

---

# Overall System Behaviour

The Smart Garden Helper continuously repeats the following cycle:

Start

↓

Read all sensors

↓

Update stored measurements

↓

Interpret sensor values

↓

Determine OLED screen

↓

Display information

↓

Check button press

↓

Change screen if required

↓

Repeat forever

This architecture allows the Smart Garden Helper to behave as a real-time environmental monitoring system while remaining simple enough to understand and extend.

---

# Design Summary

The Smart Garden Helper follows a layered architecture that separates sensing, processing, decision-making, and user interaction into distinct stages. This separation reduces software complexity, improves maintainability, and supports the modular development approach used throughout the project.

By combining multiple sensors, threshold-based decision logic, and a state-driven OLED interface, the system demonstrates how relatively simple embedded components can be integrated into a coherent monitoring platform for smart agriculture applications.
