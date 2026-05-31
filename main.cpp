#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFast.h"
#include "EnemyTank.h"
#include "HealthPack.h"
#include "Bullet.h"
#include "InputHandler.h"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

int score = 0;  // Глобальный счёт (потом можно вынести в отдельный класс)

void drawMap(Player* player, std::vector<Enemy*>& enemies, 
             std::vector<EnemyFast*>& fastEnemies, 
             std::vector<EnemyTank*>& tankEnemies,
             std::vector<Bullet*>& bullets,
             std::vector<HealthPack*>& healthPacks) {
    
    std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
    
    // Быстрые враги
    for (auto* e : fastEnemies) {
        if (e->isAlive()) {
            int mx = static_cast<int>(e->getX());
            int my = static_cast<int>(e->getY());
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) map[my][mx] = 'F';
        }
    }
    
    // Танки
    for (auto* e : tankEnemies) {
        if (e->isAlive()) {
            int mx = static_cast<int>(e->getX());
            int my = static_cast<int>(e->getY());
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) map[my][mx] = 'T';
        }
    }
    
    // Обычные враги
    for (auto* e : enemies) {
        if (e->isAlive()) {
            int mx = static_cast<int>(e->getX());
            int my = static_cast<int>(e->getY());
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) map[my][mx] = 'E';
        }
    }
    
    // Аптечки
    for (auto* hp : healthPacks) {
        if (hp->isAlive()) {
            int mx = static_cast<int>(hp->getX());
            int my = static_cast<int>(hp->getY());
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) map[my][mx] = '+';
        }
    }
    
    // Пули
    for (auto* bullet : bullets) {
        if (bullet->getIsActive()) {
            int mx = static_cast<int>(bullet->getX());
            int my = static_cast<int>(bullet->getY());
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) map[my][mx] = '*';
        }
    }
    
    // Игрок
    int px = static_cast<int>(player->getX());
    int py = static_cast<int>(player->getY());
    if (px >= 0 && px < MAP_WIDTH && py >= 0 && py < MAP_HEIGHT) map[py][px] = 'P';
    
    std::cout << "=== ОТЛАДКА ===\n";
    std::cout << "Игрок создан. Здоровье: " << player->getHealth() << "\n";
    std::cout << "Врагов (обычных): " << enemies.size() << "\n";
    std::cout << "Быстрых врагов: " << fastEnemies.size() << "\n";
    std::cout << "Врагов-танков: " << tankEnemies.size() << "\n";
    std::cout << "Аптечек: " << healthPacks.size() << "\n";
    std::cout << "=== НАЧАЛО ИГРЫ ===\n";

    // Вывод карты
    std::cout << "\n  ";
    for (int x = 0; x < MAP_WIDTH; x++) std::cout << (x % 10);
    std::cout << "\n";
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        std::cout << (y % 10) << " ";
        for (int x = 0; x < MAP_WIDTH; x++) std::cout << map[y][x];
        std::cout << "\n";
    }
}

int main() {
    Player* player = new Player(10, 10);
    std::vector<Enemy*> enemies;
    std::vector<EnemyFast*> fastEnemies;
    std::vector<EnemyTank*> tankEnemies;
    std::vector<Bullet*> bullets;
    std::vector<HealthPack*> healthPacks;
    
    // Создаём врагов разных типов
    enemies.push_back(new Enemy(3, 3, 10, 10));
    enemies.push_back(new Enemy(17, 3, 10, 10));
    fastEnemies.push_back(new EnemyFast(3, 17, 10, 10));
    fastEnemies.push_back(new EnemyFast(17, 17, 10, 10));
    tankEnemies.push_back(new EnemyTank(10, 1, 10, 10));
    
    // Аптечки на карте
    healthPacks.push_back(new HealthPack(5, 5, 25.0f));
    healthPacks.push_back(new HealthPack(15, 5, 25.0f));
    healthPacks.push_back(new HealthPack(5, 15, 25.0f));
    healthPacks.push_back(new HealthPack(15, 15, 25.0f));
    
    // Игровой цикл
    auto lastTime = std::chrono::steady_clock::now();
    float gameTime = 0;
    float shootCooldown = 0;
    
    std::cout << "\n=== БИТВА АРЕНА ===\n";
    std::cout << "Управление: WASD - движение, Пробел - стрельба, Q - выход\n";
    std::cout << "Враги: E(обычный), F(быстрый ⚡), T(танк 🐗)\n";
    std::cout << "Аптечки: + восстанавливают 25 HP\n\n";
    
    while (player->isAlive() && 
           (!enemies.empty() || !fastEnemies.empty() || !tankEnemies.empty())) {
        
        auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;
        if (deltaTime > 0.1f) deltaTime = 0.1f;
        
        gameTime += deltaTime;
        
        // Обновление
        player->update(deltaTime);
        for (auto* e : enemies) e->update(deltaTime);
        for (auto* e : fastEnemies) e->update(deltaTime);
        for (auto* e : tankEnemies) e->update(deltaTime);
        for (auto* b : bullets) b->update(deltaTime);
        
        // Стрельба по пробелу
        shootCooldown -= deltaTime;
        if (player->canShoot()) {
            char key = InputHandler::getKey();
            if (key == ' ') {
                auto dir = player->getShootDirection();
                Bullet* bullet = new Bullet(player->getX(), player->getY(), dir.first, dir.second);
                bullets.push_back(bullet);
                player->resetShootCooldown();
            }
        }
        
        // СТОЛКНОВЕНИЯ: пули vs враги
        for (auto* bullet : bullets) {
            if (!bullet->getIsActive()) continue;
            
            // Обычные враги
            for (auto* enemy : enemies) {
                if (!enemy->isAlive()) continue;
                float dx = bullet->getX() - enemy->getX();
                float dy = bullet->getY() - enemy->getY();
                if (std::sqrt(dx*dx + dy*dy) < 1.0f) {
                    enemy->takeDamage(15.0f);
                    bullet->~Bullet();
                    if (!enemy->isAlive()) score += 10;
                    break;
                }
            }
            
            // Быстрые враги
            for (auto* enemy : fastEnemies) {
                if (!enemy->isAlive()) continue;
                float dx = bullet->getX() - enemy->getX();
                float dy = bullet->getY() - enemy->getY();
                if (std::sqrt(dx*dx + dy*dy) < 1.0f) {
                    enemy->takeDamage(15.0f);
                    bullet->~Bullet();
                    if (!enemy->isAlive()) score += 20;
                    break;
                }
            }
            
            // Враги-танки
            for (auto* enemy : tankEnemies) {
                if (!enemy->isAlive()) continue;
                float dx = bullet->getX() - enemy->getX();
                float dy = bullet->getY() - enemy->getY();
                if (std::sqrt(dx*dx + dy*dy) < 1.0f) {
                    enemy->takeDamage(10.0f);  // Танк бронирован
                    bullet->~Bullet();
                    if (!enemy->isAlive()) score += 30;
                    break;
                }
            }
        }
        
        // Удаляем мёртвых врагов
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy* e) { if (!e->isAlive()) { delete e; return true; } return false; }), enemies.end());
        fastEnemies.erase(std::remove_if(fastEnemies.begin(), fastEnemies.end(),
            [](EnemyFast* e) { if (!e->isAlive()) { delete e; return true; } return false; }), fastEnemies.end());
        tankEnemies.erase(std::remove_if(tankEnemies.begin(), tankEnemies.end(),
            [](EnemyTank* e) { if (!e->isAlive()) { delete e; return true; } return false; }), tankEnemies.end());
        
        // Удаляем неактивные пули
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet* b) { if (!b->getIsActive()) { delete b; return true; } return false; }), bullets.end());
        
        // СТОЛКНОВЕНИЯ: враги vs игрок (с отбрасыванием)
        bool justDamaged = false;
        float damageCooldown = 0.0f;
        
        // В игровом цикле перед обработкой столкновений:
        if (damageCooldown > 0) damageCooldown -= deltaTime;
        
        // Обычные враги
        for (auto* enemy : enemies) {
            float dx = player->getX() - enemy->getX();
            float dy = player->getY() - enemy->getY();
            float dist = std::sqrt(dx*dx + dy*dy);
            if (dist < 1.2f) {
                if (damageCooldown <= 0) {
                    player->takeDamage(8.0f);
                    damageCooldown = 0.5f;  // защита 0.5 сек после удара
                }
                enemy->knockback(player->getX(), player->getY(), 2.5f);
            }
        }
        
        // Быстрые враги
        for (auto* enemy : fastEnemies) {
            float dx = player->getX() - enemy->getX();
            float dy = player->getY() - enemy->getY();
            float dist = std::sqrt(dx*dx + dy*dy);
            if (dist < 1.2f) {
                if (damageCooldown <= 0) {
                    player->takeDamage(12.0f);
                    damageCooldown = 0.5f;
                }
                enemy->knockback(player->getX(), player->getY(), 3.0f);
            }
        }
        
        // Враги-танки
        for (auto* enemy : tankEnemies) {
            float dx = player->getX() - enemy->getX();
            float dy = player->getY() - enemy->getY();
            float dist = std::sqrt(dx*dx + dy*dy);
            if (dist < 1.2f) {
                if (damageCooldown <= 0) {
                    player->takeDamage(15.0f);
                    damageCooldown = 0.5f;
                }
                enemy->knockback(player->getX(), player->getY(), 1.5f);  // тяжёлого трудно отбросить
            }
        }
        
        // СБОР АПТЕЧЕК
        for (auto* hp : healthPacks) {
            if (!hp->isAlive()) continue;
            float dx = player->getX() - hp->getX();
            float dy = player->getY() - hp->getY();
            if (std::sqrt(dx*dx + dy*dy) < 1.0f) {
                float newHealth = player->getHealth() + hp->getHealAmount();
                if (newHealth > 100) newHealth = 100;
                player->setHealth(newHealth);
                hp->collect();
                score += 15;
                std::cout << "\n💊 +" << hp->getHealAmount() << " HP! 💊\n";
            }
        }
        
        // Отрисовка
        system("clear");
        std::cout << "=== БИТВА АРЕНА ===\n";
        std::cout << "Счёт: " << score << " | Время: " << (int)gameTime << " сек\n";
        std::cout << "Врагов: " << (enemies.size() + fastEnemies.size() + tankEnemies.size()) << "\n\n";
        
        drawMap(player, enemies, fastEnemies, tankEnemies, bullets, healthPacks);
        
        std::cout << "\n" << player->getRenderInfo() << "\n";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    // Итог
    system("clear");
    if (!player->isAlive()) {
        std::cout << "\n💀 ВЫ ПРОИГРАЛИ! 💀\n";
        std::cout << "Счёт: " << score << "\n";
        std::cout << "Вы продержались " << (int)gameTime << " секунд\n";
    } else {
        std::cout << "\n🏆 ПОБЕДА! 🏆\n";
        std::cout << "Финальный счёт: " << score << "\n";
        std::cout << "Время: " << (int)gameTime << " секунд\n";
    }
    
    // Очистка
    delete player;
    for (auto* e : enemies) delete e;
    for (auto* e : fastEnemies) delete e;
    for (auto* e : tankEnemies) delete e;
    for (auto* b : bullets) delete b;
    for (auto* h : healthPacks) delete h;
    
    InputHandler::restore();
    return 0;
}