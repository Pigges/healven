#pragma once

#include <unordered_map>
#include "SpriteEntity.h"
#include "Animation.h"
#include "EntityManager.h"
#include <vector>

#define PLAYER_SPRITE "resources/sprites/player.png"

#define GLIDING_SPEED_FACTOR 1.6f
#define JUMPING_SPEED 700
#define GRAVITY 300

enum class PlayerState {
    IDLE,
    WALKING,
    RUNNING,
    JUMPING,
    FALLING,
    GLIDING,
    DIVING
};

class Player : public SpriteEntity {
protected:

public:
    Player();

    void update(float delta);

private:
    float health = 0;
    PlayerState state = PlayerState::IDLE;
    float jumpProgress = 0.0f;
    sf::Vector2f velocity;
    std::unordered_map<PlayerState, Animation*> animations;
    EntityManager* entityManager = EntityManager::getInstance(); // Grab the entity manager

    void applyGravity(float delta);
    std::vector<Entity*> getCollisions();

};
