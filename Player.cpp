#include "Player.h"
#include "Bullet.h"
#include "InputHandler.h"
#include <iostream>

Player::Player(float startX, float startY) 
    : x(startX), y(startY), health(100.0f), speed(55.0f),  // было 40
      attackCooldown(0.0f), attackCooldownMax(0.3f) {}

void Player::update(float deltaTime) {
    // Уменьшаем кулдаун
    if (attackCooldown > 0) {
        attackCooldown -= deltaTime;
    }
    
    // Чтение клавиш
    char key = InputHandler::getKey();
    
    switch(key) {
        case 'w': case 'W': y -= speed * deltaTime; break;
        case 's': case 'S': y += speed * deltaTime; break;
        case 'a': case 'A': x -= speed * deltaTime; break;
        case 'd': case 'D': x += speed * deltaTime; break;
        case ' ':  // Пробел для стрельбы
            if (attackCooldown <= 0) {
                attackCooldown = attackCooldownMax;
            }
            break;
        case 'q': case 'Q':  // Выход
            health = 0;
            break;
    }
    
    // Ограничиваем движение по карте
    if (x < 0) x = 0;
    if (x >= 20) x = 19.9f;
    if (y < 0) y = 0;
    if (y >= 20) y = 19.9f;
}

void Player::render() const {
    std::cout << "❤️ HP: ";
    int hpBars = static_cast<int>(health / 10);
    for (int i = 0; i < hpBars; i++) std::cout << "#";
    for (int i = hpBars; i < 10; i++) std::cout << "-";
    std::cout << " " << health << "%";
}

std::string Player::getRenderInfo() const {
    return "Player [x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", hp=" + std::to_string(health) + "]";
}

void Player::setHealth(float h) {
    health = h;
    if (health > 100) health = 100;
}

float Player::getHealth() const {
    return health;
}

void Player::takeDamage(float damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Player::canShoot() const {
    return attackCooldown <= 0;
}

void Player::resetShootCooldown() {
    attackCooldown = attackCooldownMax;
}

std::pair<float, float> Player::getShootDirection() const {
    // Стреляем в направлении движения мыши? Упростим: 
    // По умолчанию вверх-вправо, но можно расширить
    return {0.7f, 0.7f};
}