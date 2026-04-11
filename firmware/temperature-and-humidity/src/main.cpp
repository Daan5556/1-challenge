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

const long interval = 5000;
unsigned long previousMillis = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  while (WiFi.begin(ssid, passPrase) != WL_CONNECTED) {
    delay(5000);
  }

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

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis < interval) {
    return;
  }

  previousMillis = currentMillis;

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  auto payload = generatePayload(ED_ID, h, t);

  mqttClient.beginMessage(mqttTopic);
  mqttClient.print(payload.c_str());
  mqttClient.endMessage();
}