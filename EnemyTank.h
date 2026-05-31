#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "IUpdatable.h"
#include "IRenderable.h"

class EnemyTank : public IUpdatable, public IRenderable {
private:
    float x, y;
    float health;
    float speed;
    float targetX, targetY;
    
public:
    EnemyTank(float startX, float startY, float targetX, float targetY);
    
    void update(float deltaTime) override;
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return health > 0; }
    void takeDamage(float damage);
    
    void knockback(float fromX, float fromY, float force = 2.0f);
};

#endif