#include <Adafruit_Sensor.h>
#include <ArduinoMqttClient.h>
#include <DHT.h>
#include <WiFi.h>

#include "config.h"
#include "payload.h"

#define DHTPIN 4
#define DHTTYPE DHT11

char ssid[] = SSID;
char passPrase[] = PASS_PRASE;

char mqttHost[] = MQTT_HOST;
char mqttTopic[] = "sensors/" ED_ID;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  while (WiFi.begin(ssid, passPrase) != WL_CONNECTED)
    delay(5000);

  Serial.print(F("Connected to WiFi with IP: "));
  Serial.println(WiFi.localIP());

  if (!mqttClient.connect(mqttHost)) {
    Serial.print("MQTT connection failed! Error code:");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("Connected to the MQTT broker");

  dht.begin();
}

void loop() {
  mqttClient.poll();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  auto payload = generatePayload(ED_ID, h, t);

  Serial.println(payload.c_str());
}