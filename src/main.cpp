#include <SFML/Graphics.hpp>
#include <iostream>
#include "RenderManager.h"
#include "EntityManager.h"
#include "EventListener.h"
#include "SpriteEntity.h"
#include "GameEngine.h"

int main() {

    /*RenderManager* renderManager = RenderManager::getInstance();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Healven");
    renderManager->setWindow(window);*/

    auto gameEngine = new GameEngine();

    gameEngine->gameLoop();

    return 0;
}
