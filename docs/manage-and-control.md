# Manage and Control

**Author:** Daan Eggen  
**Date:** 18/04/2026  
**Version:** 1.0

---

In this document, I describe how I perform activities related to control,
monitoring and optimization within the Smart Springfield challenge. These
activities are not separate from the technical implementation. They are needed
to keep development structured, to commission the platform in a controlled way
and to make sure the final system can be used and maintained reliably.

For this project, manage and control means that I do not only build the IoT
platform, but also keep track of what must be delivered, how I verify that it
works and how I improve it when I detect problems. That includes requirements,
testing, monitoring, configuration management and communication with the people
who depend on the system.

## Controlling development

I control the development of the project by working from documented structure
instead of making ad-hoc changes. A good example is `requirements.pdf`. In that
document, I translated the challenge into user and system requirements for
operators, maintenance engineers, administrators and the project demonstrator.

That requirements document gives me a reference point during development. When I
work on the MQTT pipeline, dashboard or sensor integration, I can check whether
the implementation still supports the original goals. This prevents me from
optimizing only for a technical detail while losing sight of the actual use
case.

I also keep the development structured by storing the platform configuration in
the repository. The Docker Compose files, Telegraf configuration, firmware code
and network documentation are all versioned together. This gives me control over
changes, because I can trace what was changed, why it was changed and which part
of the platform is affected.

The advantage of this approach is that the project becomes reproducible. If I
need to rebuild the server platform, explain the setup to a stakeholder or debug
a regression, I do not have to rely on memory. The required configuration and
design decisions are documented and stored as code.

## Deploying the platform

Control is also important when deploying the system. A smart city proof of
concept is only useful if the complete chain can be started, tested and shown in
a predictable way.

In this challenge, deploying means validating the flow from edge device to
dashboard:

1. a real or simulated sensor publishes MQTT data;
2. Telegraf subscribes to the correct topic;
3. InfluxDB stores the measurement;
4. Chronograf visualizes the result;
5. monitoring and alerting react when something goes wrong.

I support this process by documenting the platform architecture and the deployed
services in the server platform documentation and by keeping the topic
structure, addressing and sensor inventory documented in the network
documentation. This makes deployment more controlled, because I can verify each
layer separately instead of treating the system as a black box.

I also deliberately chose tools that support repeatable deployment. Docker
Compose allows me to start the server services in a known state. Standardized
MQTT topics and line protocol messages make it easier to validate whether sensor
data enters the platform in the expected format. This reduces the risk of manual
mistakes during setup and demonstration.

## Monitoring and optimization

After commissioning, the next control activity is monitoring the actual behavior
of the platform. For this part, `monitroing.pdf` is an important document. In
it, I describe how I extended the InfluxData stack with Kapacitor-based
alerting.

This is relevant for manage and control because dashboards alone are passive. A
graph may show that a sensor stopped publishing, but only after someone notices
it. Active monitoring gives me direct feedback when the system deviates from the
expected behavior.

Within this project, monitoring focuses on questions such as:

- Are sensors still publishing?
- Is the broker or ingestion pipeline reachable?
- Are server resources healthy enough to keep the platform running?
- Does an abnormal condition require operator attention?

The dead man alert on the traffic camera simulation is a good example of this.
It turns missing data into a visible alert instead of leaving the failure hidden
inside a dashboard. That improves control over the operational phase of the
project.

Monitoring also supports optimization. When I can observe the behavior of the
platform, I can make better decisions about improvements. For example, if I see
that a service is fragile, that sensor messages are not clear enough to trace or
that debugging is too difficult, I can improve the configuration, topic layout
or documentation. In that way, optimization is not guesswork, but a response to
measured behavior.

## Conclusion

In this project, I perform manage and control activities by combining
requirements, versioned configuration, commissioning steps and monitoring. That
gives structure to both the development process and the use of the final
platform.

Because of this approach, I can better justify design decisions, detect problems
earlier and explain the state of the system to others. That makes the Smart
Springfield challenge not only a technical implementation, but also a controlled
and monitorable ICT system.
