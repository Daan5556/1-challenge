# Network Analysis

To ensure success for the "Safe Springfield" initiative I need to setup a
network of sensors, monitoring activity throughout the city. The sensor data
should be stored on a central service for monitoring. This document will go over
the requirements of the network.

| Abbreviation | Meaning                      |
| ------------ | ---------------------------- |
| SOC          | System on Chip               |
| GPIO         | General-Purpose Input/Output |

## Background

![Springfield](../assets/springfield_panoramic.png)

Springfield is a town of 50.000 residents. The local authority wants to get an
insight on traffic, air quality, noise pollution and punctuality of public
transport. They want to monitor this data from a secure easy to use platform. To
collect the all of the activity, I need a lot of sensors spread out over a large
area. This asks for a stable network!

## Requirements

- The network has to be private. Only authorized devices can connect.
- A single point of failure must not lead to data loss.
- The network must have an uptime of 99%.

## Devices

In this section I'm going to analyse different edge devices to connect to the
sensors. I'm looking for a reliable, compact and cost effective device.

### Raspberry Pi 5

This computer has a dedicated Wi-Fi module, which will greatly improve the
stability of the network. This way, we I can even connect it directly to the
central server without an edge device. It also has a huge amount of RAM (8GB),
which I can use to cache data when another network down in unavailable.

However, the price of this computer is really steep. It also has a large
footprint, making it hard to use it in small spaces. The specs of this machine
are a little overkill for reading some sensor data, so it might be wise to see
other options.

### Arduino Nano 33

This board is equipped with the capable **ATmega328 microcontroller**. This chip
is very energy efficient. And it even has sleep modes, making it even draw less
power when no sensor data is being read. And unlike the Raspberry Pi, it can
sustain a wider range of thermal ranges, with a minimum of -40°C and a maximum
of 85°C. Making it well suitable for a device that needs to operate outside and
year round.

The downside of this board is that it doesn't have wireless communication like
Wi-Fi or Bluetooth. To connect this to the network I would have to use USB. This
is not practical due to the location of the sensors I need to gather data from.

### ESP32

So, this SOC has an 32-bit microprocessor, 512KB of RAM, and wireless
capabilities with Wi-Fi and Bluetooth! It has the same thermal limits as the
Arduino Nano, and 32 GPIOs, more than plenty for the sensor data. This board is
also the cheapest option, so I think it would be an excellent choice for my
project.

### Edge gateways

## Protocols

## Network diagram
