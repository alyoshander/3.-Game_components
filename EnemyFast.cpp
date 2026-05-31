#include "EnemyFast.h"
#include "Player.h"
#include <cmath>
#include <iostream>

EnemyFast::EnemyFast(float startX, float startY, float tX, float tY)
    : x(startX), y(startY), health(15.0f), speed(20.0f), targetX(tX), targetY(tY) {}

void EnemyFast::update(float deltaTime) {
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

void EnemyFast::render() const {
    if (!isAlive()) {
        std::cout << "💀";
        return;
    }
    std::cout << "⚡";
}

std::string EnemyFast::getRenderInfo() const {
    if (!isAlive()) return "FastEnemy [DEAD]";
    return "FastEnemy [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void EnemyFast::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void EnemyFast::onCollisionWithPlayer(Player* player) {
    player->takeDamage(20.0f);  // Быстрый враг наносит больше урона
}

void EnemyFast::knockback(float fromX, float fromY, float force) {
    float dx = x - fromX;
    float dy = y - fromY;
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0.01f) {
        x += (dx / length) * force;
        y += (dy / length) * force;
    }
}