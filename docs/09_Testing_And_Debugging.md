## Testing and Debugging
# Purpose

Engineering rarely follows a perfectly linear path from design to implementation. While the final version of the Smart Garden Helper operates as intended, Version 1.0.0 was developed through a continuous process of observation, testing, troubleshooting and refinement.

Throughout development, both hardware and software were repeatedly evaluated under realistic operating conditions. Unexpected behaviour was documented, hypotheses were formed, alternative explanations were investigated, and solutions were implemented before testing resumed.

Rather than viewing these challenges as setbacks, they became an essential part of the engineering process. Each issue provided additional understanding of the behaviour of the hardware, the software architecture and the interaction between the two.

This document records the most significant testing activities, observations and debugging decisions made during the development of Version 1.0.0.

# Testing Philosophy

Testing was performed according to a modular development strategy.

Rather than constructing the complete Smart Garden Helper immediately, each subsystem was first developed and tested independently.

This provided two important advantages.

First, unexpected behaviour could be isolated to a single module rather than the complete system.

Second, once each subsystem operated reliably, integration became considerably simpler.

Testing therefore followed the progression below.

Individual Sensor Modules

↓

OLED Display

↓

Button Navigation

↓

Threshold Logic

↓

Integrated Smart Garden Helper

↓

Educational Demonstrations

Each stage provided confidence before progressing to the next.

# Testing Environment

The Smart Garden Helper was tested using:

Grove Beginner Kit for Arduino
DFRobot Gravity Analog Soil Moisture Sensor V2
Arduino IDE
Serial Monitor
Integrated OLED display
Classroom demonstrations
Practical testing with high school learners

Both laboratory-style testing and live educational demonstrations contributed to the final Version 1.0.0 implementation.

# Issue 1: Light Sensor Saturation
# Objective

Determine whether the Grove light sensor responded correctly to changes in ambient illumination.

# Test Procedure

The light sensor was exposed to a variety of lighting conditions.

Testing included:

Normal classroom lighting,
Covering the sensor by hand,
Partial shading,
Direct torch illumination,
Multiple torch lights,
Exposure to the brightest available indoor conditions.

The OLED and Serial Monitor were both used to observe changes in measured values.

# Observation

The sensor consistently responded to changing light levels.

However, the calculated percentage never reached 100%.

Instead, measurements appeared to stabilise at approximately 73%, even under the brightest available conditions.

Repeated testing produced similar results.

# Investigation

Initially, several explanations were considered.

Possible causes included:

Incorrect percentage conversion,
Software mapping errors,
Calibration constants,
Sensor limitations.

The mapping equation was reviewed and found to be mathematically correct.

The sensor continued to respond consistently to changes in illumination.

# Engineering Decision

Rather than forcing the software to report 100%, the measured behaviour was accepted as the practical operating range of the hardware.

The threshold values were therefore selected using experimentally observed measurements rather than theoretical limits.

This decision preserves measurement integrity while accurately representing real sensor behaviour.

# Lessons Learned

Real sensors do not always utilise their complete theoretical operating range.

Engineering decisions should be based on measured behaviour rather than assumptions.

## Issue 2: Soil Moisture Sensor Calibration
# Objective

Convert raw analogue measurements into meaningful soil moisture percentages.

# Initial Behaviour

The first implementation successfully compiled and uploaded to the Arduino.

The OLED displayed moisture information correctly.

However, the calculated moisture percentage remained almost constant.

Typical values were:

0%

1%

This occurred even when obvious environmental changes were introduced.

# Test Procedure

Several practical tests were performed.

These included:

Dry sensor,
Damp soil,
Wet soil,
Immersion in water,
Repeated insertion into different materials.

Little improvement was observed.

# Initial Hypotheses

Several possible explanations were considered.

# Incorrect calibration constants

The dry and wet reference values might not accurately represent the physical sensor.

# Software error

The mapping equation may have been incorrect.

# Faulty sensor

The moisture sensor itself may have been defective.

# Wiring issue

The analogue signal path may have been unstable.

# Investigation

The software implementation was reviewed.

The mapping function was verified.

Calibration constants were adjusted.

Multiple sensor modules were tested.

Despite these changes, the reported percentage remained unrealistic.

# Root Cause

Further investigation shifted attention from software to hardware.

The analogue signal routing was identified as the primary cause of the instability.

After rerouting the analogue signal connection, measurements became significantly more stable.

The calibration constants were then updated using experimentally observed values.

# Final Solution

Following hardware correction:

Raw analogue readings stabilised,
Percentage calculations became meaningful,
Threshold logic operated correctly,
OLED messages reflected observed soil conditions.

The final calibration values adopted for Version 1.0.0 are documented in 06_Sensor_Calibration.md.

# Lessons Learned

Embedded systems problems are not always software problems.

Stable hardware connections should always be verified before modifying software.

## Issue 3: DHT11 Error Handling
# Objective

Ensure reliable operation of the environmental sensor.

# Observation

The DHT11 library occasionally reports invalid measurements.

These appear as "Not a Number" (NaN) values.

Without additional software checks, these invalid values would propagate through the remainder of the system.

# Solution

Version 1.0.0 verifies every temperature and humidity measurement before updating the stored sensor values.

If an invalid measurement is detected:

Sensor values are not updated,
The air sensor status is marked as unavailable,
The OLED reports an error,
The Plant Advice screen recommends checking the sensor.
# Lessons Learned

Embedded software should never assume that sensors always produce valid data.

Graceful failure handling improves both reliability and user experience.

## Issue 4: Button Navigation
# Objective

Allow the user to navigate between OLED screens using a single push-button.

# Observation

Mechanical push-buttons do not produce perfectly clean electrical signals.

A single press may generate multiple rapid transitions.

Without correction, one button press frequently skipped several display screens.

# Solution

A software debounce delay of 250 ms was introduced.

The software records the time of the previous valid button press and ignores additional transitions occurring within the debounce period.

# Result

Navigation became predictable.

Each physical button press produced exactly one screen transition.

# Lessons Learned

Simple hardware components often require software compensation.

Reliable embedded systems frequently combine hardware and software solutions.

## Issue 5: OLED Information Density
# Objective

Present environmental information clearly on a 128 × 64 display.

# Observation

Early interface layouts attempted to display excessive information simultaneously.

Although technically correct, the display became crowded and difficult to read.

# Decision

Information was separated into five dedicated display states.

Overview
Air Conditions
Light
Soil Moisture
Plant Advice

Navigation between screens was assigned to the push-button.

# Result

The interface became substantially easier to understand.

The final layout also aligned closely with the educational structure used during the Sensor School workshops.

# Lessons Learned

A successful user interface presents the right amount of information rather than the maximum amount of information.

# System Integration Testing

After each module had been validated independently, the complete Smart Garden Helper was assembled.

Integration testing confirmed:

Simultaneous operation of all sensors,
OLED navigation,
Threshold evaluation,
Plant Advice generation,
Serial Monitor output,
periodic sensor updates,
Reliable button navigation.

No significant integration issues were observed following completion of the modular testing phase.

# Live Classroom Testing

Perhaps the most valuable testing occurred during the Sensor School workshops.

Unlike controlled laboratory testing, classroom demonstrations introduced real users interacting with the system.

Learners:

Manipulated the sensors,
Observed changing measurements,
Suggested threshold values,
Interpreted OLED messages,
Discussed why measurements changed.

These sessions confirmed that the Smart Garden Helper was not only technically functional but also effective as an educational tool.

The classroom demonstrations also influenced several refinements, including adjustments to the pacing of learner activities and confirmation that displaying interpreted messages alongside sensor values improved understanding.

# Overall Lessons Learned

Development of Version 1.0.0 reinforced several important engineering principles.

Test one subsystem at a time.
Record observations before changing code.
Consider hardware and software together when troubleshooting.
Validate assumptions experimentally.
Preserve unsuccessful attempts as part of the engineering record.
Design software that fails gracefully.
Real-world testing is just as valuable as laboratory testing.

These lessons influenced both the final implementation of Version 1.0.0 and the planned development methodology for future versions.

# Testing and Debugging Summary

The Smart Garden Helper was developed through a structured process of iterative testing and debugging rather than a single implementation effort. By validating each module independently, investigating unexpected behaviour systematically, and documenting both successful and unsuccessful approaches, Version 1.0.0 reflects a practical engineering workflow rather than simply a finished product.

Many of the project's most valuable lessons emerged from challenges encountered during development, including analogue sensor calibration, hardware troubleshooting, user interface design, and robust error handling. Recording these experiences not only improves the reproducibility of the project but also provides a transparent account of the engineering decisions that shaped the final system.
