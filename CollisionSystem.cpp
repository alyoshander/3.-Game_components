#include "CollisionSystem.h"
#include <cmath>

void CollisionSystem::handleCollisions(Player* player,
                                        std::vector<Enemy*>& enemies,
                                        std::vector<Bullet*>& bullets) {
    if (!player->isAlive()) return;
    
    // Пули vs Враги
    for (auto* bullet : bullets) {
        if (!bullet->getIsActive()) continue;
        
        for (auto* enemy : enemies) {
            if (!enemy->isAlive()) continue;
            
            float dx = bullet->getX() - enemy->getX();
            float dy = bullet->getY() - enemy->getY();
            float dist = std::sqrt(dx*dx + dy*dy);
            
            if (dist < 1.0f) {  // Попадание!
                enemy->takeDamage(10.0f);
                bullet->~Bullet();  // пуля исчезает
                break;
            }
        }
    }
    
    // Враги vs Игрок
    for (auto* enemy : enemies) {
        if (!enemy->isAlive()) continue;
        
        float dx = player->getX() - enemy->getX();
        float dy = player->getY() - enemy->getY();
        float dist = std::sqrt(dx*dx + dy*dy);
        
        if (dist < 1.0f) {
            player->takeDamage(1.0f);
        }
    }
}