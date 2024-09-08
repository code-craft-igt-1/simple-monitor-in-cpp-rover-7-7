#include <unordered_map>
#include <string>
#include "gtest/gtest.h"
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
    ASSERT_FALSE(areVitalsOk(99, 102, 70, "EN", messages));
    ASSERT_TRUE(areVitalsOk(98.1, 70, 98, "EN", messages));
}

TEST(Monitor, OkWhenAllVitalsAreInRange) {
    ASSERT_TRUE(areVitalsOk(100, 99, 91, "EN", messages));
    ASSERT_TRUE(areVitalsOk(98.6, 90, 95, "EN", messages));
    ASSERT_TRUE(areVitalsOk(97.5, 80, 100, "EN", messages));
}

TEST(Monitor, NotOkWhenTemperatureIsOutOfRange) {
    ASSERT_FALSE(areVitalsOk(95, 100, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(105, 100, 80, "EN", messages));
}

TEST(Monitor, NotOkWhenPulseRateIsOutOfRange) {
    ASSERT_FALSE(areVitalsOk(100, 60, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(100, 120, 80, "EN", messages));
}

TEST(Monitor, NotOkWhenBloodPressureIsOutOfRange) {
    ASSERT_FALSE(areVitalsOk(100, 100, 60, "EN", messages));
    ASSERT_FALSE(areVitalsOk(100, 100, 55, "EN", messages));
}

TEST(Monitor, NotOkWhenHeartRateIsBelowRange) {
    ASSERT_FALSE(areVitalsOk(95, 100, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(97.5, 101, 95, "EN", messages));
}

TEST(Monitor, NotOkWhenHeartRateIsAboveRange) {
    ASSERT_FALSE(areVitalsOk(105, 100, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(102.5, 90, 95, "EN", messages));
}

TEST(Monitor, NotOkWhenOxygenLevelIsBelowRange) {
    ASSERT_FALSE(areVitalsOk(100, 95, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(98.6, 85, 89, "EN", messages));
}

TEST(Monitor, NotOkWhenOxygenLevelIsAboveRange) {
    ASSERT_FALSE(areVitalsOk(100, 105, 80, "EN", messages));
    ASSERT_FALSE(areVitalsOk(98.6, 100, 69, "EN", messages));
}

TEST(Monitor, NotOkWhenTemperatureIsBelowRange) {
    ASSERT_FALSE(areVitalsOk(100, 100, 75, "EN", messages));
    ASSERT_FALSE(areVitalsOk(92.8, 90, 97.5, "EN", messages));
}

TEST(Monitor, NotOkWhenTemperatureIsAboveRange) {
    ASSERT_FALSE(areVitalsOk(100, 100, 85, "EN", messages));
    ASSERT_FALSE(areVitalsOk(103, 90, 100, "EN", messages));
}
