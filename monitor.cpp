#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>


using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

void displayAlert(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool checkTemperature(float temperature) {
    if (temperature > 102 || temperature < 95) {
        displayAlert("Temperature is critical!");
        return false;
    }
    return true;
}

bool checkPulseRate(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        displayAlert("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

bool checkSpo2(float spo2) {
    if (spo2 < 90) {
        displayAlert("Oxygen Saturation out of range!");
        return false;
    }
    return true;
}

bool areVitalsOk(float temperature, float pulseRate, float spo2) {
    return checkTemperature(temperature) && checkPulseRate(pulseRate) && checkSpo2(spo2);
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    return areVitalsOk(temperature, pulseRate, spo2) ? 1 : 0;
}
