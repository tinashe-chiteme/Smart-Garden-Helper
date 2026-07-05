## Engineering Decisions
# Purpose

The Smart Garden Helper Version 1.0.0 was not developed by simply writing code until the system worked. Throughout development, numerous architectural, hardware, and software decisions were made that influenced the final design.

For many of these decisions, multiple implementation approaches were possible. The final solution was selected by considering factors such as readability, maintainability, modularity, educational value, reliability, and compatibility with the Grove Beginner Kit hardware.

This document records the major engineering decisions made during the development of Version 1.0.0, together with the reasoning behind each decision.

## Decision 1: Modular Software Architecture
# Problem

The Smart Garden Helper integrates multiple hardware devices:

DHT11 temperature and humidity sensor
Light sensor
Soil moisture sensor
OLED display
Push-button

Implementing the entire system within a single loop() function would rapidly become difficult to understand and maintain.

As additional functionality was introduced, the risk of producing long, repetitive, and confusing code increased.

# Possible Solutions
# Option 1

Write the complete program inside loop().

# Advantages:

Simple to begin.

# Disadvantages:

Difficult to read.
Difficult to debug.
Poor scalability.
# Option 2

Divide responsibilities into separate functions.

# Advantages:

Organised structure.
Easier testing.
Easier maintenance.
Supports future expansion.
Engineering Decision

The project adopts a modular software architecture.

Major tasks are implemented as independent functions, including:

readSensors()
handleButton()
updateSensorsIfNeeded()
updateDisplayIfNeeded()
display functions
status functions
Reasoning

Each function performs one clearly defined responsibility.

This improves readability while reducing software complexity.

It also mirrors good engineering practice by separating sensing, processing, and presentation into independent software modules.

# Outcome

The resulting code is significantly easier to understand and was particularly beneficial during the educational demonstrations, where individual modules could be explained independently before integrating the complete system.

## Decision 2: Using Helper Functions
# Problem

Many OLED messages depended on interpreting sensor values.

Without helper functions, the same threshold comparisons would need to be repeated throughout the code.

This would introduce unnecessary duplication.

# Possible Solutions
# Option 1

Write threshold comparisons wherever needed.

# Option 2

Create reusable helper functions.

# Engineering Decision

Dedicated helper functions were created.

These include:

getAirStatus()
getLightStatus()
getMoistureStatus()
getPlantAdvice()
Reasoning

Each helper function converts raw sensor measurements into meaningful descriptions.

Rather than repeating threshold comparisons throughout the program, every decision is centralised within a single location.

This improves consistency and greatly simplifies future modifications.

# Outcome

Threshold values can be updated without modifying multiple sections of code.

The software also becomes easier for learners to follow because the function names describe their purpose directly.

## Decision 3: OLED State Machine
# Problem

The Grove OLED display provides limited screen space.

Displaying every measurement simultaneously would produce an overcrowded and difficult-to-read interface.

# Possible Solutions
# Option 1

Display every measurement continuously.

# Option 2

Automatically scroll through information.

# Option 3

Use multiple display states controlled by the user.

# Engineering Decision

The interface was implemented as a finite state machine.

Five dedicated display states were created:

Overview
Air Conditions
Light
Soil Moisture
Plant Advice
Reasoning

Only one category of information is displayed at a time.

This significantly improves readability while allowing the user to choose which information is currently visible.

# Outcome

The interface became considerably cleaner while also providing an excellent demonstration of state-machine concepts during the educational workshops.

## Decision 4: Single Button Navigation
# Problem

Only one user input device was available on the Grove Beginner Kit.

The interface still required a simple navigation mechanism.

# Possible Solutions
# Option 1

Automatically rotate screens.

# Option 2

Add additional hardware buttons.

# Option 3

Use one button to cycle through screens.

# Engineering Decision

A single push-button cycles through all OLED screens.

# Reasoning

The single-button interface is intuitive and requires minimal hardware.

It also demonstrates how a single digital input can control multiple software states.

# Outcome

The final interface remains simple while requiring almost no user training.

## Decision 5: Software Debouncing
# Problem

Mechanical push-buttons naturally bounce.

One press can generate multiple electrical transitions.

Without correction, the OLED frequently skipped several screens.

# Possible Solutions
# Option 1

Ignore switch bouncing.

# Option 2

Add hardware debouncing components.

# Option 3

Implement software debouncing.

# Engineering Decision

Software debouncing was implemented using a 250 ms timing interval.

# Reasoning

The software solution required no additional hardware while providing reliable operation.

# Outcome

Each button press consistently advances exactly one OLED screen.

## Decision 6: Sensor Calibration
# Problem

Analogue sensors do not naturally produce percentages.

Instead, they generate raw ADC values.

# Possible Solutions
# Option 1

Display raw values only.

# Option 2

Convert values into percentages using calibration.

# Engineering Decision

Experimental calibration values were used to map raw measurements into percentages.

# Reasoning

Percentages are considerably easier for users to understand.

This was especially important for the educational demonstrations.

# Outcome

Sensor readings became intuitive while preserving the underlying raw measurements for debugging.

## Decision 7: Displaying Raw Values and Percentages
# Problem

Displaying only percentages hides how analogue sensing works.

Displaying only raw values is difficult for beginners to interpret.

# Engineering Decision

Both values are shown.

For example:

Raw: 538

Light: 72%
# Reasoning

This allows users to observe how electrical measurements are transformed into meaningful information.

# Outcome

The interface supports both technical debugging and educational demonstrations.

## Decision 8: Threshold-Based Decision Making
# Problem

Sensors measure quantities.

They do not make decisions.

# Possible Solutions
# Option 1

Display numerical values only.

# Option 2

Interpret measurements using threshold logic.

# Engineering Decision

Thresholds classify measurements into qualitative conditions.

Examples include:

Too dark
Needs water
Too hot
Air dry
# Reasoning

Thresholds transform numerical measurements into practical advice.

This reflects how many embedded monitoring systems operate.

# Outcome

The Smart Garden Helper provides meaningful recommendations rather than simply displaying sensor data.

## Decision 9: Combining Temperature and Humidity
# Problem

The DHT11 provides two related measurements.

These could either be displayed separately or together.

# Engineering Decision

Temperature and humidity are displayed on the same OLED screen.

# Reasoning

Both measurements describe atmospheric conditions.

Grouping them together reduces unnecessary navigation while presenting logically related information.

# Outcome

Users obtain a complete understanding of the surrounding air from a single display state.

## Decision 10: Plant Advice as the Final Screen
# Problem

Users ultimately want to know whether action is required.

Viewing several individual sensor readings may still require interpretation.

# Possible Solutions
# Option 1

Require users to interpret each sensor individually.

# Option 2

Generate an overall recommendation.

# Engineering Decision

A dedicated "Plant Advice" screen combines information from all sensors before presenting a single recommendation.

Examples include:

Water Plant
Needs Light
Too Hot
Plant OK
Reasoning

This represents the highest level of system processing.

Rather than simply reporting measurements, the Smart Garden Helper performs a basic environmental assessment.

# Outcome

The system transitions from being a sensor monitor to becoming a simple decision-support tool.

## Decision 11: Periodic Sensor Updates
# Problem

Reading every sensor continuously within every iteration of loop() would waste processing time and produce excessive display updates.

# Engineering Decision

Sensors are sampled every two seconds using millis() rather than continuous blocking delays.

The display is refreshed independently.

# Reasoning

Separating sensor acquisition from display updates produces smoother system behaviour and avoids unnecessary processing.

It also introduces learners to the concept of non-blocking timing in embedded systems.

# Outcome

The interface remains responsive while sensor values are updated at an appropriate rate for environmental monitoring.

## Decision 12: Error Handling for the DHT11
# Problem

The DHT11 library can occasionally return invalid (NaN) measurements.

Without checks, these values would propagate through the rest of the system.

# Engineering Decision

The software verifies every temperature and humidity reading before updating stored values.

If a reading fails, the system displays an error message and suppresses invalid data.

# Reasoning

Robust embedded software should assume that sensors may fail and should handle those failures gracefully rather than crashing or displaying misleading information.

# Outcome

The Smart Garden Helper continues operating even when the environmental sensor experiences temporary read failures.

## Engineering Decisions Summary

The final architecture of the Smart Garden Helper is the result of deliberate engineering trade-offs rather than arbitrary implementation choices. Decisions regarding modularity, state-based user interfaces, helper functions, calibration, threshold logic, timing, error handling and display organisation were all guided by the project's dual objectives of technical robustness and educational clarity.

By documenting not only what was implemented but also why each design choice was made, Version 1.0.0 provides a transparent engineering record that supports reproducibility, future development and maintenance. This design rationale will also inform subsequent versions of the Smart Garden Helper as additional sensing, automation and connectivity features are introduced.
