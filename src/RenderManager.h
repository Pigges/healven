#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

enum GameState {
    PLAYING, PAUSED
};

class RenderManager {
private:
    EntityManager* entityManager = EntityManager::getInstance();
    sf::RenderWindow* window;
    GameState state = PLAYING;
    sf::Clock stateTime;
    static RenderManager* instancePtr; // Pointer to the singleton instance


    RenderManager() : window(nullptr) {}

public:
    RenderManager(const RenderManager &obj) = delete;
    RenderManager& operator=(const RenderManager &obj) = delete;

    static RenderManager *getInstance() {
        // If there is no instance of class
        // then we can create an instance.
        if (instancePtr == NULL)
            instancePtr = new RenderManager();

        return instancePtr;
    }

    // Destructor to clean up memory
    ~RenderManager() {
        if (instancePtr != nullptr) {
            delete instancePtr;
            instancePtr = nullptr;
        }
    }

    // Set the window object
    void setWindow(sf::RenderWindow& window) {
        this->window = &window;
    }

    void render() {
        // Draw every Entity found in entities
        for (Entity *entity : entityManager->getEntities()) {
            window->draw(*entity->getDrawable()); // Render the Entity's drawable
        }
        window->display();
    }

    void setState(GameState state) {
        this->state = state;
        stateTime.restart();
    }


    // Get the current window object
    sf::RenderWindow * getWindow() {
        return window;
    }

    // Get the current game state
    GameState getState() {
        return state;
    }

    // Get the elapsed time since last state change (in ms)
    int getStateTime() {
        return stateTime.getElapsedTime().asMilliseconds();
    }
};