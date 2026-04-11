#include <cstdio>
#include <string>
#include <unity.h>

#include "payload.h"

void test_generate_payload_formats_sensor_values() {
  const std::string payload = generatePayload("device-id", 45.2f, 21.8f);

  TEST_ASSERT_EQUAL_STRING("temperature_and_humidity,edge_device_id=device-id "
                           "humidity=45.200001,temperature=21.799999",
                           payload.c_str());
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_generate_payload_formats_sensor_values);
  return UNITY_END();
}
