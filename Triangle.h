#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
private:
    double side1, side2, side3;
    
public:
    Triangle(double a, double b, double c);
    
    double getArea() const override;      // По формуле Герона
    double getPerimeter() const override;
    std::string getName() const override;
};

#endif