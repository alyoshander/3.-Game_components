#include "GameEngine.h"
#include <iostream>

void GameEngine::update(float deltaTime) {
    for (auto* obj : updatables) {
        obj->update(deltaTime);
    }
}

void GameEngine::render() const {
    system("clear");  // или "cls" на Windows
    
    std::cout << "=== GAME RENDER ===\n\n";
    for (auto* obj : renderables) {
        obj->render();
        std::cout << "\n";
    }
    std::cout << "\n==================\n";
}

void GameEngine::clear() {
    updatables.clear();
    renderables.clear();
    ownedUpdatables.clear();
    ownedRenderables.clear();
}

GameEngine::~GameEngine() {
    clear();  // unique_ptr автоматически удалит всё
}