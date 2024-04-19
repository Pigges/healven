#pragma once

#include "SpriteEntity.h"
#include <SFML/Graphics.hpp>

class Platform : public SpriteEntity {
public:
    Platform(sf::Vector2i position);

    void update(float delta);
};
