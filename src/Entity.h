#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class Entity {
public:
    Entity() = default;
    virtual void update(float delta) = 0;
    virtual sf::Drawable* getDrawable() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
};
