## Software Architecture
# Purpose

The Smart Garden Helper is built around a modular software architecture designed to separate individual responsibilities into independent, reusable software components. Rather than implementing all functionality within a single program loop, the system divides sensing, processing, user interaction, and display management into logical modules that each perform one clearly defined task.

This design philosophy improves readability, maintainability, debugging, and future scalability while also making the project significantly easier to explain in an educational setting.

Although the Smart Garden Helper is a relatively small embedded application, its software structure reflects many of the same design principles used in larger embedded systems and industrial control software.

For a description of the overall system architecture and information flow, refer to 02_System_Architecture.md.

---

# Software Design Philosophy

During the planning stage of the project, one primary objective was identified:

Keep the software simple enough for beginners to understand, while structuring it in a way that reflects good engineering practice.

Instead of attempting to optimise for the shortest possible code, the software prioritises clarity.

Several design principles guided the implementation:

One function should perform one responsibility.
Related functionality should remain grouped together.
The main program should describe what happens, while helper functions describe how it happens.
Sensor-specific logic should remain independent wherever possible.
User interface code should remain separate from sensor acquisition code.
Threshold decisions should remain configurable without rewriting the rest of the program.

These principles influenced every stage of software development.

---

# High-Level Software Flow

The software continuously executes the following sequence:
Power On

↓

setup()

↓

loop()

↓

Handle Button

↓

Read Sensors

↓

Interpret Readings

↓

Determine OLED State

↓

Update Display

↓

Repeat Forever

Unlike a conventional desktop program that executes once and terminates, Arduino software executes continuously. The loop() function repeats indefinitely, allowing the Smart Garden Helper to monitor environmental conditions in real time.

Each pass through the loop updates the system based on both sensor measurements and user interaction.

---

# Program Entry Point

Like all Arduino applications, the Smart Garden Helper consists of two primary execution functions:
void setup()

void loop()

Although these functions are mandatory within the Arduino framework, they serve very different purposes.

setup()
 # Purpose

The setup() function executes once immediately after the microcontroller powers on or resets.

Its responsibility is to prepare every hardware component before the monitoring system begins operating.

Typical tasks performed during initialisation include:

Initialising serial communication for debugging
Starting the OLED display
Configuring display settings
Initialising sensor libraries
Configuring button input
Displaying the startup screen
Initialising program variables

Once initialisation is complete, execution transfers permanently to the loop() function.

No environmental monitoring occurs until setup has successfully completed.

# Why initialise everything first?

Embedded systems frequently interact directly with hardware peripherals.

Attempting to read sensors before they have been initialised may produce invalid readings or undefined behaviour.

Similarly, attempting to write to the OLED before it has been configured may result in a blank or corrupted display.

By concentrating all initialisation inside setup(), the remainder of the software can safely assume that every subsystem is ready for use.

---

loop()
# Purpose

The loop() function represents the continuous operation of the Smart Garden Helper.

Rather than containing every programming instruction directly, it coordinates the execution of smaller helper functions.

Conceptually, the loop answers one question repeatedly:

"What is happening in the garden right now?"

Every iteration performs the following sequence:

Check whether the user pressed the button.
Read current sensor measurements.
Process the measurements.
Determine which OLED screen should be displayed.
Update the OLED.
Wait briefly.
Repeat.

This cycle continues for as long as the Arduino remains powered.

# Why the Loop Was Kept Small

One of the earliest software design decisions was to avoid writing a large, monolithic loop() function.

Instead of placing every sensor reading, every threshold comparison, every OLED command, and every button check inside one large block of code, the loop was intentionally kept short and descriptive.

Conceptually, the final structure resembles:
void loop()
{
    handleButton();

    updateSensors();

    updateDisplay();

    delay(100);
}

Although each helper function contains substantial logic internally, the loop itself reads almost like a list of instructions.

This improves readability considerably.

Someone unfamiliar with the project can understand the overall system behaviour simply by reading these few lines.

---

# Helper Functions

The Smart Garden Helper is organised around helper functions.

Each helper function performs one specific responsibility.

Examples include:
handleButton()

↓

Read button state

↓

Determine whether display should change

↓

Update current OLED state

updateSensors()

↓

Read temperature

↓

Read humidity

↓

Read light

↓

Read soil moisture

↓

Store measurements

updateDisplay()

↓

Determine current display state

↓

Call correct OLED screen

↓

Render information

Each helper function behaves like a small self-contained module.

This makes individual components easier to understand, modify, and debug.

A detailed discussion of the project's modular design philosophy is provided in 05_Modularity.md.

---

# Sensor Modules

Rather than treating all sensors as one combined subsystem, each sensing operation was initially developed independently.

Separate software modules were created for:

Temperature & Humidity
Light
Soil Moisture

Each module was capable of:

Reading its own sensor
Processing the measurement
Displaying results independently on the OLED

Only after each module functioned correctly were they integrated into the final Smart Garden Helper.

This incremental development process significantly reduced debugging complexity.

Individual sensor implementation and calibration are documented in:

03_Hardware.md
06_Sensor_Calibration.md

---

# Threshold Processing

Raw sensor readings are not inherently meaningful to users.

For example, 'Soil Moisture = 427' provides little practical information.

Instead, each sensor reading is interpreted using configurable threshold values.

The software follows a simple decision process:

Read Sensor

↓

Convert if Required

↓

Compare Against Thresholds

↓

Determine Status Message

↓

Display Result

This separation between measurement and interpretation allows threshold values to be modified without affecting the remainder of the software.

The complete threshold implementation is described in 07_Threshold_Logic.md.

---

# OLED Display Management

The OLED display is treated as a dedicated subsystem rather than simply another output device.

Instead of continuously printing every available measurement, the software organises information into separate display states.

Each display state focuses on one category of information.

Typical states include:

Overview
Temperature & Humidity
Light
Soil Moisture
Plant Advice

The current display state determines which rendering function is executed.

This significantly improves readability on the small OLED screen.

The complete state machine is documented in 08_OLED_State_Logic.md.

---

# Button Handling

The push button forms the primary user input.

Instead of interacting directly with sensors, the button modifies the current OLED display state.

Every valid button press advances the interface to the next screen.

This behaviour is isolated inside a dedicated button handling function rather than being mixed with display code.

Separating button logic provides several advantages:

Cleaner program flow,
Easier debugging,
Reusable navigation logic,
Simplified future expansion.

---

# Separation of Responsibilities

One of the most important software engineering principles demonstrated by this project is separation of responsibilities.

Rather than allowing one function to perform multiple unrelated tasks, each module performs one clearly defined role.

The software can therefore be viewed as several cooperating layers:
| Layer                | Responsibility                 |
| -------------------- | ------------------------------ |
| Hardware Interface   | Read sensor measurements       |
| Processing Layer     | Convert and interpret readings |
| Decision Layer       | Apply threshold logic          |
| User Interface Layer | Manage OLED display states     |
| Input Layer          | Handle button navigation       |
This layered approach makes the software easier to understand and maintain.

---

# Scalability

Although Version 1.0.0 monitors only four environmental variables, the software architecture was designed to accommodate future expansion.

Potential future additions include:

Automatic irrigation control
Wi-Fi connectivity
Cloud data logging
Historical trend analysis
Mobile application integration
Weather forecast integration
Additional environmental sensors

Because each subsystem is modular, new functionality can be added with minimal modification to existing code.

Future expansion ideas are discussed further in 12_Future_Work.md.

---

# Design Decisions

Several deliberate engineering decisions shaped the software architecture:
| Decision                   | Reason                                             |
| -------------------------- | -------------------------------------------------- |
| Modular helper functions   | Improved readability and maintainability           |
| Small `loop()` function    | Clearly communicates overall system behaviour      |
| Independent sensor modules | Simplifies testing and debugging                   |
| State-based OLED interface | Efficient use of limited display space             |
| Threshold-based processing | Converts raw data into meaningful information      |
| Layered software structure | Supports future scalability and easier maintenance |
Many of these decisions emerged through iterative development and refinement rather than being fixed from the beginning. A discussion of these design trade-offs is provided in 10_Engineering_Decisions.md.

---

# Software Architecture Summary

The Smart Garden Helper's software architecture was intentionally designed to balance educational clarity with sound engineering practice. By separating hardware interaction, sensor processing, decision-making, user interaction, and display management into distinct modules, the system remains easy to understand while reflecting principles commonly used in professional embedded software development.

This modular approach also mirrored the project's educational methodology. Each subsystem was first developed and demonstrated independently before being integrated into the complete Smart Garden Helper, allowing both the developers and the learners to build understanding progressively. The resulting architecture is therefore not only technically maintainable but also well suited to teaching fundamental concepts in embedded systems and systems engineering.
