#ifndef ENEMY_H
#define ENEMY_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include <string>

class Enemy : public IUpdatable, public IRenderable {
private:
    float x, y;
    float health;
    float speed;
    float targetX, targetY;  // куда двигаться
    
public:
    Enemy(float startX, float startY, float targetX, float targetY);
    
    void update(float deltaTime) override;
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return health > 0; }
    void takeDamage(float damage);
};

#endif