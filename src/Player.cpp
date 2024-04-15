#include "Player.h"
#include "SFML/Graphics.hpp"

Player::Player() : SpriteEntity(PLAYER_SPRITE) {
    sprite.setTextureRect(playerSprite[this->state]);
}

void Player::update(float delta) {
    velocity.x *= 1 / (1 + (delta * 10.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = 50;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -50;
    }
    sprite.move(velocity * delta);

    if (abs(velocity.x) < 0.1) velocity.x = 0;

    if (velocity.x == 0) state = PlayerState::IDLE;
    else state = PlayerState::WALKING;

    if (velocity.x < 0) sprite.setScale({ -10, 10 });
    else sprite.setScale({ 10, 10 });

    sprite.setTextureRect(playerSprite[this->state]);
}