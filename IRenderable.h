#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include <string>

// Интерфейс для всех объектов, которые нужно рисовать
class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual void render() const = 0;
    virtual std::string getRenderInfo() const = 0;  // что показывать в консоли
};

#endif