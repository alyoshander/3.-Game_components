#include "Enemy.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(float startX, float startY, float tX, float tY)
    : x(startX), y(startY), health(30.0f), speed(12.0f), targetX(tX), targetY(tY) {}

void Enemy::update(float deltaTime) {
    if (!isAlive()) return;
    
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = std::sqrt(dx*dx + dy*dy);
    
    if (distance > 0.5f) {
        float move = speed * deltaTime;
        if (move > distance) move = distance;
        x += (dx / distance) * move;
        y += (dy / distance) * move;
    }
}

void Enemy::render() const {
    if (!isAlive()) {
        std::cout << "💀 DEAD";
        return;
    }
    
    std::cout << "👾 HP: ";
    int hpBars = static_cast<int>(health / 10);
    for (int i = 0; i < hpBars; i++) std::cout << "#";
    for (int i = hpBars; i < 3; i++) std::cout << "-";
}

std::string Enemy::getRenderInfo() const {
    if (!isAlive()) return "Enemy [DEAD]";
    return "Enemy [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void Enemy::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << "\n⚔️ Враг получил " << damage << " урона!\n";
}

void Enemy::knockback(float fromX, float fromY, float force) {
    float dx = x - fromX;
    float dy = y - fromY;
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0.01f) {
        x += (dx / length) * force;
        y += (dy / length) * force;
    }
}