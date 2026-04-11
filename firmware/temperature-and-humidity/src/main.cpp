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

char mqttBroker[] = MQTT_HOST;
char mqttTopic[] = "sensors/" ED_ID;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  auto payload = generatePayload(ED_ID, h, t);

  Serial.println(payload.c_str());
}