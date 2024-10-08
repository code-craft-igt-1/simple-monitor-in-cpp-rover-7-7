#include "./monitor.h"
#include <iostream>

Messages messages = {
    {"EN", {
        {"TEMP_CRITICAL", "Temperature is critical!"},
        {"TEMP_HYPER_WARNING", "Warning: Approaching hyperthermia"},
        {"TEMP_HYPO_WARNING", "Warning: Approaching hypothermia"},
        {"PULSE_CRITICAL", "Pulse Rate is out of range!"},
        {"PULSE_HIGH_WARNING", "Warning: Approaching high pulse rate"},
        {"PULSE_LOW_WARNING", "Warning: Approaching low pulse rate"},
        {"SPO2_CRITICAL", "Oxygen Saturation out of range!"},
        {"SPO2_LOW_WARNING", "Warning: Approaching low oxygen saturation"}
    }},

    {"DE", {
        {"TEMP_CRITICAL", "Temperatur ist kritisch!"},
        {"TEMP_HYPER_WARNING", "Warnung: Annäherung an Hyperthermie"},
        {"TEMP_HYPO_WARNING", "Warnung: Annäherung an Hypothermie"},
        {"PULSE_CRITICAL", "Pulsrate ist außerhalb des Bereichs!"},
        {"PULSE_HIGH_WARNING", "Warnung: Annäherung an hohe Pulsrate"},
        {"PULSE_LOW_WARNING", "Warnung: Annäherung an niedrige Pulsrate"},
        {"SPO2_CRITICAL", "Sauerstoffsättigung außerhalb des Bereichs!"},
        {"SPO2_LOW_WARNING", "Warnung: Annäherung an niedrige Sauerstoffsättigung"}
    }}
};

void displayAlert(const std::string& messageKey, const std::string& language,
const Messages& messages) {
    std::cout << messages.at(language).at(messageKey) << std::endl;
}

bool isTemperatureCritical(float temperature) {
    const float TEMP_UPPER_LIMIT = 102.0;
    const float TEMP_LOWER_LIMIT = 95.0;
    return temperature > TEMP_UPPER_LIMIT | temperature < TEMP_LOWER_LIMIT;
}

bool isUpperWarning(float temperature, float upperWarningLimit, float TEMP_UPPER_LIMIT) {
    return temperature >= upperWarningLimit && temperature < TEMP_UPPER_LIMIT;
}

bool isLowerWarning(float temperature, float lowerWarningLimit, float TEMP_LOWER_LIMIT) {
    return temperature > TEMP_LOWER_LIMIT && temperature <= lowerWarningLimit;
}

bool isTemperatureWarning(float temperature) {
    const float TEMP_UPPER_LIMIT = 102.0;
    const float TEMP_LOWER_LIMIT = 95.0;
    const float WARNING_TOLERANCE = 1.5 / 100.0;
    float upperWarningLimit = TEMP_UPPER_LIMIT - (TEMP_UPPER_LIMIT * WARNING_TOLERANCE);
    float lowerWarningLimit = TEMP_LOWER_LIMIT + (TEMP_LOWER_LIMIT * WARNING_TOLERANCE);
    return isUpperWarning(temperature, upperWarningLimit, TEMP_UPPER_LIMIT) ||
           isLowerWarning(temperature, lowerWarningLimit, TEMP_LOWER_LIMIT);
}

bool isTemperatureunder(float temperature, const std::string& language, const Messages& messages) {
    if (isTemperatureCritical(temperature)) {
        displayAlert("TEMP_CRITICAL", language, messages);
        return true;
    }
    return false;
}

bool isTemperatureover(float temperature, const std::string& language, const Messages& messages) {
    if (isTemperatureWarning(temperature)) {
        if (temperature >= 102.0 - (102.0 * 1.5 / 100.0)) {
            displayAlert("TEMP_HYPER_WARNING", language, messages);
        } else {
            displayAlert("TEMP_HYPO_WARNING", language, messages);
        }
        return true;
    }
    return false;
}

bool checkTemperature(float temperature, const std::string& language, const Messages& messages) {
    if (isTemperatureunder(temperature, language, messages)) {
        return false;
    } else if (isTemperatureover(temperature, language, messages)) {
        return false;
    }
    return true;
}

bool isPulseRateCritical(float pulseRate) {
    const float PULSE_UPPER_LIMIT = 100.0;
    const float PULSE_LOWER_LIMIT = 60.0;
    return pulseRate > PULSE_UPPER_LIMIT | pulseRate < PULSE_LOWER_LIMIT;
}

bool isPulseRateWarning(float pulseRate) {
    const float PULSE_UPPER_LIMIT = 100.0;
    const float PULSE_LOWER_LIMIT = 60.0;
    const float WARNING_TOLERANCE = 1.5 / 100.0;
    float upperWarningLimit = PULSE_UPPER_LIMIT - (PULSE_UPPER_LIMIT * WARNING_TOLERANCE);
    float lowerWarningLimit = PULSE_LOWER_LIMIT + (PULSE_LOWER_LIMIT * WARNING_TOLERANCE);
    return (pulseRate >= upperWarningLimit & pulseRate < PULSE_UPPER_LIMIT) |
           (pulseRate > PULSE_LOWER_LIMIT & pulseRate <= lowerWarningLimit);
}

bool isPulseRateHighWarning(float pulseRate) {
    return pulseRate >= 100.0 - (100.0 * 1.5 / 100.0);
}

bool isPulseRateLowWarning(float pulseRate) {
    return pulseRate < 100.0 - (100.0 * 1.5 / 100.0);
}

void handlePulseRateWarning(float pulseRate, const std::string& language,
const Messages& messages) {
    if (isPulseRateHighWarning(pulseRate)) {
        displayAlert("PULSE_HIGH_WARNING", language, messages);
    } else if (isPulseRateLowWarning(pulseRate)) {
        displayAlert("PULSE_LOW_WARNING", language, messages);
    }
}

bool checkPulseRate(float pulseRate, const std::string& language, const Messages& messages) {
    if (isPulseRateCritical(pulseRate)) {
        displayAlert("PULSE_CRITICAL", language, messages);
        return false;
    } else if (isPulseRateWarning(pulseRate)) {
        handlePulseRateWarning(pulseRate, language, messages);
    }
    return true;
}

bool isSpo2Critical(float spo2) {
    const float SPO2_LOWER_LIMIT = 90.0;
    return spo2 < SPO2_LOWER_LIMIT;
}

bool isSpo2Warning(float spo2) {
    const float SPO2_LOWER_LIMIT = 90.0;
    const float WARNING_TOLERANCE = 1.5 / 100.0;
    float lowerWarningLimit = SPO2_LOWER_LIMIT + (SPO2_LOWER_LIMIT * WARNING_TOLERANCE);
    return spo2 >= SPO2_LOWER_LIMIT & spo2 <= lowerWarningLimit;
}

bool checkSpo2(float spo2, const std::string& language, const Messages& messages) {
    if (isSpo2Critical(spo2)) {
        displayAlert("SPO2_CRITICAL", language, messages);
        return false;
    } else if (isSpo2Warning(spo2)) {
        displayAlert("SPO2_LOW_WARNING", language, messages);
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2,
const std::string& language, const Messages& messages) {
    return checkTemperature(temperature, language, messages) &
           checkPulseRate(pulseRate, language, messages) &
           checkSpo2(spo2, language, messages);
}

bool areVitalsOk(float temperature, float pulseRate, float spo2,
const std::string& language, const Messages& messages) {
    return vitalsOk(temperature, pulseRate, spo2, language, messages);
}
