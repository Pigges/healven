#pragma once

#include <unordered_map>
#include "SpriteEntity.h"

#define PLAYER_SPRITE "resources/sprites/player.png"

enum class PlayerState {
    IDLE,
    WALKING,
    RUNNING,
    JUMPING
};

class Player : public SpriteEntity {
public:
    Player();

    void update(float delta);

private:
    float health = 0;
    PlayerState state = PlayerState::IDLE;
    sf::Vector2f velocity;

    std::unordered_map<PlayerState, sf::IntRect> playerSprite = {
            { PlayerState::IDLE, sf::IntRect(0, 0, 16, 16) },
            { PlayerState::WALKING, sf::IntRect(0, 16, 16, 16) },
    };
};
