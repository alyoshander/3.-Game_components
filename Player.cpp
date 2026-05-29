#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(float startX, float startY) 
    : x(startX), y(startY), health(100.0f), speed(50.0f) {}

void Player::update(float deltaTime) {
    // В реальной игре здесь был бы ввод с клавиатуры
    // Для демонстрации: просто двигаемся по кругу
    
    static float angle = 0;
    angle += deltaTime * 1.0f;  // вращаемся со скоростью 1 рад/сек
    
    x = 10 + std::cos(angle) * 5;
    y = 10 + std::sin(angle) * 5;
}

void Player::render() const {
    std::cout << "👤 ";
    for (int i = 0; i < static_cast<int>(health / 10); i++) {
        std::cout << "█";
    }
    std::cout << " " << health << "%";
}

std::string Player::getRenderInfo() const {
    return "Player [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void Player::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
}