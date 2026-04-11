#include <cstdio>
#include <string>

#include "config.h"
#include "payload.h"

std::string generatePayload(const std::string &edgeId, float humidity,
                            float temperature) {

  return "temperature_and_humidity,edge_device_id=" + edgeId + " " +
         "humidity=" + std::to_string(humidity) +
         ","
         "temperature=" +
         std::to_string(temperature);
}
