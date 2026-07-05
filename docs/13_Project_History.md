# Project Timeline
# 6 February 2026: Project Introduction

The Sensor School project was formally introduced as part of the Joint Community Project (JCP) module.

During this introduction, students were informed that they would later facilitate a week-long Sensor School programme for high school learners. The overall objectives of the project, community partnerships, expected deliverables, and assessment requirements were presented.

At this stage, no technical development had begun. The focus was on understanding the purpose of the project and the broader educational goals of the JCP module.

## Milestone
Sensor School project introduced.
Community engagement objectives explained.
Teaching week and learner competition announced.
Initial understanding of project expectations established.
# 30 March 2026: Initial Technical Training

The first practical training session introduced the hardware that would later form the basis of the Smart Garden Helper.

Students, along with me, were introduced to the Grove Beginner Kit for Arduino and gained experience with:

Arduino programming fundamentals,
Analogue and digital sensors,
Serial Monitor output,
Simple Arduino sketches,
Basic sensor testing,
Introductory embedded systems concepts.

This session provided the technical foundation required for future project development.

## Milestone
First experience with the Grove Beginner Kit.
Initial sensor testing completed.
Arduino programming was introduced.
Basic hardware familiarity established.
# 28 May 2026 — System Planning and Refinement

The second technical workshop shifted attention from individual sensors toward designing a complete educational demonstration.

During this session, sensor modules were tested in greater detail, and the overall project direction became clearer.

It was during this refinement phase that the concept of integrating multiple sensors into a single Smart Garden Helper emerged.

Rather than presenting isolated demonstrations, the project evolved into a unified embedded system capable of monitoring several environmental conditions while providing meaningful feedback through a structured OLED interface.

The concept of multiple OLED display states, navigated using the Grove push-button, was also developed during this phase. This architectural decision would later become one of the defining features of Version 1.0.0.

Sensor calibration also began during this period, particularly for the external soil moisture sensor, whose integration required additional testing and hardware troubleshooting.

## Milestone
Integrated system concept established.
OLED state-machine interface proposed.
Modular software architecture planned.
Sensor calibration initiated.
Initial system architecture defined.
# June 2026: Software Development

Following the refinement workshop, software development progressed independently.

Development followed a modular approach in which each subsystem was implemented and tested separately before integration.

Major software components developed during this phase included:

Temperature and humidity module,
Light sensing module,
Soil moisture module,
Threshold logic,
OLED display functions,
Button navigation,
Plant Advice decision logic,
Integrated system architecture.

Each module was validated individually before being incorporated into the complete Smart Garden Helper.

## Milestone
Individual sensor modules completed.
Threshold logic implemented.
OLED interface developed.
Button-controlled state machine implemented.
Complete Smart Garden Helper integrated.
# 29 June – 2 July 2026: Sensor School Implementation

The completed Smart Garden Helper formed the centrepiece of the Sensor School workshops delivered to high school learners.

Across four days, learners were introduced to:

Electricity and sensing,
Environmental sensors,
Calibration,
Threshold logic,
Modular software design,
Systems thinking,
Integrated embedded systems.

Rather than focusing on programming syntax, the workshops emphasised conceptual understanding through demonstrations, learner activities and interactive discussions.

Each sensor was first explored independently before learners observed how the individual modules combined into a complete Smart Garden Helper.

The week concluded with a mini engineering competition in which learners presented their own understanding of the system and its operation.

## Milestone
Four-day Sensor School successfully delivered.
Smart Garden Helper was demonstrated to learners.
Interactive learner activities completed.
Final learner presentations and competition were conducted.
3–5 July 2026 — Version 1.0.0 Documentation

Following completion of the Sensor School workshops, attention shifted toward documenting the engineering work completed throughout the project.

A public GitHub repository was created to preserve both the source code and the engineering decisions behind Version 1.0.0.

Rather than uploading only the final Arduino sketch, the repository was designed as comprehensive technical documentation covering:

System architecture,
Hardware configuration,
Software design,
Calibration,
Threshold logic,
OLED state machine,
Testing,
Debugging,
Engineering decisions,
Lessons learned,
Future work.

The objective was to create an engineering record that documents not only the final implementation but also the reasoning and development process that produced it.

## Milestone
GitHub repository created.
Version 1.0.0 documented.
Engineering documentation completed.
Project formally archived as Version 1.0.0.
# Project Evolution
6 Feb 2026
Project introduced
        │
        ▼
30 Mar 2026
Initial sensor training
        │
        ▼
28 May 2026
System planning and refinement
        │
        ▼
June 2026
Modular software development
        │
        ▼
29 Jun – 2 Jul 2026
Sensor School implementation
        │
        ▼
3–5 Jul 2026
GitHub repository and Version 1.0.0 documentation

# Reflection

The Smart Garden Helper Version 1.0.0 evolved from an educational community engagement project into a fully documented embedded systems project. What began as introductory training with sensors developed into the design of a modular environmental monitoring system capable of integrating multiple sensors, processing environmental data through threshold-based logic, and presenting meaningful feedback via a state-driven OLED interface.

Beyond the technical implementation, the project also strengthened skills in systems thinking, embedded software architecture, hardware integration, technical communication, project leadership, and engineering documentation. The completion of Version 1.0.0 represents both the conclusion of the initial Sensor School project and the foundation for future iterations that may incorporate automation, wireless connectivity, and broader smart agriculture applications.
