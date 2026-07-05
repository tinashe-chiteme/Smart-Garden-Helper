## Threshold Logic
# Purpose

One of the primary objectives of the Smart Garden Helper is to transform raw environmental measurements into information that is meaningful to the user.

Although the sensors continuously measure physical quantities such as temperature, humidity, light intensity and soil moisture, the values produced by these sensors are simply numbers. By themselves, these numbers provide little practical guidance regarding the health of the monitored environment.

For example, knowing that a soil moisture sensor reports a value of 426 or that the light sensor reports 68% does not immediately indicate whether the conditions are suitable for plant growth.

Threshold logic provides the link between measurement and interpretation.

Instead of presenting raw values alone, the Smart Garden Helper compares each measurement against predefined threshold values. These comparisons allow the software to classify environmental conditions into meaningful categories such as Too Dark, Light OK, Needs Water, or Too Hot.

This process transforms numerical sensor readings into practical advice that can be understood by users with little or no technical background.

The calibrated sensor measurements discussed in 06_Sensor_Calibration.md form the inputs to the threshold logic described in this document.

---

# Why Threshold Logic?

Sensors measure physical quantities.

People make decisions.

The Smart Garden Helper therefore acts as the bridge between these two worlds.

Rather than asking a user to interpret sensor measurements directly, the software performs a simple evaluation and displays an easily understood message.

Conceptually, every measurement follows the same decision process.

Physical Environment

↓

Sensor Measurement

↓

Arduino Reads Value

↓

Convert if Necessary

↓

Compare Against Thresholds

↓

Determine Status

↓

Display OLED Message

This process is repeated continuously while the system operates.

---

# Raw Measurements vs Meaning

During development, an important distinction was made between raw sensor values and interpreted information.

Consider the following example.

Raw Soil Moisture = 487

Although technically correct, this value tells most users very little.

Instead, the Smart Garden Helper first converts the raw analogue reading into a percentage.

Raw Reading

↓

487

↓

Moisture Percentage

↓

42%

The percentage is then compared against predefined thresholds.

42%

↓

Between 30% and 80%

↓

"Soil OK"

The OLED therefore displays

Soil Moisture

42%

Status:
Soil OK

This progression illustrates the central purpose of threshold logic, being that measurements become useful only after they have been interpreted.

---

## Common Threshold Workflow

Although each sensor measures a different physical quantity, the software processes each one using the same overall workflow.

Read Sensor

↓

Obtain Measurement

↓

Convert to Engineering Units

↓

Compare Against Threshold Values

↓

Assign Status

↓

Display Status on OLED

Because every sensor follows the same logical structure, the software remains consistent and easy to extend.

Only the threshold values differ between sensors.

## Temperature Threshold Logic
# Measurement

The temperature sensor reports air temperature directly in degrees Celsius.

No additional conversion is required.

Example measurement:

Temperature = 24°C

The software compares this value against predefined thresholds.

Temperature

↓

Below Lower Limit?

↓

Yes → Too Cold

No

↓

Above Upper Limit?

↓

Yes → Too Hot

No

↓

Air OK

The OLED therefore displays both the measured temperature and its interpreted status.

Example:

Temperature

24°C

Status:
Air OK

The threshold values used in Version 1.0.0 are intentionally simple and were selected to support educational demonstrations rather than represent precise horticultural recommendations.

## Humidity Threshold Logic

Humidity is processed in a similar manner.

The environmental sensor reports relative humidity directly as a percentage.

Example:

Humidity = 48%

The decision process follows:

Humidity

↓

Below Lower Limit?

↓

Air Dry

↓

Between Limits?

↓

Air OK

↓

Above Upper Limit?

↓

Very Humid

The OLED combines the measured humidity value with the interpreted condition.

Example:

Humidity

48%

Status:
Air OK

## Light Threshold Logic

Unlike temperature and humidity, the light sensor produces an analogue measurement.

The Smart Garden Helper first converts this raw value into an estimated percentage.

Raw ADC

↓

Percentage

↓

Threshold Comparison

↓

OLED Message

Example:

Light = 67%

Decision process:

Below 30%

↓

Too Dark

30%–80%

↓

Light OK

Above 80%

↓

Very Bright

The OLED therefore presents information that is much easier to interpret than a raw analogue value.

Example:

Light Level

67%

Status:
Light OK

As discussed in 06_Sensor_Calibration.md, experimental testing revealed that the sensor reached a practical maximum of approximately 73% under the available lighting conditions. Threshold values were therefore selected based on observed behaviour rather than purely theoretical limits.

## Soil Moisture Threshold Logic

The soil moisture sensor follows the most extensive processing sequence within the Smart Garden Helper.

The analogue probe produces a raw electrical measurement representing the conductivity of the surrounding soil.

This measurement is first converted into a moisture percentage using experimentally determined calibration constants.

The resulting percentage is then compared against threshold values.

Conceptually:

Raw Moisture Reading

↓

Calibration

↓

Moisture Percentage

↓

Threshold Comparison

↓

OLED Message

For Version 1.0.0 the software classifies soil moisture into three simple categories.

Below 30%

↓

Needs Water

30%–80%

↓

Soil OK

Above 80%

↓

Too Wet

Example OLED display:

Soil Moisture

45%

Status:
Soil OK

The threshold values were deliberately chosen to demonstrate decision-making logic during educational activities. They are easily adjustable and may be modified to suit different soil types or plant species without requiring changes to the remainder of the software.

## Plant Advice Logic

The previous sections describe how individual sensor measurements are interpreted.

The Plant Advice screen extends this concept by combining information from multiple sensors to produce a simple recommendation for the user.

Rather than displaying individual measurements, this screen summarises the overall condition of the monitored environment.

Conceptually, the decision process is:

Read All Sensors

↓

Interpret Each Reading

↓

Evaluate Conditions

↓

Display Overall Advice

Examples of possible recommendations include:

Water the plant.
Increase available light.
Air conditions are suitable.
Garden conditions look healthy.

The purpose of this screen is not to replace individual sensor displays but to demonstrate how multiple independent measurements can be combined into a higher-level decision.

This represents a simple example of systems thinking, where information from several independent modules contributes to a single overall conclusion.

## Why Three Threshold Regions?

Each monitored quantity is divided into three simple operating regions:
| Region                | Meaning                              |
| --------------------- | ------------------------------------ |
| Below Lower Threshold | Condition may require attention      |
| Between Thresholds    | Normal operating range               |
| Above Upper Threshold | Condition may also require attention |
This three-region structure was selected because it is:

Easy to understand,
Easy to explain,
Simple to implement,
Straightforward to modify,
Suitable for introductory embedded systems education.

More complex classification systems could certainly be implemented, but they would add unnecessary complexity to Version 1.0.0.

---

## Engineering Considerations

Several important engineering decisions influenced the threshold logic.

# Thresholds are configurable

Threshold values are defined separately from the remainder of the processing logic.

Changing a threshold therefore does not require rewriting the sensor reading functions or OLED display code.

# Thresholds depend on calibration

Meaningful thresholds can only be selected after reliable sensor calibration has been completed.

Incorrect calibration inevitably produces incorrect classifications.

For this reason, calibration preceded threshold selection throughout development.

# Thresholds simplify communication

Most users understand messages such as:

Needs Water
Too Dark
Air OK

far more readily than raw numerical measurements.

Threshold logic therefore improves the accessibility of the Smart Garden Helper without sacrificing technical accuracy.

---

## Relationship to the Software Architecture

Threshold processing represents the decision-making layer of the Smart Garden Helper.

The complete software workflow is therefore:

Sensors

↓

Sensor Reading Functions

↓

Calibration

↓

Threshold Logic

↓

OLED Display Manager

↓

User

This layered structure separates sensing, interpretation and presentation into independent responsibilities, supporting the modular software architecture described in 04_Software_Architecture.md and the development methodology presented in 05_Modularity.md.

---

## Threshold Logic Summary

Threshold logic forms the core of the Smart Garden Helper's decision-making capability. Rather than presenting users with raw sensor measurements, the system interprets calibrated environmental data using configurable threshold values and communicates the results through simple, intuitive OLED messages.

This design improves usability, supports educational objectives, and demonstrates a fundamental principle of embedded systems engineering: data becomes valuable only when it is interpreted in context. By separating measurement, calibration, interpretation and presentation into distinct stages, Version 1.0.0 provides a clear, maintainable and extensible foundation for future development while remaining accessible to first-time learners.

## Threshold Values Used in Version 1.0.0:
The Smart Garden Helper Version 1.0.0 uses the threshold values shown below to classify environmental conditions. These constants are defined near the beginning of the source code, allowing the decision-making behaviour of the system to be modified without changing the underlying program logic.

These values were selected during testing and educational demonstrations to provide clear, easy-to-understand feedback suitable for introductory embedded systems learning. Future versions of the project may refine these values to better suit specific plant species, environmental conditions, or deployment locations.

# A.1 Light Sensor Thresholds
| Constant            |   Value | Interpretation                                   | OLED Status     |
| ------------------- | ------: | ------------------------------------------------ | --------------- |
| `LIGHT_LOW`         | **30%** | Light level below the acceptable operating range | **Too dark**    |
| `LIGHT_HIGH`        | **80%** | Light level above the acceptable operating range | **Very bright** |
| Between 30% and 80% |       — | Acceptable lighting conditions                   | **Light OK**    |
# Light Sensor Calibration
| Constant           |   Value | Description                                                                                                            |
| ------------------ | ------: | ---------------------------------------------------------------------------------------------------------------------- |
| `LIGHT_DARK_RAW`   |   **0** | Raw analogue value representing complete darkness (minimum expected reading).                                          |
| `LIGHT_BRIGHT_RAW` | **740** | Highest experimentally observed raw analogue value during testing. Used when converting raw readings into percentages. |

# A.2 Soil Moisture Thresholds
| Constant            |   Value | Interpretation                     | OLED Status     |
| ------------------- | ------: | ---------------------------------- | --------------- |
| `MOISTURE_LOW`      | **30%** | Soil is considered dry             | **Needs water** |
| `MOISTURE_HIGH`     | **80%** | Soil is considered excessively wet | **Too wet**     |
| Between 30% and 80% |       — | Suitable soil moisture             | **Soil OK**     |
# Soil Moisture Calibration
| Constant           |   Value | Description                                                                                                                      |
| ------------------ | ------: | -------------------------------------------------------------------------------------------------------------------------------- |
| `MOISTURE_DRY_RAW` |   **0** | Raw analogue value representing the dry calibration point used in Version 1.0.0.                                                 |
| `MOISTURE_WET_RAW` | **821** | Raw analogue value representing the wet calibration point determined experimentally after hardware troubleshooting and rewiring. |
# Engineering Note:
The DFRobot Gravity Analog Soil Moisture Sensor V2 required practical calibration during development. Initial calibration attempts produced unreliable percentage values due to analogue signal routing issues. After correcting the wiring and experimentally determining suitable calibration points, the values above were adopted for Version 1.0.0. Because soil moisture sensors are highly dependent on soil type, moisture content, and deployment conditions, these calibration values should be regarded as application-specific rather than universal.

# A.3 Temperature Thresholds
| Constant                |       Value | Interpretation                                       | OLED Status                                   |
| ----------------------- | ----------: | ---------------------------------------------------- | --------------------------------------------- |
| `TEMP_LOW`              | **15.0 °C** | Air temperature is below the desired operating range | **Quite cold**                                |
| `TEMP_HIGH`             | **35.0 °C** | Air temperature is above the desired operating range | **Very hot**                                  |
| Between 15 °C and 35 °C |           — | Acceptable air temperature                           | **Air OK** *(subject to humidity conditions)* |
The temperature sensor reports measurements directly in degrees Celsius using the Grove DHT11 sensor library and therefore requires no additional software calibration.
# A.4 Humidity Thresholds
| Constant            |        Value | Interpretation                      | OLED Status                                      |
| ------------------- | -----------: | ----------------------------------- | ------------------------------------------------ |
| `HUMIDITY_LOW`      | **30.0 %RH** | Air is considered dry               | **Air dry**                                      |
| `HUMIDITY_HIGH`     | **70.0 %RH** | Air is considered excessively humid | **Very humid**                                   |
| Between 30% and 70% |            — | Acceptable humidity                 | **Air OK** *(subject to temperature conditions)* |
Like the temperature measurements, humidity values are supplied directly by the Grove DHT11 sensor library and therefore do not require manual calibration.
# A.5 Plant Advice Decision Priority
Unlike the individual sensor screens, the Plant Advice screen evaluates multiple environmental conditions before presenting a single recommendation to the user.

The decision logic follows a fixed priority order, ensuring that the most significant issue is displayed first.
| Priority | Condition Evaluated                                     | OLED Advice          |
| -------: | ------------------------------------------------------- | -------------------- |
|        1 | Air sensor unavailable                                  | **Check air sensor** |
|        2 | Soil moisture below threshold                           | **Water plant**      |
|        3 | Soil moisture above threshold                           | **Too much water**   |
|        4 | Light below threshold                                   | **Needs light**      |
|        5 | Light above threshold                                   | **Very bright**      |
|        6 | Temperature above threshold                             | **Too hot**          |
|        7 | Temperature below threshold                             | **Too cold**         |
|        8 | Humidity below threshold                                | **Air too dry**      |
|        9 | Humidity above threshold                                | **Air humid**        |
|       10 | All monitored conditions within their acceptable ranges | **Plant OK**         |
This ordered evaluation ensures that the OLED presents a single, concise recommendation rather than multiple simultaneous messages, making the system easier to interpret during demonstrations and classroom activities.

# A.6 Summary of Version 1.0.0 Threshold Constants
| Category      | Lower Threshold | Upper Threshold | Normal Operating Range |
| ------------- | --------------: | --------------: | ---------------------- |
| Light         |             30% |             80% | 30–80%                 |
| Soil Moisture |             30% |             80% | 30–80%                 |
| Temperature   |           15 °C |           35 °C | 15–35 °C               |
| Humidity      |          30% RH |          70% RH | 30–70% RH              |
