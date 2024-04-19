#include "Platform.h"
#include <SFML/Graphics.hpp>

Platform::Platform(sf::Vector2i position) : SpriteEntity("resources/sprites/platform.png") {
    sprite.setPosition(position.x, position.y);
}

void Platform::update(float delta) {

}