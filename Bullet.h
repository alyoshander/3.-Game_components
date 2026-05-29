#ifndef BULLET_H
#define BULLET_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include <string>

class Bullet : public IUpdatable, public IRenderable {
private:
    float x, y;
    float dx, dy;  // направление движения
    float lifeTime;  // сколько живёт (секунд)
    bool isActive;
    
public:
    Bullet(float startX, float startY, float dirX, float dirY);
    
    void update(float deltaTime) override;
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool getIsActive() const { return isActive; }
};

#endif