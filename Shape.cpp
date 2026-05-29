#include "Shape.h"
#include <iostream>

void Shape::printInfo() const {
    std::cout << "Фигура: " << getName() << "\n";
    std::cout << "Площадь: " << getArea() << "\n";
    std::cout << "Периметр: " << getPerimeter() << "\n";
}