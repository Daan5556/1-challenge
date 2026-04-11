#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "config.h"
#include "payload.h"

#define DHTPIN 4
#define DHTTYPE DHT11

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