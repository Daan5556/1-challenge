#! /usr/bin/env python

import os
import time

import paho.mqtt.client as mqtt
import payload

MQTT_HOST = os.environ["MQTT_HOST"]
EDGE_DEVICE_IDENTIFIER = os.environ["EDGE_DEVICE_ID"]
SENSOR_TYPE = os.environ["SENSOR_TYPE"]
TABLE_NAME = payload.get_tablename(SENSOR_TYPE)

MQTT_TOPIC = f"sensors/{EDGE_DEVICE_IDENTIFIER}"


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


if __name__ == "__main__":
    main()
