# Sensor Simulation

**Author:** Daan Eggen  
**Date:** 02/04/2026  
**Version:** 1.0

---

To demonstrate the proof of concept, I need to simulate some sensors. The proof
of concept consists a demonstration of a single intersection in the city. I'm
going to use 2 real, physical sensors and 4 simulated ones, as you can see from
this table.

| EdgeDeviceId | SensorType             | Real/Simulated |
| ------------ | ---------------------- | -------------- |
| ED-1022-01   | TrafficCamera          | Simulated      |
| ED-1022-02   | AirQuality             | Real           |
| ED-1022-03   | Noise                  | Simulated      |
| ED-1022-04   | TemperatureAndHumidity | Real           |
| ED-1022-05   | ParkingSensor          | Simulated      |
| ED-1022-06   | WaterQuality           | Simulated      |
| ED-1022-07   | Seismic                | Simulated      |

The simulated edge devices have to connect to an MQTT broker and publish fake
sensor data at an interval.

## Software Stack

To make this as realistic as possible, I will have the simulated sensors run in
Docker containers, so they can represent different hosts.

As for the language I'm going to use to program this, I think Python is a good
choice. Because it's a small script, that will not run in production. Plus,
Python is already used in this project.

## Packages

Because I'm going to need an MQTT client in this app, I decided to use a
package[^paho-mqtt] that will handle the connection and the publishing of
messages to the broker.

## Project Structure

Its an art form really to setup a project nicely and make it quick and easy to
read and run. I will use Mise[^mise] to handle run time versions and setting up
the environment. In the Mise configuration file (`mise.toml`) I will pin the
Python version, activate the Python virtual environment and load in the
environment variables from the `.env` file.

```toml
[tools]
python = "3.14"

[env]
_.python.venv = ".venv"

[env.mise]
file = ".env"
```

Because a lot of the simulation logic is the same between different edge
devices, only differing in the payload that is published to the broker, I
decided to create a single app, making the payload customizable via environment
variables. That means I will have a Docker compose file (`compose.yaml`) at the
root, where I can specify the different instances of the simulation, and then
have the simulation project as a sub directory. There I will have the entry
point of the app (`main.py`), and a payload specific logic (`payload.py`). I
will also have the `Dockerfile` there to containerize the app + the pinned
dependencies (`Requirements.txt`). Resulting in the following project structure:

```plaintext
.
├── compose.yaml
├── mise.toml
└── sensor-simulation
    ├── Dockerfile
    ├── main.py
    ├── payload.py
    └── Requirements.txt
```

On top of the `main.py` file I will ad a shebang, and I will make the file
executable.

```bash
#! /usr/bin/env python
```

This makes it so the script can be invoked like:

```bash
$   ./main.py
```

Which is just a good practice to have.

## Configuration

The application needs certain configuration values. By accessing these trough
the `environ` dictionary provided by the runtime, I also get some validation,
because the app will crash if one of the values is missing, this follows the
"fail fast" principle, which means that if the application is in an undefined
state, it will stop execution. This ensures that all of the configuration values
are present during the `main()` function.

```python
MQTT_HOST = os.environ["MQTT_HOST"]
EDGE_DEVICE_IDENTIFIER = os.environ["EDGE_DEVICE_ID"]
SENSOR_TYPE = os.environ["SENSOR_TYPE"]
```

## Payload

For the payload, I will use the `SENSOR_TYPE` configuration value from the
previous section, lets say I want to simulate the "Traffic Camera" sensor, the
`SENSOR_TYPE` would be 1. The generate payload function will first try to parse
this to an int, making it fail fast if its anything else then an int. It then
tries to match it to a specific sensor.

```python
def generate(sensortype) -> str:
    sensortype = int(sensortype)
    match sensortype:
        case 1:
            return _generate_traffic_camera()
        # ...
```

The `_generate_traffic_camera` function will generate a payload using a
"Gaussian distribution" algorithm. Making the payload random and also more
realistic.

```python
def _generate_traffic_camera():
    mean = 50
    std_dev = 10
    measurement = int(random.gauss(mean, std_dev))

    return f"value={measurement}"
```

## Main loop

Now that everything is setup, I can create the main loop of the application. The
way to do this, is in a `while True` loop with a `time.sleep()`. Before the
loop, I will make the connection to the MQTT broker.

```python
mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.connect(MQTT_HOST)
```

The `connect` function call is blocking, and will also trow when its unable to
connect to the broker, adhering to the "fail fast" principle.

In the loop, I will generate the payload, create the line protocol string and
publish it as a message to the broker before waiting 5 seconds. With some error
handling added, the main function will look like this:

```python
def main():
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    mqttc.connect(MQTT_HOST)
    mqttc.loop_start()

    try:
        while True:
            measurements = payload.generate(SENSOR_TYPE)
            line = (
                f"{TABLE_NAME},edge_device_id={EDGE_DEVICE_IDENTIFIER} {measurements}"
            )

            print(line)

            mqttc.publish(MQTT_TOPIC, line)
            time.sleep(5)
    except KeyboardInterrupt:
        pass
    finally:
        mqttc.loop_stop()
        mqttc.disconnect()
```

## Compose project

Because I made the project configurable via environment variables, I can supply
these in the running containers. This makes the compose project very lean, only
supplying these configuration values.

```yaml
services:
  traffic-camera:
    build: ./sensor-simulation
    environment:
      - MQTT_HOST
      - SENSOR_TYPE=1
      - EDGE_DEVICE_ID=ED-1022-01

  noise:
    build: ./sensor-simulation
    environment:
      - MQTT_HOST
      - SENSOR_TYPE=3
      - EDGE_DEVICE_ID=ED-1022-03

  parking-sensor:
    build: ./sensor-simulation
    environment:
      - MQTT_HOST
      - SENSOR_TYPE=5
      - EDGE_DEVICE_ID=ED-1022-05

  water-quality:
    build: ./sensor-simulation
    environment:
      - MQTT_HOST
      - SENSOR_TYPE=6
      - EDGE_DEVICE_ID=ED-1022-06

  seismic:
    build: ./sensor-simulation
    environment:
      - MQTT_HOST
      - SENSOR_TYPE=7
      - EDGE_DEVICE_ID=ED-1022-07
```

The `MQTT_HOST` value present in all of the services will be inherited from the
host machine, making it dynamic.

## Conclusion

I've managed to create a very simple and dynamic sensor simulation project. I've
used the fail fast principle for quick feedback.

I can quickly add and edit simulations via the `compose.yaml` file.

[^paho-mqtt]: https://pypi.org/project/paho-mqtt/

[^mise]: https://mise.jdx.dev/
