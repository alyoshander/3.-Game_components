#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape {
public:
    virtual ~Shape() = default;  // Виртуальный деструктор — важно!
    
    // Чисто виртуальные методы (обязательны для наследников)
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual std::string getName() const = 0;
    
    // Обычный виртуальный метод (можно переопределить, но не обязательно)
    virtual void printInfo() const;
};

#endif