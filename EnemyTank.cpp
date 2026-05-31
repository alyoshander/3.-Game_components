#include "EnemyTank.h"
#include <cmath>
#include <iostream>

EnemyTank::EnemyTank(float startX, float startY, float tX, float tY)
    : x(startX), y(startY), health(60.0f), speed(6.0f), targetX(tX), targetY(tY) {}

void EnemyTank::update(float deltaTime) {
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

void EnemyTank::render() const {
    if (!isAlive()) {
        std::cout << "💀";
        return;
    }
    std::cout << "🐗";
}

std::string EnemyTank::getRenderInfo() const {
    if (!isAlive()) return "TankEnemy [DEAD]";
    return "TankEnemy [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void EnemyTank::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void EnemyTank::knockback(float fromX, float fromY, float force) {
    float dx = x - fromX;
    float dy = y - fromY;
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0.01f) {
        x += (dx / length) * force;
        y += (dy / length) * force;
    }
}