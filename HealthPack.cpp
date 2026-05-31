#include "HealthPack.h"
#include <iostream>

HealthPack::HealthPack(float startX, float startY, float heal)
    : x(startX), y(startY), isActive(true), healAmount(heal) {}

void HealthPack::render() const {
    if (isActive) {
        std::cout << "💊";
    }
}

std::string HealthPack::getRenderInfo() const {
    if (!isActive) return "HealthPack [used]";
    return "HealthPack [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", heal=" + std::to_string(healAmount) + "]";
}

void HealthPack::collect() {
    isActive = false;
}