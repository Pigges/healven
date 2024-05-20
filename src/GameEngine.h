#pragma once

#include <SFML/Graphics.hpp>
#include "EventListener.h"
#include "EntityManager.h"
#include "RenderManager.h"

class GameEngine {
public:
    GameEngine();
    virtual ~GameEngine();
    void gameLoop();

private:
    sf::RenderWindow window{};
    sf::Clock platformTime;
    sf::Clock deltaClock;
    void renderLoop();
    EventListener eventListener;
    EntityManager* entityManager = EntityManager::getInstance();
    RenderManager* renderManager = RenderManager::getInstance();
};
