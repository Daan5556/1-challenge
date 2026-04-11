#pragma once

#include <string>

std::string generatePayload(const std::string &edgeId, float humidity,
                            float temperature);
