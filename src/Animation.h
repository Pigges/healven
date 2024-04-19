#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

struct Frame {
    sf::IntRect rect;
    double duration; // in seconds
};

class Animation {
public:
    Animation(sf::Sprite &target, int gridSize) {
        this->target = &target;
        this->gridSize = gridSize;
        totalProgress = 0.0;
    }

    // Add a Frame to the animation
    void addFrame(sf::Vector2i position, double duration) {
        frames.push_back({sf::IntRect(position.x*gridSize, position.y*gridSize, 16, 16), duration});
        totalLength += duration;
    }

    void update(double elapsed) {
        totalProgress += elapsed;
        if (totalProgress >= totalLength) totalProgress = totalProgress - totalLength; // Loop the Animation
        double progress = totalProgress;
        for (auto frame: frames) {
            progress -= (frame).duration;

            if (progress <= 0.0 || &(frame) == &frames.back()) {
                target->setTextureRect((frame).rect);
                break; // we found our frame
            }
        }
    };

private:
    std::vector<Frame> frames;
    double totalLength;
    double totalProgress;
    int gridSize;
    sf::Sprite *target;

};