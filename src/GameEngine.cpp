#include "GameEngine.h"
#include "Player.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>

GameEngine::GameEngine() :
        window(sf::VideoMode(480, 854), "Healven"), eventListener(&window) {
    window.setSize(sf::Vector2u(480, 854));
}

GameEngine::~GameEngine() = default;

void GameEngine::gameLoop() {
    this->renderLoop();
}

void GameEngine::renderLoop() {
    sf::View view(sf::Vector2(0.0f, 0.0f), sf::Vector2f(1280, 720));
    window.setView(view);

    entityManager->add(new Player());
    entityManager->add(new Platform(sf::Vector2i(100, 700)));
    entityManager->add(new Platform(sf::Vector2i(350, 550)));

    //entityManager->add(new Platform(sf::Vector2i(100, 400)));
    entityManager->add(new Platform(sf::Vector2i(100, 300)));

    sf::Clock deltaClock;

    while (window.isOpen()) {
        // Input
        eventListener.pollEvents();

        window.setView(window.getDefaultView());

        window.clear(sf::Color::Red);

        entityManager->update(deltaClock.restart().asSeconds());

        for (Entity *entity : entityManager->getEntities()) {
            window.draw(*entity->getDrawable()); // Render the Entity's drawable
        }

        window.display();
    }
}