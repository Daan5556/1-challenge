# End-to-end demo

**Author:** Daan Eggen  
**Date:** 18/04/2026  
**Version:** 1.0

---

In this document, I describe the end-to-end demonstration of the Smart
Springfield proof of concept. The goal of this demo is to show that the full
chain works in practice: from edge network connectivity and MQTT messaging to
database storage, dashboard visualization and alerting.

The demo combines both simulated sensors and a real ESP32-based sensor. This is
important because it shows that the platform does not only work for scripted
test traffic, but also for an actual physical edge device.

## Raspberry Pi as gateway

The first step in the demonstration is preparing the Raspberry Pi as the local
gateway. In this setup, the Raspberry Pi runs the MQTT broker and also provides
a Wi-Fi access point for nearby edge devices.

This gives the project a clear edge architecture:

- The Raspberry Pi acts as the local communication point
- Simulated sensors connect to the Pi over Wi-Fi
- The ESP32 connects to the same Wi-Fi network
- The broker on the Pi receives all sensor messages

Using the Raspberry Pi in this role is practical for the demo, because it brings
network access and message collection together on one device. That makes it
easier to validate the setup in a controlled environment before data is sent
further into the platform.

## Connecting the simulated sensors

After the Raspberry Pi is prepared, I connect the simulated sensors to the Wi-Fi
access point hosted by the Pi. These sensors publish MQTT messages to the broker
running on the same gateway.

To verify that this part of the chain works, I subscribe to the MQTT topic from
my host machine using `mosquitto_sub`. This allows me to confirm that the
messages are actually arriving at the broker and that the payloads are in the
expected line protocol format.

During the demo, I showed this with the following command:

```bash
mosquitto_sub -h rpi.local -t 'sensors/#'
```

If I want to show broker-side activity or logs on the Raspberry Pi itself, I can
also use:

```bash
docker logs -f mosquitto
```

This validation step is important. Before looking at databases or dashboards, I
first want proof that the messages exist on the messaging layer itself. If the
payload does not appear here, then the rest of the chain cannot work either.

## Connecting the ESP32

Once the simulated sensors are working, I turn on the ESP32 with the flashed
firmware. This firmware connects to the Raspberry Pi access point, reads the DHT
sensor and publishes temperature and humidity values to MQTT.

Just like with the simulated sensors, I validate the ESP32 messages on the MQTT
layer first. Again, I use `mosquitto_sub` on the host machine to check that the
device connects successfully and publishes the expected payload.

The same MQTT subscription can stay open during this step:

```bash
mosquitto_sub -h rpi.local -t 'sensors/#'
```

This part of the demo shows that the platform supports both software-generated
sensor traffic and data from a real physical edge device. That is an important
step in the proof of concept, because it demonstrates that the architecture is
not limited to simulations.

## Validating database storage

After confirming that MQTT messages are arriving correctly, I move to the
database layer. At this point, Telegraf subscribes to the MQTT topics and
forwards the messages into InfluxDB 3.

To show that the ingestion pipeline works, I run a CLI query against the
database. This allows me to demonstrate that the sensor data is not only visible
on the broker, but is also actually stored in the time-series database.

I can also show the Telegraf logs while it is forwarding the MQTT messages:

```bash
docker logs -f telegraf
```

After that, I query the database directly:

```bash
docker exec -it influxdb3 influxdb3 query \
  "SELECT * FROM temperature_and_humidity"
```

This validation proves several things at once:

- Telegraf can read from MQTT;
- the line protocol messages are valid;
- InfluxDB accepts and stores the measurements;
- the records can be queried again afterwards.

By checking the data from the command line, I can demonstrate the stored values
directly without depending on a visual dashboard.

## Showing the dashboard

After the CLI query confirms that the data is stored, I show the dashboard in
Chronograf. This completes the user-facing part of the end-to-end flow, because
the sensor data is now visible as charts.

The following screenshot shows the dashboard used in the proof of concept:

![dashboard](assets/dashboard-GW.png)

This dashboard combines the available sensor streams into one view. In the demo,
it shows that the data collected through the Raspberry Pi gateway and processed
by the server platform can be explored visually by an operator.

## Demonstrating alerting

The final step of the demo is to show that the platform does more than only
store and visualize data. I also demonstrate the dead man alert by disabling one
of the sensor simulations.

To trigger this during the demo, I stop the running simulation process or
container. For example:

```bash
docker stop docker stop sensor-simulation-traffic-camera-1
```

When that simulated sensor stops publishing, Kapacitor detects the missing data
stream after the configured time window and raises an alert. This proves that
the monitoring layer is working and that the platform can react when expected
sensor traffic disappears.

The alert can be seen in the following screenshot:

![Alert history](assets/alert-history.png)

This is a useful final step in the demo because it shows operational behavior.
The platform is not only able to process normal traffic, but can also detect
when that normal behavior stops.

## Conclusion

This end-to-end demonstration shows the complete Smart Springfield data flow in
practice. Starting from the Raspberry Pi gateway and Wi-Fi access point, I
connect simulated sensors and a real ESP32, validate the MQTT messages, confirm
database storage with a CLI query, visualize the data in Chronograf and finally
trigger a dead man alert by disabling a sensor simulation.

Because every layer is validated separately during the demo, I can clearly show
that the proof of concept works as an integrated and monitorable IoT system.
