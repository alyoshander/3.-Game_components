#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include "IRenderable.h"
#include <string>

class HealthPack : public IRenderable {
private:
    float x, y;
    bool isActive;
    float healAmount;
    
public:
    HealthPack(float startX, float startY, float heal = 25.0f);
    
    void render() const override;
    std::string getRenderInfo() const override;
    
    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return isActive; }
    void collect();
    float getHealAmount() const { return healAmount; }
};

#endif