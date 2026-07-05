## OLED State Machine
# Purpose

One of the design objectives of the Smart Garden Helper was to present environmental information in a clear and intuitive manner while working within the physical limitations of the Grove Beginner Kit's 128 × 64 OLED display.

Although the system monitors several environmental conditions simultaneously, including temperature, humidity, ambient light and soil moisture. The OLED display is capable of presenting only a limited amount of information at any one time.

Displaying every sensor reading simultaneously would result in a cluttered interface that is difficult to read, particularly for first-time users and learners who may have little prior experience with embedded systems.

To address this limitation, the Smart Garden Helper organises information into a collection of independent display states.

Each state focuses on one aspect of the monitored environment, while a single push-button allows the user to navigate between screens.

This approach provides a simple, structured interface that improves readability without sacrificing functionality.

# What is a State Machine?

A state machine is a software design technique in which a system behaves differently depending on its current operating state.

Rather than performing every possible action simultaneously, the software exists in one defined state at a time.

Events, such as a button press, cause the system to transition from one state to another.

State machines are widely used throughout embedded systems because they provide an organised method of controlling user interfaces, communication protocols and system behaviour.

Within the Smart Garden Helper, each OLED screen represents one state of the overall interface.

Only one screen is active at any given moment.

# Why a State Machine Was Chosen

Several interface designs were considered during development.

One possible approach would have displayed every sensor reading simultaneously.

While technically possible, this quickly produced a crowded display with little visual organisation.

Users would need to search through numerous measurements before locating the information they required.

Another approach would have continuously scrolled information across the display.

Although this reduces screen clutter, users must wait for the desired information to appear, making interaction slower and less predictable.

Instead, Version 1.0.0 adopts a state-based interface.

Each screen contains only closely related information.

The user remains in complete control of navigation through a single push-button.

This design provides several advantages:

Improved readability,
Predictable navigation,
Simple implementation,
Clear separation of information,
Reduced cognitive load,
Scalability for future versions.
# OLED Navigation

Navigation is performed using a single push-button connected to the Grove Beginner Kit.

Each valid button press advances the OLED to the next display state.

When the final screen has been reached, the interface returns to the Overview screen.

The navigation sequence is shown below.

Overview

↓

Air Conditions

↓

Light

↓

Soil Moisture

↓

Plant Advice

↓

Overview

The navigation therefore forms a continuous loop.

This behaviour is implemented within the handleButton() function by incrementing the current screen state and wrapping back to zero once the final state has been reached.

# State Definitions

The Smart Garden Helper Version 1.0.0 contains five OLED states.

| State | Screen         | Primary Purpose                                         |
| ----: | -------------- | ------------------------------------------------------- |
|     0 | Overview       | Provide an immediate summary of the system.             |
|     1 | Air Conditions | Display temperature, humidity and air status.           |
|     2 | Light Level    | Display light measurements and interpretation.          |
|     3 | Soil Moisture  | Display moisture measurements and interpretation.       |
|     4 | Plant Advice   | Present an overall recommendation based on all sensors. |


Each state is implemented as an independent display function.

## State 0: Overview Screen
# Purpose

The Overview screen acts as the entry point to the Smart Garden Helper.

Rather than presenting every available measurement, it provides a concise summary of the overall system.

In Version 1.0.0 the Overview screen displays:

The project title,
The current plant advice,
A simple visual indicator (:)),
A reminder that the button changes screens.

Example layout:

Smart Garden

Plant OK

:)

Btn: next

The Overview screen is intended to answer the user's first question:

"Is everything okay?"

If additional information is required, the user can navigate to the detailed monitoring screens.

## State 1: Air Conditions
# Purpose

The Air Conditions screen groups together the measurements obtained from the Grove DHT11 environmental sensor.

Because both temperature and humidity originate from the same hardware module and together describe atmospheric conditions, they are presented on the same screen.

Displayed information includes:

Air temperature,
Relative humidity,
Interpreted air status.

Example:

Air Conditions

Temp: 24.3 C

Hum: 52%

Air OK

If the DHT11 sensor cannot be read successfully, the interface automatically displays an error message instead of invalid measurements.

Example:

Air Conditions

DHT Error

Check Sensor

This behaviour provides immediate feedback should the environmental sensor become disconnected or malfunction.

## State 2: Light Level
# Purpose

The Light screen presents information obtained from the Grove analogue light sensor.

Both the raw analogue reading and the calculated percentage are displayed.

Presenting both values serves an educational purpose.

Learners are able to observe the relationship between:

The electrical measurement,
The processed percentage,
The interpreted environmental condition.

Example:

Light Level

Raw: 512

Light: 69%

Light OK

This screen demonstrates how analogue measurements are transformed into meaningful information through calibration and threshold logic.

## State 3: Soil Moisture
# Purpose

The Soil Moisture screen presents information obtained from the external DFRobot Gravity Analog Soil Moisture Sensor V2.

Like the Light screen, both the raw analogue measurement and the calculated percentage are displayed.

Example:

Soil Moisture

Raw: 436

Moist: 53%

Soil OK

Displaying both values allows users to understand that the reported percentage originates from measured electrical signals rather than arbitrary software values.

This screen also proved particularly valuable during calibration and debugging.

During development, comparing raw readings with calculated percentages assisted in identifying wiring issues affecting the analogue signal.

## State 4: Plant Advice
# Purpose

The Plant Advice screen represents the highest level of information processing within the Smart Garden Helper.

Unlike the previous screens, which focus on individual sensor measurements, this state combines information from multiple sensors before presenting a single recommendation.

Example:

Plant Advice

Water Plant

Based on:

Air Light Soil

Rather than requiring users to interpret several independent measurements, this screen provides a clear recommendation describing the most significant environmental condition requiring attention.

As discussed in 07_Threshold_Logic.md, this screen functions as the system's decision engine.

# Software Architecture

The OLED interface is implemented using a hierarchical structure.

The central display manager selects which screen should be displayed according to the current state.

Conceptually, the software follows the structure below.

showCurrentScreen()

↓

switch(screenState)

↓

showOverviewScreen()

showAirScreen()

showLightScreen()

showMoistureScreen()

showAdviceScreen()

Separating each screen into its own function significantly improves readability and maintainability.

Each function is responsible only for rendering a single display state.

# Relationship with the Button

The OLED state machine operates closely with the button handling module.

Each successful button press causes the interface to transition to the next display state.

To prevent multiple transitions resulting from switch bouncing, the software incorporates a debounce delay of 250 milliseconds.

This ensures that each physical press produces only one state transition, resulting in predictable navigation and a smoother user experience.

# Educational Benefits

The state machine architecture provided several educational advantages during the Sensor School workshops.

Instead of overwhelming learners with every sensor simultaneously, each display focused on a single concept.

This mirrored the modular teaching approach used throughout the project, where learners first understood individual sensors before exploring how they work together as an integrated monitoring system.

The state-based interface therefore reinforced both the software architecture and the educational philosophy of the Smart Garden Helper.

# Future Improvements

The state machine architecture adopted in Version 1.0.0 provides a flexible foundation for future development.

Potential enhancements include:

Automatic screen timeouts,
Animated screen transitions,
Graphical icons,
Menu navigation,
Configurable display settings,
Additional monitoring screens,
Touchscreen support,
Remote display interfaces.

Because each display state is implemented independently, these improvements can be incorporated without significantly altering the remainder of the software architecture.

# OLED State Machine Summary

The OLED interface of the Smart Garden Helper was deliberately designed as a finite state machine to overcome the physical limitations of a small embedded display while maintaining a clear and intuitive user experience. By dividing information into five dedicated display states and allowing navigation through a single push-button, the interface remains uncluttered, predictable and easy to understand.

Beyond improving usability, the state machine also reflects sound embedded systems engineering practice. Each display function is responsible for a single aspect of the user interface, supporting the project's modular software architecture and simplifying future maintenance and expansion. The result is an interface that is both technically robust and well-suited to the educational objectives of Version 1.0.0.
