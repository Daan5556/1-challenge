# General Requirements

**Author:** Daan Eggen  
**Date:** 15/04/2026  
**Version:** 2.0

| Term           | Meaning                                                                 |
| -------------- | ----------------------------------------------------------------------- |
| MQTT           | A lightweight messaging protocol commonly used for IoT devices.         |
| TLS            | Transport Layer Security, used to protect data sent over the network.   |
| Gateway        | A device or service that connects nearby sensors to the central system. |
| Edge device    | A sensor node or small device that collects and sends measurements.     |
| Docker Compose | A tool for running multiple related containers together.                |
| ESP32          | A microcontroller often used for connected sensor and IoT projects.     |
| DHT sensor     | A sensor used to measure temperature and humidity.                      |
| Line protocol  | A text-based format for writing structured measurement data.            |
| Time-series DB | A database optimized for storing measurements over time.                |

---

## Abbreviations and terms

In this document, I will describe the general requirements for the Smart
Springfield infrastructure from a user perspective. The goal is not to describe
every technical detail, but to make clear what the system should make possible
for the people that use, maintain and depend on it.

The project is a smart city element. Springfield wants to collect data about
traffic, air quality, noise pollution, public transport punctuality and other
city conditions. This data should be collected by real and simulated sensors,
stored on a central platform and shown in a dashboard.

## Users

The system has a couple of different users. They all look at the same
infrastructure from a different angle.

| User                 | Goal                                                 |
| -------------------- | ---------------------------------------------------- |
| City operator        | Monitor the city and respond to changing conditions  |
| Maintenance engineer | Keep sensors, gateways and server services working   |
| System administrator | Manage access, security, storage and configuration   |
| Project demonstrator | Show the complete proof of concept in a reliable way |

## City operator requirements

- As a city operator, I want to see sensor data in a dashboard, so I can quickly
  understand what is happening in Springfield.
- As a city operator, I want data from multiple sensor types to be shown
  side-by-side, so traffic, air quality, noise and environmental measurements
  can be compared.
- As a city operator, I want the dashboard to update from live MQTT data, so I
  do not have to manually refresh files or run commands to inspect the city
  state.
- As a city operator, I want the system to trigger an alert when a measurement
  or device state becomes important, so I can react before the problem is only
  found afterwards.
- As a city operator, I want alerts to have at least two priority levels, so I
  can distinguish between a warning and a critical situation.

## Maintenance requirements

- As a maintenance engineer, I want every edge device to have a clear
  identifier, so I can trace measurements back to the device and location that
  produced them.
- As a maintenance engineer, I want every gateway to support a small private
  network for nearby edge devices, so sensors can be installed at intersections
  without needing a separate internet connection for every sensor.
- As a maintenance engineer, I want devices to reconnect automatically after a
  temporary network problem, so normal operation can continue without manually
  restarting every device.
- As a maintenance engineer, I want outgoing sensor messages to be buffered when
  connectivity is unavailable, so temporary failures do not immediately cause
  data loss.
- As a maintenance engineer, I want to monitor whether the MQTT broker and
  sensor publishers are reachable, so broken services or offline sensors can be
  detected.

## Administrator requirements

- As a system administrator, I want the MQTT broker to require authentication,
  so only known devices and services can publish or read sensor data.
- As a system administrator, I want the network to expose only the required
  services, so unnecessary attack surfaces are reduced.
- As a system administrator, I want the data transfer to be protected with TLS
  where possible, so credentials and sensor data cannot easily be read on the
  network.
- As a system administrator, I want secrets such as database tokens and broker
  settings to be stored outside committed configuration files, so the repository
  can be shared without leaking credentials.
- As a system administrator, I want a documented IP plan and topic layout, so
  the system stays predictable when more sensors or gateways are added.

## Proof of concept requirements

- As a project demonstrator, I want at least one real sensor connected to the
  system, so the setup proves that it works with physical hardware and not only
  with simulations.
- As a project demonstrator, I want simulated sensors to publish data in the
  same format as real sensors, so both sources can be processed by the same
  server platform.
- As a project demonstrator, I want the server stack to receive, store and
  visualize sensor data, so the complete data flow can be shown end-to-end.
- As a project demonstrator, I want one automatic action or alert to be
  triggered by sensor data, so the infrastructure demonstrates more than passive
  storage.
- As a project demonstrator, I want clear test steps with expected results, so
  the proof of concept can be repeated and verified.

## Quality requirements

- The infrastructure should be stable enough for a city monitoring use case. The
  network should maintain at least 99% availability per calendar month, measured
  by automated checks against the broker and important endpoints.
- The system should be easy to reproduce. Docker Compose is used where
  practical, because the server platform consists of multiple services that need
  to run together.
- The system should be beginner friendly. Configuration files, small scripts and
  standard tools are preferred over a complex custom platform.
- The system should be extensible. New sensor types should be addable by giving
  them an edge device id, a sensor type, a topic and a payload format that fits
  the existing schema.
- The system should fail visibly during development. Missing configuration,
  invalid payload settings or unreachable services should be easy to detect
  instead of silently producing incorrect data.

## Scope

The current proof of concept focuses on one Springfield intersection. It uses
real temperature and humidity data from an ESP32 with a DHT sensor, alongside
simulated sensors for the other city measurements.

The broader design still assumes that Springfield can grow to many gateways and
around 172 edge devices. The implementation therefore uses identifiers, MQTT
topics, line protocol payloads and a time-series database that can scale beyond
the first demonstration.
