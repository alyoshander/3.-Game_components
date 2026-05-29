#ifndef IUPDATABLE_H
#define IUPDATABLE_H

// Интерфейс для всех объектов, которые нужно обновлять каждый кадр
class IUpdatable {
public:
    virtual ~IUpdatable() = default;
    virtual void update(float deltaTime) = 0;  // deltaTime = время с прошлого кадра
};

#endif