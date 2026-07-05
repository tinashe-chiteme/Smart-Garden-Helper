## Hardware
# Overview

The Smart Garden Helper was implemented using the Seeed Studio Grove Beginner Kit for Arduino together with an external DFRobot Gravity Analog Soil Moisture Sensor V2. The Grove Beginner Kit provided an integrated platform containing the microcontroller, OLED display, environmental sensors, and user input components, while the external soil moisture sensor extended the system's ability to monitor below-ground conditions.

The selection of these components allowed the project to demonstrate several fundamental concepts in embedded systems engineering, including sensor integration, analogue and digital interfacing, user interaction, and environmental monitoring.

Throughout development, emphasis was placed on keeping the hardware architecture simple, modular, and easy to understand, making it suitable for both engineering demonstrations and educational outreach.

---

# Hardware Architecture

The Smart Garden Helper consists of five major hardware subsystems:
| Subsystem                                      | Purpose                                                                                           |
| ---------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| Grove Beginner Kit                             | Main embedded platform containing the Arduino-compatible microcontroller and built-in peripherals |
| Temperature & Humidity Sensor                  | Measures ambient environmental conditions                                                         |
| Light Sensor                                   | Measures ambient light intensity                                                                  |
| OLED Display                                   | Displays sensor information and system status                                                     |
| Push Button                                    | Allows navigation between OLED display screens                                                    |
| DFRobot Gravity Analog Soil Moisture Sensor V2 | Measures soil moisture content                                                                    |

The relationship between these components is illustrated below.

                     User
                       │
                       │
                 Push Button
                       │
                       ▼
             Grove Beginner Kit
       (Arduino-compatible MCU)
          │      │      │
          │      │      │
          ▼      ▼      ▼
 Temperature   Light   Soil Moisture
& Humidity    Sensor      Sensor
      │
      ▼
   OLED Display

The Grove Beginner Kit forms the centre of the system, collecting data from the sensors, processing the information, and presenting the results on the OLED display.

---

## Grove Beginner Kit for Arduino
# Purpose

The Grove Beginner Kit serves as the primary embedded development platform used throughout the project.

Unlike a traditional Arduino setup requiring extensive wiring, the Grove Beginner Kit integrates many commonly used sensors directly onto the PCB, allowing development to focus on software architecture rather than hardware assembly.

This significantly reduced development time while maintaining exposure to real embedded systems concepts.

---

# Components Used

The following onboard peripherals were utilised:

Temperature & Humidity Sensor
Light Sensor
OLED Display
Push Button

Other peripherals available on the board were intentionally not used to maintain a focused project scope.

---

# Benefits

The Grove Beginner Kit offered several advantages:

Reduced wiring complexity
Reliable sensor integration
Faster prototyping
Simplified troubleshooting
Ideal platform for educational demonstrations

These characteristics made the kit particularly well suited for the Smart Garden Helper.

---

## Temperature & Humidity Sensor
# Purpose

The Temperature & Humidity Sensor monitors the surrounding air conditions.

These two measurements are important indicators of the environmental conditions experienced by plants.

Rather than treating temperature and humidity as separate modules, they were combined into a single software module because both measurements originate from the same physical sensor and describe the surrounding atmosphere.

# Measurements

The sensor provides:

Air temperature (°C)
Relative humidity (%)

These values are updated periodically and displayed on the OLED.

# Interface
Communication: Digital
Location: Built into Grove Beginner Kit

# Role within the System

The sensor is responsible for determining whether atmospheric conditions fall within acceptable ranges.

Example messages include:

Air OK
Too Hot
Too Cold
Air Dry
Very Humid

The actual thresholds are configurable within the software and documented separately in Sensor Calibration and Threshold Logic.

# Development Notes

No hardware modifications were required.

The sensor operated reliably throughout development using the Grove libraries supplied with the development kit.

---

## Light Sensor
# Purpose

The Light Sensor measures ambient brightness surrounding the garden.

Light availability is one of the most important environmental variables affecting plant growth, making it a natural inclusion in the Smart Garden Helper.

# Interface
Communication: Analogue
Location: Built into Grove Beginner Kit
Measurements

The Arduino reads the sensor as an analogue value before converting the reading into a percentage for easier interpretation.

This percentage is then compared against configurable thresholds.

# Development Notes

During testing, an important limitation was observed.

Even under very bright conditions using multiple torch lights, the measured light level saturated at approximately 73% rather than reaching 100%.

While this behaviour did not prevent the system from functioning correctly, it demonstrated an important engineering principle, in that sensor outputs do not always utilise the full theoretical measurement range.

Rather than forcing the sensor to reach 100%, this practical limitation was documented and considered when selecting threshold values.

---

## OLED Display
# Purpose

The OLED Display serves as the primary user interface for the Smart Garden Helper.

Instead of displaying raw serial output, the OLED provides a portable and intuitive way of presenting information directly on the embedded system.

# Interface
Communication: I²C
Location: Built into Grove Beginner Kit
# Display Philosophy

The OLED has limited display space.

Displaying every sensor reading simultaneously would quickly become cluttered and difficult to read.

To overcome this limitation, the project implements a state-based display system, where each screen focuses on one aspect of the garden.

This approach improves readability while introducing users to a common embedded systems design pattern.

# Display States

The OLED cycles through:

Overview
Temperature & Humidity
Light
Soil Moisture
Plant Advice

Navigation between these screens is handled using the onboard push button.

---

## Push Button
# Purpose

The push button provides the only direct user input to the Smart Garden Helper.

Rather than interacting with the sensors themselves, the button allows the user to navigate between OLED display states.

# Interface
Communication: Digital
Location: Built into Grove Beginner Kit
# System Role

Each button press advances the OLED to the next display state.

This simple interaction model keeps the user interface intuitive while demonstrating the concept of finite state machines in embedded systems.

# Design Decision

A single-button interface was chosen because:

It minimises hardware complexity,
It is easy for first-time users to understand,
It demonstrates state-based programming,
and it scales naturally as additional display screens are added.

---

## DFRobot Gravity Analog Soil Moisture Sensor V2
# Purpose

The DFRobot Gravity Analog Soil Moisture Sensor V2 was added as an external component to extend the Grove Beginner Kit's sensing capabilities.

Its purpose is to estimate the relative moisture content of the soil surrounding a plant.

This measurement allows the Smart Garden Helper to determine whether watering may be required.

# Interface
Communication: Analogue
Manufacturer: DFRobot
Model: Gravity Analog Soil Moisture Sensor V2

Unlike the other sensors used in the project, this module required external wiring to the Grove Beginner Kit.

# Initial Integration

The first implementation followed the manufacturer's recommended analogue connection.

Although the sensor produced changing raw values, converting these values into percentages consistently resulted in readings close to 0–1%, even when testing under noticeably different conditions.

# Initial testing included:

Touching the sensor,
Exposing the probe to open air,
Inserting the probe into damp soil,
and placing the probe into water.

The percentage values remained unrealistically low, indicating that further investigation was required.

# Troubleshooting

Several possible causes were considered:

Incorrect calibration constants,
Faulty sensor hardware,
Poor electrical connections,
Incorrect analogue signal routing.

Multiple sensor modules were tested, producing similar behaviour.

This suggested that the issue was unlikely to be a defective sensor.

Further hardware investigation identified the analogue signal routing as the most likely cause of the unstable readings.

The signal connection was rerouted to an alternative analogue input, after which sensor behaviour became significantly more stable.

Once reliable analogue readings were obtained, the calibration constants were updated experimentally until the reported moisture percentages more accurately reflected observed soil conditions.

For the purposes of acknowledgement, this conclusion was reached courtesy of my teammate, a second-year student in Informatics, in this JCP (Joint Community Project) module, when this project's implementation was done.

This experience reinforced an important embedded systems lesson, that being that apparent software problems often originate from hardware.

# Final Calibration

The final calibration values used in Version 1.0.0 are documented directly within the project source code.

These values were determined experimentally using repeated testing rather than relying solely on manufacturer specifications.

Future versions of the project may require recalibration depending on:

Soil type,
Environmental conditions,
Probe ageing,
Sensor manufacturing variation.
# Future Notes

When troubleshooting analogue sensors:

Verify the wiring before modifying software.
Confirm stable raw ADC readings.
Perform calibration only after reliable hardware operation has been established.
Record calibration values alongside the source code.

Following this process significantly reduces debugging time and improves measurement reliability.

# Hardware Summary

The Smart Garden Helper demonstrates how a small collection of inexpensive hardware components can be integrated into a coherent embedded monitoring system. The Grove Beginner Kit provides a robust foundation for rapid prototyping, while the addition of the DFRobot Gravity Analog Soil Moisture Sensor V2 extends the system's ability to monitor conditions directly relevant to plant health.

Throughout development, practical hardware observations—including the light sensor's saturation behaviour and the moisture sensor's analogue wiring issue, which highlighted the importance of testing real hardware rather than relying solely on theoretical specifications. These experiences informed both the software implementation and the project's documentation, ensuring that Version 1.0.0 captures not only the final design but also the engineering decisions made during development.
