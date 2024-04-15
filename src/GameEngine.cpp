#include "GameEngine.h"
#include "Player.h"

GameEngine::GameEngine() :
        window(sf::VideoMode(1280, 720), "Healven"), eventListener(&window) {

}

GameEngine::~GameEngine() = default;

void GameEngine::gameLoop() {
    this->renderLoop();
}

void GameEngine::renderLoop() {
    sf::View view(sf::Vector2(0.0f, 0.0f), sf::Vector2f(1280, 720));
    window.setView(view);

    entityManager->add(new Player());

    sf::Clock deltaClock;

    while (window.isOpen()) {
        // Input
        eventListener.pollEvents();

        window.setView(window.getDefaultView());

        window.clear();

        entityManager->update(deltaClock.restart().asSeconds());

        for (Entity *entity : entityManager->getEntities()) {
            window.draw(*entity->getDrawable()); // Render the Entity's drawable
        }

        window.display();
    }
}