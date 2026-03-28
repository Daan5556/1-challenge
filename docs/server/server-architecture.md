<!-- markdownlint-disable MD013 -->

# Server Architecture

**Author:** Daan Eggen  
**Date:** 26/03/2026  
**Version:** 1.0

---

This document will describe the server-side processing platform that will be
connected to the MQTT broker. I will explore different options for this server
platform and compare them.

The broker will expose sensor data from 172 IoT edge devices. I would like to
setup a robust system to store and visualize this data efficiently. I'm looking
for a cost effective scalable solution.

## Self hosting vs cloud hosting

I think this decision is largely based on culture. If you have a team that is
passionate for server hardware, and they like configurating the software, I
think you will _save_ money by self hosting. However, there will be some risks
involved. I will compare these different models now.

|              | Self hosting                                  | Cloud hosting                                 |
| ------------ | --------------------------------------------- | --------------------------------------------- |
| Complexity   | Requires server knowledge and more setup time | Accesible and quick to setup                  |
| Price        | Expensive initial investment                  | Low price at entry level                      |
| Security     | Security needs to be configured and updated   | Security is managed by provider               |
| Connectivity | Services are available in private network     | Services are only reachable over the internet |

### Risks of self hosting

With self hosting, you **own your own hardware**. That could cause issues later
down the line. If you have to scale up, you might be stuck with your current
setup. In the cloud, you can dynamically scale up and down very easily.

You also have to **manage your own security**. Cloud providers have very large
teams that specialize in securing servers. Doing it on your own means that you
have to spend time analyzing and updating for security risks.

### Risks of using a cloud provider

The more and more service you use from one specific cloud provider, the harder
it becomes to leave for another. In the industry, they call this **vendor
lock-in** Providers can even be more aggressive, and charge you to leave.

**Lack of control** is another risk of cloud computing. You're not in charge of
the systems you run. Which could mean unexpected downtime, deprecating of
services you use.

### Freedom to Host

The resource usage of this project is really stable. We can predict very well
how many users and devices will be connected to the server. So, we will not
benefit that much from the cloud capabilities for dynamic scaling. We also have
a team that likes to work with physical hardware. Plus, digital sovereignty is a
really important topic nowadays. So self hosting offers the "Smart Springfield
Program" a lot of freedom.

## Server Software Stack

Now that we decided to self host, its time to decide _what_ to host. The server
has the following responsibilities:

- **Data ingestion:** Collecting the data from the MQTT broker and storing it.
- **Visualization of data:** Using the stored data to create graphs in a
  dashboard.
- **Monitoring of the system:** Collecting data about the system, like uptime
  and device status.

Based on these responsibilities, we can setup a couple of weighted priorities.

- Ingestion performance (25%)
- Query performance (20%)
- Ease of use (20%)
- Scalability (15%)
- Ecosystem/tooling (20%)

Next, I looked at some popular, self hosted options for IoT database stacks. I
put the top 4 in the decision matrix, and started grading based on the
priorities.

| Criteria              | Weight | InfluxDB | TimescaleDB | MongoDB (TS) | VictoriaMetrics |
| --------------------- | ------ | -------- | ----------- | ------------ | --------------- |
| Ingestion performance | 25%    | **9**    | 7           | 6            | **10**          |
| Query performance     | 20%    | 7        | **9**       | 6            | 7               |
| Ease of use           | 20%    | **9**    | 7           | 8            | 7               |
| Scalability           | 15%    | 8        | 8           | 7            | **9**           |
| Ecosystem/tooling     | 20%    | **9**    | 9           | 9            | 8               |

The stack with the most points is **InfluxDB**. This platform has excellent
tooling and great documentation. I'm looking forward to implementing a data
pipeline using this stack.
