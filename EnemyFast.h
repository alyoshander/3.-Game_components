#ifndef ENEMYFAST_H
#define ENEMYFAST_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include "Player.h"

class EnemyFast : public IUpdatable, public IRenderable {
private:
    float x, y;
    float health;
    float speed;
    float targetX, targetY;
    
public:
    EnemyFast(float startX, float startY, float targetX, float targetY);
    
    void update(float deltaTime) override;
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return health > 0; }
    void takeDamage(float damage);
    void onCollisionWithPlayer(Player* player);
    
    void knockback(float fromX, float fromY, float force = 2.0f);
};

#endif