#include "Triangle.h"
#include <cmath>

Triangle::Triangle(double a, double b, double c) 
    : side1(a), side2(b), side3(c) {}

double Triangle::getPerimeter() const {
    return side1 + side2 + side3;
}

double Triangle::getArea() const {
    double p = getPerimeter() / 2;
    return std::sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

std::string Triangle::getName() const {
    return "Треугольник";
}