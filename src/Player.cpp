#include "Player.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>

Player::Player() : SpriteEntity(PLAYER_SPRITE) {
    sprite.setPosition(100, -100);
    sprite.setOrigin(8, 8);

    // A bunch of animation definitions
    animations[PlayerState::IDLE] = new Animation(sprite, 16);
    animations[PlayerState::WALKING] = new Animation(sprite, 16);
    animations[PlayerState::JUMPING] = new Animation(sprite, 16);
    animations[PlayerState::FALLING] = new Animation(sprite, 16);
    animations[PlayerState::GLIDING] = new Animation(sprite, 16);

    animations[PlayerState::IDLE]->addFrame(sf::Vector2i(0, 0), 1);
    animations[PlayerState::IDLE]->addFrame(sf::Vector2i(1, 0), 1);
    animations[PlayerState::IDLE]->addFrame(sf::Vector2i(2, 0), 1);
    animations[PlayerState::IDLE]->addFrame(sf::Vector2i(3, 0), 1);

    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(0, 1), 0.15);
    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(1, 1), 0.15);
    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(2, 1), 0.15);
    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(3, 1), 0.15);
    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(4, 1), 0.15);
    animations[PlayerState::WALKING]->addFrame(sf::Vector2i(5, 1), 0.15);

    animations[PlayerState::JUMPING]->addFrame(sf::Vector2i(0, 2), 0.5);
    animations[PlayerState::JUMPING]->addFrame(sf::Vector2i(1, 2), 0.5);

    animations[PlayerState::FALLING]->addFrame(sf::Vector2i(4, 0), 0.15);

    animations[PlayerState::GLIDING]->addFrame(sf::Vector2i (3, 2), 1);
}

void Player::update(float delta) {
    velocity.x *= 1 / (1 + (delta * 15.f));

    if (renderManager->getWindow()->hasFocus()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = 300;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -300;
        }
    }

    if (jumpProgress) {
        jumpProgress -= delta;
        velocity.y = -JUMPING_SPEED;

        if (jumpProgress < 0) jumpProgress = 0.0f;
    } else {
        velocity.y = 0.0f;
    }

    sprite.move(velocity * delta * (state == PlayerState::GLIDING ? GLIDING_SPEED_FACTOR : 1));

    applyGravity(delta);

    if (sprite.getPosition().x < 0) sprite.move(480, 0);
    else if (sprite.getPosition().x > 480) sprite.move(-480, 0);

    // Set velocity to 0 if the speed is being slowed down
    if (abs(velocity.x) < 0.2) velocity.x = 0;

    if (!jumpProgress) {
        if (velocity.x == 0) state = PlayerState::IDLE;
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) state = PlayerState::GLIDING;
            else state = PlayerState::WALKING;
        }
    }

    // Set looking direction
    if (velocity.x < 0) sprite.setScale({ -5, 5 });
    else if (velocity.x > 0) sprite.setScale({ 5, 5 });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumpProgress && !getCollisions().empty()) {
        jumpProgress = 0.5f;
        state = PlayerState::JUMPING;
    }

    if (getCollisions().empty() && !jumpProgress) state = PlayerState::FALLING;


    // Update Animations (fallback to PlayerState::IDLE)
    if (animations[state])
        animations[state]->update(delta);
    else
        animations[PlayerState::IDLE]->update(delta);

}

void Player::applyGravity(float delta) {
    bool collision = false;
    for (Entity *entity : getCollisions()) {
        // Check if the player is standing with at least half the body above the platform
        if (entity->getGlobalBounds().getPosition().y <= sprite.getGlobalBounds().getPosition().y + sprite.getGlobalBounds().getSize().y && sprite.getGlobalBounds().getPosition().y + (sprite.getGlobalBounds().getSize().y/4)*3 < entity->getGlobalBounds().getPosition().y) {
            collision = true;

            // Move player to top of platform
            if (entity->getGlobalBounds().getPosition().y <= sprite.getGlobalBounds().getPosition().y + sprite.getGlobalBounds().getSize().y -1) sprite.setPosition(sprite.getPosition().x, entity->getGlobalBounds().getPosition().y - sprite.getGlobalBounds().getSize().y/2);
            break;
        }
    }

    // Apply gravity only when there is no collision
    if (!collision) sprite.move(0, GRAVITY * delta);
    else jumpProgress = 0.0f; // There can't be a jump currently if we are colliding
}


// Get all Entities the player is colliding with
std::vector<Entity*> Player::getCollisions() {
    std::vector<Entity*> collisions;
    for (Entity *entity : entityManager->getEntities()) {
        if (typeid(*entity) == typeid(Player)) continue;
        if (sprite.getGlobalBounds().intersects(entity->getGlobalBounds())) collisions.push_back(entity);
    }

    return collisions;
}