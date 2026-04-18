# Professional Standard

**Author:** Daan Eggen  
**Date:** 18/04/2026  
**Version:** 1.0

---

In this document, I describe how I apply a professional standard within the
Smart Springfield challenge. This learning outcome is not only about the final
technical result, but also about the way I work toward that result. It asks me
to use a relevant methodological approach, involve stakeholders, conduct applied
research, justify decisions and report my work in a professional way.

For this project, I apply that professional standard by working in a structured
engineering process. I define goals, analyse requirements, compare solution
options, implement and validate the chosen design and document both the outcome
and the reasoning behind it. Throughout that process, I also keep ethical,
intercultural and sustainable aspects in view.

## Methodological approach

The methodological approach I use in this challenge is a practical engineering
cycle. I start by identifying the problem and the context of the assignment.
After that, I translate the challenge into requirements, explore design options,
make reasoned choices, implement the selected solution and then validate whether
the result meets the goals.

This approach is visible in the structure of the repository. The documents do
not only describe what I built, but also how I came to certain choices. For
example:

- `requirements.pdf` defines the project goals from different user perspectives
- `network-analysis.pdf` compares network devices and communication protocols
- `server-architecture.pdf` compares different server-side platform options
- `server-platform.pdf` translates the chosen architecture into an
  implementation
- `monitoring.pdf` describes how I added active monitoring and alerting

Because of this structure, the project is more than a collection of technical
parts. It becomes a traceable design process in which goals, research, choices
and implementation are linked together.

## Formulating project goals

I formulate project goals by translating the Smart Springfield challenge into
practical objectives for the platform. The city wants insight into traffic, air
quality, noise pollution and other conditions, so the platform has to collect,
store and visualize sensor data in a reliable way.

I made these goals concrete in `requirements.pdf`. In that document, I
describe requirements from the perspective of several users, such as the city
operator, maintenance engineer, system administrator and project demonstrator.
That helps me keep the goals grounded in actual use cases instead of treating
the project as a purely technical exercise.

This is a professional way of working because it creates alignment between the
assignment and the implementation. It also makes it easier to evaluate later
whether the result really supports the people who would use or maintain the
system.

## Involving stakeholders

The project includes several stakeholders who all have different interests.
Operators want visibility of the city state, maintenance engineers want to
diagnose failures, administrators want control over security and configuration,
and assessors want to understand the design decisions and results.

I involve these stakeholders mainly by documenting the project from their point
of view and by letting those viewpoints influence my design decisions. For
example:

- operators are represented through dashboard and alerting requirements
- maintenance engineers are represented through monitoring, device identifiers
  and troubleshooting visibility
- administrators are represented through security, topic structure and
  configuration management
- assessors are represented through the design documents, research documents and
  end-to-end demonstration material

Even in an individual challenge, stakeholder involvement still matters. It means
that I do not optimize only for what I personally find interesting, but for what
different users and decision makers actually need from the system.

## Conducting applied research

Applied research is an important part of this project. Before implementing the
platform, I first investigated several technologies and compared them based on
the needs of the challenge.

In `network-analysis.pdf`, I compare edge devices, gateways and communication
protocols. In `server-architecture.pdf`, I compare different self-hosted data
platforms for time-series storage and visualization. These documents show that
I did not choose technologies randomly. I looked at criteria such as
reliability, scalability, ease of use, performance and practical deployment.

This research is applied research because it is directly connected to the
project context. The purpose is not only to gather theoretical knowledge, but to
support concrete engineering decisions in the Smart Springfield proof of
concept.

## Advising and decision making

A professional standard also means that I can provide advice and make decisions
based on argumentation. In this project, that can be seen in the way I justify
choices such as MQTT for messaging, self-hosting for the platform and InfluxDB
for time-series storage.

These decisions are not presented as preferences without support. They are tied
to the constraints and goals of the project. For example, MQTT fits the IoT use
case because it supports lightweight publish/subscribe communication. InfluxDB
fits because the system deals with real-time sensor measurements. Monitoring and
alerting are added because a dashboard alone is not enough for operational
control.

This way of working is important in the professional field. A technical decision
has more value when it is transparent, explainable and related to the needs of
the stakeholders and the system.

## Delivering reports and evidence

Another part of the learning outcome is reporting. Within this project, I
deliver reports by documenting different aspects of the design and
implementation in separate but connected documents.

These reports include:

- research and decision documents
- technical design and implementation documents
- monitoring and operational documents
- demo-oriented documents that show validation of the complete chain

This documentation supports professional communication. It allows others to
understand the project without needing all information from a live explanation.
It also provides evidence that the work was performed in a structured way and
that the design decisions can be traced back to requirements and research.

## Ethical aspects

The Smart Springfield challenge deals with monitoring a city environment. That
means ethical aspects must be kept in view, especially around data collection
and system control.

For this project, the most relevant ethical aspect is proportionality. A city
monitoring system should collect data that is necessary for the goal of the
platform, but not more than that. In the proof of concept, I focus on technical
sensor values such as temperature, humidity, traffic counts and other
environmental measurements. That is a more responsible basis than collecting
unnecessary personal or identifying data.

Another ethical aspect is transparency. If a system monitors public space, the
stakeholders who manage it should understand what is being measured, where the
data goes and how alerts are triggered. My documentation contributes to that
transparency by making the system design and data flow visible.

## Intercultural aspects

Intercultural awareness is also relevant, even in a technical project. Smart
city systems affect different groups of people, and those groups may not all
have the same expectations, technical background or priorities.

In practice, this means I should communicate clearly and avoid assuming that one
technical perspective is enough. A system administrator, operator and assessor
all interpret the project differently. By documenting the platform in accessible
and role-focused ways, I make it easier for different stakeholders to understand
the system from their own context.

This matters in professional collaboration, because technical quality alone is
not sufficient if the solution cannot be understood, explained or maintained by
others.

## Sustainable aspects

Sustainability is relevant for both the technical choices and the long-term use
of the system. In this project, sustainability is visible in several ways.

First, I choose a design that is modular and reproducible. A reproducible setup
is easier to maintain, repair and extend, which improves the lifespan of the
system. Second, I use lightweight messaging and targeted monitoring, which fits
an IoT environment where efficiency matters. Third, I select relatively compact
edge hardware such as the ESP32, which is appropriate for low-power sensor
tasks.

Sustainability also means avoiding waste in the development process. By using
documentation, versioned configuration and a structured architecture, I reduce
the chance of unnecessary rework and make the project easier to continue in the
future.

## Conclusion

In this challenge, I apply a professional standard by using a structured
methodological approach to define goals, involve stakeholders, conduct applied
research, justify decisions and report the results. I support this with
documentation that connects requirements, research, implementation, monitoring
and validation.

At the same time, I keep ethical, intercultural and sustainable aspects in view.
Because of that, the project is not only a technical proof of concept, but also
an example of professional engineering practice.
