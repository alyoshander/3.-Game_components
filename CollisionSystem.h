#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class CollisionSystem {
public:
    static void handleCollisions(Player* player, 
                                  std::vector<Enemy*>& enemies,
                                  std::vector<Bullet*>& bullets);
};

#endif