#! /usr/bin/env python

import sys
import yaml
import csv


def get_sensor_by_id(sensors, id):
    return sensors[id]["type"]


def main():
    with open("config.yaml") as f:
        config = yaml.safe_load(f)
        sensors = config["sensors"]

    intersections = config["intersections"]

    writer = csv.writer(sys.stdout)
    writer.writerow(["Intersection", "EdgeGatewayId", "EdgeDeviceId", "SensorType"])

    edge_gateway_id = 1001
    for intersection, intersection_value in intersections.items():
        edge_device_id = 1
        for sensor_id in intersection_value["sensors"]:
            sensor = get_sensor_by_id(sensors, sensor_id)
            writer.writerow(
                [
                    intersection,
                    f"GW-{edge_gateway_id}",
                    f"ED-{edge_gateway_id}-{edge_device_id:02}",
                    sensor,
                ]
            )
            edge_device_id += 1
        edge_gateway_id += 1


if __name__ == "__main__":
    main()
