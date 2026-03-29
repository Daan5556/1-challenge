# InfluxDB

## Telegraf

Open source agent for collecting data. With loads of plugins.

On startup, loads inputs + outputs.

### MQTT plugin (Input)

[docs](https://github.com/influxdata/telegraf/tree/master/plugins/inputs/mqtt_consumer)

Plugins are loaded via the `telegraf.conf` file.

```conf
[[inputs.mqtt_consumer]]
servers = ["tcp://mosquitto:1883"]

topics = [
  "/sensors/#"
]

[[outputs.file]]
```

InfluxDB uses line protocol, so it makes sense for the MQTT nodes to also
publish using that.

```
  mosquitto_pub -h localhost -t '/sensors' -m 'vehicle_camera,edge_device_id=ED-1001-01 value=23'
```

This setup will output the transformed data to STDOUT. If you omit the
timestamp, Telegraf will add it, same as the hostname.

### InfluxDB plugin (Output)

[docs](https://github.com/influxdata/telegraf/tree/master/plugins/outputs/influxdb_v3)

With a simple config we can add InfluxDB as output in Telegraf.

```conf
[[outputs.influxdb_v3]]
  urls = ["http://influxdb3-core:8181"]

  token = "apiv3_..."
  database = "mydb"
```

Telegraf will use HTTP to insert the data in InfluxDB.
