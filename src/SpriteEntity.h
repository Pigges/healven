#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>

class SpriteEntity : public Entity {
public:
    explicit SpriteEntity(std::string file) : Entity() {
        // Load a sprite to display
        texture.loadFromFile(file); // TODO: Handle error case
        sprite.setTexture(texture);
        sprite.setScale(5, 5);
        sprite.setOrigin(8, 8);
    }

    virtual void update(float delta) {
    }

    sf::Drawable* getDrawable() {
        return &sprite;
    }

    sf::FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }
private:
    sf::Texture texture;
protected:
    sf::Sprite sprite;
};
