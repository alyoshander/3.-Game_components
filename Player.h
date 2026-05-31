#ifndef PLAYER_H
#define PLAYER_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include <string>
#include <utility>

class Player : public IUpdatable, public IRenderable {
private:
    float x, y;
    float health;
    float speed;
    float attackCooldown;
    float attackCooldownMax;
    
public:
    Player(float startX, float startY);
    
    void update(float deltaTime) override;
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return health > 0; }
    
    float getHealth() const;
    void setHealth(float h);
    
    void takeDamage(float damage);
    bool canShoot() const;
    void resetShootCooldown();
    std::pair<float, float> getShootDirection() const;
};

#endif