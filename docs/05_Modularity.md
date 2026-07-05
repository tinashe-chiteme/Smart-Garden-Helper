# Origin of the Modular Approach
The modular approach was a deliberate design choice of mine after considering the final system, as well as the educational approach meant for teaching the importance of sensors to high school learners, as was a requirement of ours for the JCP module.

# Purpose

One of the primary software engineering objectives of the Smart Garden Helper was to develop the system using a modular design philosophy.

Rather than attempting to build the complete Smart Garden Helper as a single program from the outset, the project was intentionally divided into a collection of smaller, self-contained software modules. Each module was responsible for one clearly defined function and could be developed, tested, debugged and understood independently before becoming part of the complete system.

This approach significantly reduced software complexity during development while also improving code readability, maintainability and scalability.

More importantly, the modular structure aligned closely with the educational objectives of the project. Because each subsystem could operate independently, learners were introduced to one concept at a time before seeing how those concepts combine into a complete embedded system.

The overall software architecture that supports this modular approach is described in 04_Software_Architecture.md.

---

# What is Modularity?

Modularity is a software engineering principle in which a complex system is divided into smaller, independent components known as modules.

Each module performs one specific task and communicates with the remainder of the system through clearly defined interfaces.

Rather than asking one large section of code to perform every operation, responsibility is distributed across multiple specialised components.

Conceptually, the idea can be represented as follows:
Large Complex System

↓

Small Independent Modules

↓

Integrated System

Each module can be developed independently, tested independently, and improved independently without requiring significant changes to the remainder of the software.

This principle is widely used in embedded systems, industrial automation, robotics, aerospace systems and large-scale software development because it reduces complexity while improving maintainability.

---

# Why Modularity Was Chosen

Several software architectures were considered during the planning of the Smart Garden Helper.

The simplest possible implementation would have placed every sensor reading, threshold comparison, OLED command and button check inside one large loop() function.

Although functional, such an approach quickly becomes difficult to understand.

For example, a single monolithic program would simultaneously contain:

sensor acquisition,
threshold processing,
display rendering,
button handling,
navigation logic,
system timing,
plant advice generation.

As the project grows, this style of programming becomes increasingly difficult to debug and extend.

Instead, the Smart Garden Helper separates these responsibilities into dedicated modules.

Each module has a single purpose.

This separation results in software that is significantly easier to understand, explain and modify.

---

# Development Philosophy

Perhaps the most important design decision made during development was the following:

The complete Smart Garden Helper would not be written first. Instead, each subsystem would be developed individually until it worked reliably, after which the individual modules would be integrated into the final project.

This incremental development strategy reduced debugging complexity considerably.

Rather than attempting to diagnose problems within an entire embedded system, each module could be validated in isolation.

Only once a module consistently behaved as expected was it incorporated into the integrated Smart Garden Helper.

Conceptually, the development process followed the progression shown below.
Temperature & Humidity Module

↓

Verified

↓

Light Module

↓

Verified

↓

Soil Moisture Module

↓

Verified

↓

OLED Display Module

↓

Verified

↓

Button Navigation Module

↓

Verified

↓

Integrated Smart Garden Helper
This sequence reflects the actual engineering workflow used throughout Version 1.0.0.

---

# Independent Module Development

Before the complete system existed, every major subsystem functioned as an independent demonstration program.

Each module had one objective.

# Temperature & Humidity Module

Purpose:

Demonstrate environmental monitoring of atmospheric conditions.

Responsibilities included:

Initialise the sensor,
Read temperature,
Read humidity,
Display readings,
Verify measurement stability.

At this stage no interaction with other sensors occurred.

The objective was simply to confirm that the atmospheric sensor operated correctly.

# Light Sensor Module

Purpose:

Measure ambient light intensity independently of every other subsystem.

Responsibilities included:

Initialise the analogue input,
Read light intensity,
Convert measurements into percentages,
Display results,
Observe behaviour under varying lighting conditions.

Testing also revealed an important practical limitation.

Even under strong illumination, the sensor consistently saturated at approximately 73%.

Rather than treating this as a software fault, the observation was documented and later incorporated into threshold selection.

Further discussion is provided in 06_Sensor_Calibration.md.

# Soil Moisture Module

Purpose:

Measure soil moisture independently before integration into the larger system.

Responsibilities included:

Read analogue moisture values,
Convert readings into percentages,
Determine moisture status,
Display moisture information,
Validate sensor stability.

Development of this module involved the largest amount of hardware troubleshooting.

Initial percentage calculations remained close to 0–1% despite significant environmental changes.

Investigation eventually identified analogue signal routing as the primary cause.

After rerouting the signal connection and experimentally updating calibration constants, stable operation was achieved.

Because this module functioned independently, the problem could be isolated quickly without affecting the remainder of the project, and as mentioned in 03_Hardware.md, this process of finding stable operation was greatly assisted by my teammate in the process of this module.

Complete calibration details are documented in 06_Sensor_Calibration.md.

# OLED Display Module

Purpose:

Develop the graphical user interface independently of sensor logic.

Responsibilities included:

Initialise the OLED,
Test text rendering,
Verify screen layout,
Experiment with information presentation,
Determine readable formatting.

At this stage, placeholder values were often displayed while interface layouts were refined.

Separating display development from sensor acquisition greatly simplified interface design.

# Button Navigation Module

Purpose:

Develop user interaction independently of sensing.

Responsibilities included:

Detect button presses,
Advance OLED display states,
Prevent unintended behaviour,
Verify navigation sequence.

Testing the button independently allowed the navigation logic to be refined before introducing live sensor updates.

This simplified debugging considerably.

---

## Advantages of Independent Development

Developing modules independently provided several engineering advantages.

# Easier Debugging

If unexpected behaviour occurred, only one subsystem required investigation.

For example, incorrect soil moisture readings could be traced directly to the soil moisture module without questioning the OLED, light sensor or button logic.

This dramatically reduced troubleshooting time.

# Faster Testing

Small programs compile more quickly and are easier to observe during testing.

Rather than interpreting multiple sensor outputs simultaneously, I, as the primary developer, could focus entirely on the behaviour of a single component.

This made identifying unexpected behaviour significantly easier.

# Improved Readability

Each module remained short and focused.

New developers can understand individual subsystems without first understanding the complete Smart Garden Helper.

This characteristic proved particularly valuable during educational demonstrations.

# Incremental Confidence

Each successfully completed module increased confidence that the overall system would function correctly after integration.

Instead of hoping the complete project would work, confidence was built progressively as each independent component reached a stable state.

---

# Integration

Once every module had been individually verified, the project entered the integration phase.

Rather than rewriting each module, the existing software components were incorporated into a common software architecture.

The integrated system followed the progression below.
Independent Modules

↓

Temperature & Humidity

Light

Soil Moisture

OLED

Button

↓

Shared Software Architecture

↓

Smart Garden Helper Version 1.0.0
Because each subsystem had already been tested independently, integration focused primarily on communication between modules rather than basic functionality.

This significantly reduced integration risk.

---

# Relationship with Helper Functions

The modular development process naturally influenced the final software architecture.

Rather than abandoning the independent modules after integration, each module evolved into one or more dedicated helper functions.

Conceptually:
Independent Test Program

↓

Reusable Helper Function

↓

Integrated Application
Examples include:

Reading sensor measurements,
Updating OLED screens,
Processing thresholds,
Handling button navigation.

This allowed the final Smart Garden Helper to retain the clarity achieved during independent module development.

The resulting helper function architecture is described in 04_Software_Architecture.md.

---

# Educational Benefits

Although modularity was initially adopted for engineering reasons, it also became one of the strongest educational features of the project.

Rather than introducing learners to an entire embedded monitoring system immediately, the Smart Garden Helper was presented progressively over four instructional sessions.

Learners first encountered each sensor independently.

Once they understood the behaviour of each module, threshold logic was introduced to explain how numerical sensor readings become meaningful information.

Only after these individual concepts had been established were the modules integrated into the complete Smart Garden Helper.

This mirrored the actual engineering workflow used during development.

The teaching approach therefore reflected the software architecture itself: To understand the parts before understanding the whole.

---

# Lessons Learned

The modular development strategy produced several important engineering lessons.

Building one reliable subsystem at a time is often more effective than attempting to develop a complete system simultaneously.
Hardware faults can be isolated more efficiently when only one subsystem is under test.
Clear separation of responsibilities leads to software that is easier to maintain and extend.
Independent testing increases confidence during later system integration.
A modular architecture naturally supports both engineering development and educational instruction.

These observations influenced not only the final implementation of Version 1.0.0 but also the planned architecture for future versions of the Smart Garden Helper.

---

# Modularity Summary

The Smart Garden Helper was intentionally engineered using a modular development strategy in which each subsystem was designed, implemented and validated independently before being integrated into the complete application. This approach reduced software complexity, simplified debugging and produced a maintainable codebase organised around clearly defined responsibilities.

Beyond its technical advantages, modularity also shaped the educational philosophy of the project. The same progression used to develop the software—moving from individual components to an integrated system—formed the foundation of the four-day learning experience delivered to the learners. In this way, the engineering process and the teaching methodology became closely aligned, demonstrating that understanding complex systems begins with understanding their individual parts.
