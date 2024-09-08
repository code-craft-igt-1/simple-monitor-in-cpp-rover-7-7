#ifndef MONITOR_H_
#define MONITOR_H_

#include <unordered_map>
#include <string>

using Messages = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

extern Messages messages;

void displayAlert(const std::string& messageKey, const std::string&
language, const Messages& messages);
bool isUpperWarning(float temperature, float upperWarningLimit, float TEMP_UPPER_LIMIT);
bool isLowerWarning(float temperature, float lowerWarningLimit, float TEMP_LOWER_LIMIT);
bool isTemperatureunder(float temperature, const std::string& language,
const Messages& messages);
bool isTemperatureover(float temperature, const std::string& language,
const Messages& messages);
bool isTemperatureCritical(float temperature);
bool isTemperatureWarning(float temperature);
bool checkTemperature(float temperature, const std::string& language,
const Messages& messages);
void displayTemperatureWarning(float temperature, const std::string& language,
const Messages& messages);
bool isPulseRateHighWarning(float pulseRate);
bool isPulseRateLowWarning(float pulseRate);
bool isPulseRateCritical(float pulseRate);
void displayPulseRateWarning(float pulseRate, const std::string& language,
const Messages& messages);
void handlePulseRateWarning(float pulseRate, const std::string& language, const Messages& messages);
bool isPulseRateWarning(float pulseRate);
bool checkPulseRate(float pulseRate, const std::string& language,
const Messages& messages);
bool isSpo2Critical(float spo2);
bool isSpo2Warning(float spo2);
bool checkSpo2(float spo2, const std::string& language,
const Messages& messages);
int vitalsOk(float temperature, float pulseRate,
float spo2, const std::string& language, const Messages& messages);
bool areVitalsOk(float temperature, float pulseRate,
float spo2, const std::string& language, const Messages& messages);

#endif  // MONITOR_H_
