#include "Platform.h"
#include <SFML/Graphics.hpp>

Platform::Platform(sf::Vector2i position) : SpriteEntity("resources/sprites/platform.png") {
    sprite.setPosition(position.x, position.y);
    //sprite.setPosition(std::rand() % renderManager->getWindow()->getSize().x - sprite.getGlobalBounds().getSize().x, -200);
}

void Platform::update(float delta) {
    move(delta);
}

void Platform::move(float delta) {
    sprite.move(0,   100*delta);
}