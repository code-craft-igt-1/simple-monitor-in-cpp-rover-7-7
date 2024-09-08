#ifndef MONITOR_H_
#define MONITOR_H_

#include <unordered_map>
#include <string>

using Messages = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

extern Messages messages;

int vitalsOk(float temperature, float pulseRate, float spo2,
const std::string& language, const Messages& messages);
bool checkTemperature(float temperature, const std::string& language,
const Messages& messages);
bool checkPulseRate(float pulseRate, const std::string& language,
const Messages& messages);
bool checkSpo2(float spo2, const std::string& language, const Messages& messages);
void displayAlert(const std::string& messageKey, const std::string& language,
const Messages& messages);
bool areVitalsOk(float temperature, float pulseRate, float spo2,
const std::string& language, const Messages& messages);

#endif  // MONITOR_H_
