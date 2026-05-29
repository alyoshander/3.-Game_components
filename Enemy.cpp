#include "Enemy.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(float startX, float startY, float tX, float tY)
    : x(startX), y(startY), health(30.0f), speed(20.0f), targetX(tX), targetY(tY) {}

void Enemy::update(float deltaTime) {
    // Движение к цели
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = std::sqrt(dx*dx + dy*dy);
    
    if (distance > 0.1f) {
        float move = speed * deltaTime;
        if (move > distance) move = distance;
        x += (dx / distance) * move;
        y += (dy / distance) * move;
    }
}

void Enemy::render() const {
    std::cout << "👾 ";
    int hpBars = static_cast<int>(health / 10);
    for (int i = 0; i < hpBars; i++) {
        std::cout << "█";
    }
    for (int i = hpBars; i < 3; i++) {
        std::cout << "░";
    }
}

std::string Enemy::getRenderInfo() const {
    return "Enemy [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void Enemy::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
}