#pragma once

#include "SpriteEntity.h"
#include <SFML/Graphics.hpp>
#include "RenderManager.h"

class Platform : public SpriteEntity {
public:
    Platform(sf::Vector2i position);

    void update(float delta);

    void move(float delta);
private:
    RenderManager* renderManager = RenderManager::getInstance();
};
