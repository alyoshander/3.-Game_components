#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    GameEngine engine;
    
    // Создаём объекты
    Player* player = new Player(10, 10);
    Enemy* enemy1 = new Enemy(2, 2, 10, 10);
    Enemy* enemy2 = new Enemy(18, 2, 10, 10);
    Bullet* bullet = new Bullet(10, 10, 0.7f, 0.7f);
    
    // Добавляем в движок (движок теперь владеет ими)
    engine.addObject(player);
    engine.addObject(enemy1);
    engine.addObject(enemy2);
    engine.addObject(bullet);
    
    // Игровой цикл (5 секунд)
    auto startTime = std::chrono::steady_clock::now();
    float lastTime = 0;
    
    std::cout << "Игра запущена на 5 секунд...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    while (true) {
        auto now = std::chrono::steady_clock::now();
        float currentTime = std::chrono::duration<float>(now - startTime).count();
        
        if (currentTime >= 5.0f) break;
        
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        engine.update(deltaTime);
        engine.render();
        
        // Отладочная информация
        std::cout << "\n[DEBUG] " << player->getRenderInfo() << "\n";
        std::cout << "[DEBUG] " << enemy1->getRenderInfo() << "\n";
        std::cout << "[DEBUG] " << enemy2->getRenderInfo() << "\n";
        std::cout << "[DEBUG] " << bullet->getRenderInfo() << "\n";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
    std::cout << "\nИгра завершена!\n";
    return 0;
}