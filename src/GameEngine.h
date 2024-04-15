#pragma once

#include <SFML/Graphics.hpp>
#include "EventListener.h"
#include "EntityManager.h"

class GameEngine {
public:
    GameEngine();
    virtual ~GameEngine();
    void gameLoop();

private:
    sf::RenderWindow window{};
    void renderLoop();
    EventListener eventListener;
    EntityManager* entityManager = EntityManager::getInstance();
};
