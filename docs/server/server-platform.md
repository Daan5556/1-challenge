# Server platform

**Author:** Daan Eggen  
**Date:** 28/03/2026  
**Version:** 1.0

---

In this document I'm going to describe the design of the server platform. In the
previous "Server Architecture" document, I already decided on a self hosted,
InfluxDB software stack. Here, I will dive into the

## Deployment strategy

The server platform needs several different services that should be running
simultaneously on a single host. I think the project can benefit from
containerized deployment for several reasons.

- "Configuration as code" can be employed for consistency.
- Services are isolated for better security.
- Dependencies are pinned.

The downside of containerization is that it adds complexity. This makes
debugging harder. But overall, I containerization makes a lot of sense for this
project.

## Database [^influxdb]

The database that is going to be used is `InfluxDB`. This is a purpose built,
time series database. This means that the database is optimized for real-time
ingest and querying, perfect for my situation! In the container setup, I will
port binding so it can be reached from the host machine, and a volume binding
for data persistence. I will use a named volume instead of a directory binding
so that the Docker daemon will manage the volume, this ensures the file
permissions are always correct.

```yaml
influxdb3-core:
  container_name: influxdb3
  image: influxdb:3-core
  ports:
    - 8181:8181
  command:
    - influxdb3
    - serve
    - --node-id=smart-springfield
    - --object-store=file
    - --data-dir=/var/lib/influxdb3/data
    - --plugin-dir=/var/lib/influxdb3/plugins
  volumes:
    - influxdb3:/var/lib/influxdb3
```

The database will have a table for every sensor type. It will have an index for
every gateway device for fast querying.

Next, I'm going to describe how data will be inserted in to the tables.

## Data ingestion

The edge devices will be publishes messages to the MQTT broker. In the following
section, I'll go over the structure of these messages, and the MQTT topics they
will be published to.

### MQTT schema

The message format of the InfluxData platform is commonly
[line protocol](https://docs.influxdata.com/influxdb3/core/reference/line-protocol/).
It is lightweight and human readable. And its fully supported by InfluxData
services. A line protocol message contains a table, optional tags, fields (the
actual measurements) and an optional timestamp. Every sensor type will have its
own table, so an edge device that is connected to a vehicle camera sensor will
use `vehicle_camera` as table in its messages. For tags, it will set the edge
device id. And for fields, it will put the measurements. Timestamp will not be
handled by the edge device, so I will omit it here. So, if I put it all
together, I get a message like this:

```plaintext
vehicle_camera,edge_device_id=ED-1001-01 value=64,count=4
```

All of the sensor data will be published to the top level `sensors` MQTT topic,
followed by the gateway id separated by a `/`. So this particular message will
get published to:

```plaintext
sensors/ED-1001-01
```

### Data collection agent

The broker will only retain and forward the messages to other clients. It will
not communicate to the database itself. That's why I need a small service that
collects and stores the data. I don't have to look far because there is already
such a service in the InfluxData stack: Telegraf[^telegraf]. This data
collection agent has a lot of input and output plugins. Inputs can be things
like files or network. Output can be databases or just the STDOUT.

For input, I will use the `mqtt_consumer` plugin. This plugin will subscribe to
topics defined in your configuration file. So in this case, I let it subscribe
to the `sensors` topic.

For output, I will use the `Influxdb_v3` plugin. This plugin will connect to a
database instance, and insert every data point in the data pipeline.

I can configure these 2 plugins in the configuration file like so:

```conf
[[inputs.mqtt_consumer]]
servers = ["tcp://mosquitto:1883"]

topics = [
  "sensors/#"
]

[[outputs.influxdb_v3]]
  urls = ["http://influxdb3-core:8181"]

  ## Token for authentication
  token = "${TOKEN}"

  ## Destination database to write into
  database = "sensors"
```

As you can see, the configuration file defines the broker URL and the topic to
subscribe to. I used a wild card topic so I get everything that's published
under `sensors`. For the output, I defined the database URL, the database name
and authentication.

The configuration is all I need. This service can operate stateless so I don't
need a volume, which is nice.

## Data management

For data administration, I could just use the CLI. I can inspect and modify the
database with the `influxdb` CLI. However, I don't consider this save, because
in order to do this, you have to have direct access to the container. If you
give people access like this, its hard to prevent dangerous, irreversible
actions. There also isn't any logging of the access that's being obtained. It
much better to grant (indirect) access via a web UI. This way, you can apply
more fine grained permissions, like giving certain roles only read access. This
also has to bonus that it more user friendly to use than a command line.

The InfluxData stack provides a application for this specific use case. Its
appropriately named `influxdb-explorer`. It will simply make a connection to the
database and will offer you to inspect databases and tables. It also offers
administration features like managing tokens.

The connection to the database is made server-sided, so you can have separate
credentials for you database instance and your database manager.

## Data visualization

This service in the platform is responsible to display the data in a nice
presentable way. It will connect directly to the database and you can save
custom queries to specific data visualization cells. You can save multiple
different dashboards.

![dashboard](../assets/chronograf.png)

```plaintext
server
├── compose.mqtt.yaml
├── compose.yaml
├── mise.toml
├── scripts
│   └── publish-message.sh
└── telegraf.conf
```

[^influxdb]: https://docs.influxdata.com/influxdb3/core/

[^telegraf]: https://github.com/influxdata/telegraf
