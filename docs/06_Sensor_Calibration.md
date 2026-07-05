## Sensor Calibration
# Purpose

Accurate environmental monitoring depends not only on selecting appropriate sensors but also on understanding how those sensors behave under real operating conditions. Although manufacturers typically provide nominal specifications for their devices, practical implementation often requires additional testing to determine how sensors respond within a particular application.

For the Smart Garden Helper, calibration was not viewed as a one-time configuration step. Instead, it formed an iterative engineering process involving repeated observation, experimentation, troubleshooting, and refinement. Each sensor was evaluated independently before being integrated into the complete monitoring system, allowing its behaviour to be understood without interference from the rest of the application.

The objective of calibration within this project was not to obtain laboratory-grade accuracy, but rather to produce reliable and repeatable measurements suitable for demonstrating embedded sensing principles and supporting simple decision-making within the Smart Garden Helper.

The modular approach used during calibration is discussed in 05_Modularity.md, while the hardware characteristics of each sensor are described in 03_Hardware.md. The software architecture that applies the calibrated values is described in 04_Software_Architecture.md.

# Calibration Philosophy

One of the most important lessons learned during development was that every sensor behaves differently.

Some sensors produce measurements that are already calibrated by the manufacturer and require little additional configuration. Others provide raw analogue values that must be interpreted through software before they become meaningful.

Consequently, calibration was performed according to the characteristics of each sensor rather than applying a single approach across the entire system.

Throughout development the following general calibration procedure was adopted:

Develop the sensor module independently.
Observe raw sensor readings under different environmental conditions.
Compare readings with expected physical behaviour.
Identify abnormal or inconsistent behaviour.
Investigate whether the cause originated from software, hardware, or wiring.
Update calibration constants where appropriate.
Repeat testing until measurements became stable and repeatable.
Integrate the calibrated module into the complete Smart Garden Helper.

This iterative process ensured that each sensor module reached a reliable operating state before system integration.

---

## Temperature Sensor Calibration
# Sensor Overview

The Grove Beginner Kit includes an integrated temperature and humidity sensor capable of directly reporting ambient air temperature.

Unlike analogue sensors that produce raw voltage measurements, the sensor performs much of its own internal signal processing before communicating with the Arduino.

As a result, the values returned by the accompanying Grove library are already expressed in engineering units (degrees Celsius).

# Calibration Requirements

No manual calibration was required for the temperature measurements.

The sensor library provided stable and realistic temperature readings throughout development without requiring correction factors or offset adjustments.

Development therefore focused primarily on verifying that measured temperatures responded appropriately to environmental changes.

Testing included:

Observing ambient room temperature,
Placing a hand near the sensor,
Relocating the board between different environments.

Each of these tests produced small but observable temperature changes consistent with expected behaviour.

# Threshold Selection

Although the temperature values themselves required no calibration, threshold values were still required for decision-making within the Smart Garden Helper.

These thresholds determine when the OLED displays messages such as:

Too Cold
Air OK
Too Hot

The threshold values were intentionally selected to provide clear educational demonstrations rather than represent precise agricultural recommendations.

Complete threshold definitions are documented in 07_Threshold_Logic.md.

---

## Humidity Sensor Calibration
# Sensor Overview

The humidity sensor is integrated with the same Grove environmental sensing module used for temperature measurement.

The sensor reports relative humidity as a percentage, representing the amount of moisture present in the surrounding air.

# Calibration Requirements

Like the temperature sensor, the humidity sensor communicates calibrated engineering values through the Grove software library.

No manual calibration was required.

Testing focused on confirming that humidity readings responded to changes in local atmospheric conditions.

Demonstration activities included:

Breathing gently near the sensor,
Moving the sensor between different locations,
Observing gradual changes over time.

Although humidity changes occurred more slowly than light or soil moisture measurements, the readings remained consistent throughout testing.

# Threshold Selection

Threshold values were selected to classify environmental conditions into simple categories suitable for educational demonstrations.

Example OLED messages include:

Air Dry
Air OK
Very Humid

The decision logic associated with these thresholds is documented in 07_Threshold_Logic.md.

---

## Light Sensor Calibration
# Sensor Overview

The Grove Beginner Kit includes an analogue light sensor that measures ambient illumination.

Unlike the temperature and humidity sensor, the light sensor outputs an analogue value that must be interpreted by software before becoming meaningful to the user.

For the Smart Garden Helper, raw analogue measurements were converted into percentages to improve readability on the OLED display.

# Initial Testing

The light sensor was evaluated under a variety of lighting conditions, including:

Normal indoor lighting,
Covering the sensor by hand,
Partial shading,
Illumination using one or more torch lights,
Exposure to the brightest available indoor conditions.

As expected, the analogue readings changed consistently as lighting conditions changed.

This confirmed that the sensor was functioning correctly.

# Observed Behaviour

Although the sensor responded reliably to changes in brightness, an unexpected limitation was observed during testing.

Despite repeated attempts to expose the sensor to brighter light sources, the calculated light percentage consistently reached a maximum value of approximately 73%.

Increasing the brightness beyond this point produced little or no further increase in the reported percentage.

Repeated testing confirmed that this behaviour was repeatable.

# Engineering Interpretation

Initially, it was suspected that the software conversion formula might be responsible for the apparent limitation.

However, further testing suggested that the sensor itself had effectively reached its practical measurement limit under the available testing conditions.

This observation demonstrated an important engineering principle:

Real sensors do not always utilise their full theoretical operating range.

Rather than modifying the software to artificially force the sensor to report 100%, the observed behaviour was documented and incorporated into later threshold selection.

This approach preserves measurement integrity while accurately representing the behaviour of the physical hardware.

# Calibration Notes

No correction factors were applied to the light sensor.

Instead, threshold values were chosen using experimentally observed measurements rather than theoretical limits.

Future deployments in different environments may require additional testing to determine appropriate threshold values.

---

## Soil Moisture Sensor Calibration
# Sensor Overview

The Smart Garden Helper extends the Grove Beginner Kit by incorporating the DFRobot Gravity Analog Soil Moisture Sensor V2.

Unlike the integrated environmental sensor, this device produces raw analogue measurements that require software calibration before meaningful moisture percentages can be calculated.

Because soil properties vary considerably between environments, no universal calibration values exist.

Calibration therefore formed one of the largest engineering tasks within Version 1.0.0.

# Initial Calibration

The first implementation adopted the following calibration constants:

const int MOISTURE_DRY_RAW = 1023;
const int MOISTURE_WET_RAW = 300;

These values were based on expected analogue behaviour and commonly reported calibration ranges.

The raw analogue measurement was converted into a moisture percentage using Arduino's map() function.

# Initial Behaviour

Although the software compiled correctly and raw analogue readings changed slightly, the calculated moisture percentage remained almost constant.

Typical percentage values ranged between:

0% – 1%

This behaviour persisted even under conditions that should have produced significant changes.

For example:

dry probe,
damp soil,
wet soil,
probe submerged in water.

The system clearly failed to represent the physical environment accurately.

## Investigation

At this stage several possible causes were considered.

# Software

The percentage conversion formula was reviewed.

The mapping operation appeared mathematically correct.

# Calibration Constants

The dry and wet calibration values were adjusted several times.

Although small improvements occurred, the reported moisture percentage remained unrealistic.

# Sensor Hardware

A defective moisture sensor was considered.

Multiple sensor modules were tested.

The behaviour remained essentially unchanged.

This suggested that the sensor itself was unlikely to be faulty.

# Wiring

Attention then shifted toward the hardware connections.

Because the sensor communicates using analogue signals, poor signal quality or incorrect routing can significantly influence measured values.

Further investigation eventually identified the analogue signal routing as the primary source of the instability.

# Root Cause

The original analogue signal routing produced unstable measurements that prevented the software calibration from functioning correctly.

After rerouting the analogue signal connection and verifying the wiring, the raw measurements became substantially more stable.

Only after reliable analogue data had been obtained were the calibration constants updated.

This experience reinforced one of the most important lessons learned during development:

Not every measurement problem originates from software.

In embedded systems, apparent software faults frequently originate from hardware wiring, electrical noise, or incorrect signal connections.

# Final Calibration

Following hardware correction, experimental testing was repeated under multiple soil conditions.

The calibration constants were adjusted until the calculated moisture percentage more accurately reflected observed soil conditions.

The final Version 1.0.0 software uses:

const int MOISTURE_DRY_RAW = 0;
const int MOISTURE_WET_RAW = 821;

const int MOISTURE_LOW = 30;
const int MOISTURE_HIGH = 80;

These values represent the experimentally determined calibration constants used throughout Version 1.0.0.

# Limitations

Several limitations should be noted when interpreting the soil moisture measurements.

Soil moisture sensors measure electrical properties rather than water content directly.
Different soil compositions produce different analogue responses.
Probe cleanliness and age can influence measurements.
Soil compaction affects sensor readings.
Environmental conditions such as temperature may introduce minor variations.

Consequently, calibration values should be viewed as application-specific rather than universally applicable.

Future implementations should repeat the calibration process whenever the sensor or operating environment changes.

# Lessons Learned

The calibration process provided several valuable engineering lessons that extend beyond this specific project.

Manufacturer specifications provide useful starting points but should not replace experimental testing.
Analogue sensors generally require significantly more calibration than digital sensors.
Stable hardware connections must be verified before attempting software modifications.
Calibration is an iterative engineering activity rather than a single configuration step.
Recording calibration values alongside source code improves reproducibility and simplifies future maintenance.

These observations influenced not only the implementation of Version 1.0.0 but also the planned development methodology for future versions of the Smart Garden Helper.

---

# Calibration Summary

Sensor calibration formed an essential part of the Smart Garden Helper development process. While the integrated temperature and humidity sensor operated reliably using manufacturer-provided calibration through the Grove libraries, the analogue light and soil moisture sensors required practical evaluation under real operating conditions.

In particular, the soil moisture sensor demonstrated that successful embedded systems development depends as much on careful hardware investigation as it does on software design. By systematically observing sensor behaviour, testing alternative explanations, correcting hardware issues, and documenting the final calibration values, Version 1.0.0 captures not only the finished implementation but also the engineering reasoning behind it.

For the threshold values that interpret these calibrated measurements into user-facing advice, refer to 07_Threshold_Logic.md. For the hardware characteristics of each sensor, see 03_Hardware.md, and for the modular development strategy used to calibrate each subsystem independently, refer to 05_Modularity.md.
