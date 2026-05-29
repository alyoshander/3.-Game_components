#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "IUpdatable.h"
#include "IRenderable.h"
#include <vector>
#include <memory>

class GameEngine {
private:
    std::vector<IUpdatable*> updatables;
    std::vector<IRenderable*> renderables;
    
    // Для автоматического удаления объектов (умные указатели)
    std::vector<std::unique_ptr<IUpdatable>> ownedUpdatables;
    std::vector<std::unique_ptr<IRenderable>> ownedRenderables;
    
public:
    // Добавить объект (движок забирает владение)
    template<typename T>
    void addObject(T* obj);
    
    void update(float deltaTime);
    void render() const;
    
    void clear();
    ~GameEngine();
};

// Реализация шаблона прямо в .h (так нужно для template)
template<typename T>
void GameEngine::addObject(T* obj) {
    // Проверяем, реализует ли объект IUpdatable
    if constexpr (std::is_base_of_v<IUpdatable, T>) {
        updatables.push_back(obj);
        ownedUpdatables.push_back(std::unique_ptr<T>(obj));
    }
    // Проверяем, реализует ли объект IRenderable
    if constexpr (std::is_base_of_v<IRenderable, T>) {
        renderables.push_back(obj);
        ownedRenderables.push_back(std::unique_ptr<T>(obj));
    }
}

#endif