#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float startX, float startY, float dirX, float dirY)
    : x(startX), y(startY), dx(dirX), dy(dirY), lifeTime(3.0f), isActive(true) {}  // было 2.0f

void Bullet::update(float deltaTime) {
    if (!isActive) return;
    
    lifeTime -= deltaTime;
    if (lifeTime <= 0) {
        isActive = false;
        return;
    }
    
    float speed = 120.0f;
    x += dx * speed * deltaTime;
    y += dy * speed * deltaTime;
}

void Bullet::render() const {
    if (isActive) {
        std::cout << "● ";
    } else {
        std::cout << "  ";
    }
}

std::string Bullet::getRenderInfo() const {
    if (!isActive) return "Bullet [inactive]";
    return "Bullet [x=" + std::to_string(x) + ", y=" + std::to_string(y) + "]";
}