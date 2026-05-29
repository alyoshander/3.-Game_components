#include "Circle.h"
#include <cmath>

const double PI = 3.14159265358979323846;

Circle::Circle(double r) : radius(r) {}

double Circle::getArea() const {
    return PI * radius * radius;
}

double Circle::getPerimeter() const {
    return 2 * PI * radius;
}

std::string Circle::getName() const {
    return "Круг";
}