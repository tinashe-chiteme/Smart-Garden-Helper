## From Monitoring to Decision Support

Up to this point, each sensor within the Smart Garden Helper has operated independently.

Each module performs a single responsibility:

The temperature sensor measures air temperature,
The humidity sensor measures atmospheric moisture,
The light sensor measures ambient illumination,
The soil moisture sensor measures the moisture content of the soil.

These modules provide valuable information, but they do not make decisions. They simply observe the environment and report their measurements to the user.

This approach is known as environmental monitoring.

The Plant Advice screen extends the system beyond simple monitoring by combining information from multiple sensors to produce a single recommendation.

Rather than asking the user to interpret four independent sensor readings, the Smart Garden Helper performs that interpretation automatically.

# Decision Support

The Plant Advice screen acts as the decision-making component of the Smart Garden Helper.

Instead of displaying every sensor reading simultaneously, the software evaluates the environmental conditions in a logical sequence before selecting the most appropriate recommendation.

This process transforms multiple independent measurements into one actionable message.

Conceptually, the workflow is:

Temperature
            \
Humidity      \
               \
Light ---------> Decision Engine ---------> Plant Advice
               /
Moisture -----/

Unlike the individual monitoring screens, which answer "What is happening?", the Plant Advice screen answers "What should be done?"

# Decision Priority

The decision engine evaluates environmental conditions according to a predefined order of importance.

This ensures that only the most significant condition is presented to the user at any one time.

For Version 1.0.0 the evaluation order is:

| Priority | Condition             | Advice           |
| -------- | --------------------- | ---------------- |
| 1        | Air sensor failure    | Check air sensor |
| 2        | Soil too dry          | Water plant      |
| 3        | Soil too wet          | Too much water   |
| 4        | Too little light      | Needs light      |
| 5        | Excessive light       | Very bright      |
| 6        | Temperature too high  | Too hot          |
| 7        | Temperature too low   | Too cold         |
| 8        | Humidity too low      | Air too dry      |
| 9        | Humidity too high     | Air humid        |
| 10       | Everything acceptable | Plant OK         |


This ordered evaluation prevents multiple messages from competing for the user's attention and allows the OLED display to communicate a single, clear recommendation.

# Why Priorities?

The Smart Garden Helper deliberately reports only one recommendation at a time.

For example, suppose the following conditions exist simultaneously:

Soil moisture = 18%
Light level = 22%
Temperature = 36°C

Several environmental problems exist.

Instead of displaying:

Needs Water
Too Dark
Too Hot

The decision engine displays only:

Water Plant

This behaviour is intentional.

Water availability is treated as the highest-priority issue because a severely dry plant is unlikely to benefit from additional light or temperature adjustments until adequate moisture has been restored.

Prioritisation therefore simplifies the user's decision-making process.

# Relationship to Systems Engineering

The Plant Advice screen represents the highest level of abstraction within Version 1.0.0.

The software architecture can therefore be viewed as four distinct stages:

Physical Environment

↓

Sensors

↓

Measurements

↓

Threshold Logic

↓

Decision Engine

↓

OLED Advice

This layered approach reflects a common design philosophy used in embedded systems engineering, where raw sensor measurements are progressively processed into meaningful information before finally supporting human decision-making.

Although the Smart Garden Helper operates on a small educational platform, the same principle is used in many larger engineering systems, including environmental monitoring networks, industrial automation, autonomous vehicles, and smart agriculture applications.
