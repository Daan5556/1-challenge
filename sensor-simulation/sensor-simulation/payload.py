import random


def get_tablename(sensortype) -> str:
    sensortype = int(sensortype)
    match sensortype:
        case 1:
            return "traffic_camera"
        case 2:
            return "air_quality"
        case 3:
            return "noise"
        case 4:
            return "temperature_and_humidity"
        case 5:
            return "parking_sensor"
        case 6:
            return "water_quality"
        case 7:
            return "seismic_sensor"
        case _:
            raise ValueError("Unknown sensortype")


def generate(sensortype) -> str:
    sensortype = int(sensortype)
    match sensortype:
        case 1:
            return _generate_traffic_camera()
        case 2:
            return _generate_air_quality()
        case 3:
            return _generate_noise()
        case 4:
            return _generate_temperature_and_humidity()
        case 5:
            return _generate_parking_sensor()
        case 6:
            return _generate_water_quality()
        case 7:
            return _generate_seismic()
        case _:
            raise ValueError("Unknown sensortype")


def _generate_traffic_camera():
    mean = 50
    std_dev = 10
    measurement = int(random.gauss(mean, std_dev))

    return f"value={measurement}"


def _generate_air_quality():
    return f"value={1}"


def _generate_noise():
    mean = 60
    std_dev = 15
    measurement = int(random.gauss(mean, std_dev))

    return f"value={measurement}"


def _generate_temperature_and_humidity():
    return f"value={1}"


def _generate_parking_sensor():
    mean = 300
    std_dev = 100
    measurement = int(random.gauss(mean, std_dev))

    return f"value={measurement}"


def _generate_water_quality():
    temperature = round(random.gauss(22, 6), 2)
    ph = round(random.gauss(7, 2), 2)
    turbidity = round(random.gauss(22, 6), 1)
    dissolved_oxygen = round(random.gauss(8, 1.5), 1)
    electrical_conductivity = int(random.gauss(412, 50))

    return f"temperature={temperature},ph={ph},turbidity={turbidity},dissolved_oxygen={dissolved_oxygen},electrical_conductivity={electrical_conductivity}"


def _generate_seismic():
    mean = 0.02
    std_dev = 0.01
    measurement = max(0, random.gauss(mean, std_dev))

    return f"value={measurement}"
