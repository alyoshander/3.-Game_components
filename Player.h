#ifndef PLAYER_H
#define PLAYER_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include <string>

class Player : public IUpdatable, public IRenderable {
private:
    float x, y;           // позиция
    float health;
    float speed;
    
public:
    Player(float startX, float startY);
    
    // IUpdatable
    void update(float deltaTime) override;
    
    // IRenderable
    void render() const override;
    std::string getRenderInfo() const override;
    
    // Геттеры для пуль и врагов
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return health > 0; }
    
    void takeDamage(float damage);
};

#endif