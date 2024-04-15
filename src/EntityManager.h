#pragma once

#include <vector>
#include "Entity.h"

class EntityManager {
private:
    std::vector<Entity*> entities;
    static EntityManager* instancePtr;

    EntityManager() {}
public:
    EntityManager(const EntityManager &obj) = delete;
    EntityManager& operator=(const EntityManager &obj) = delete;

    static EntityManager *getInstance() {
        // If there is no instance of class
        // then we can create an instance.
        if (instancePtr == NULL)
            instancePtr = new EntityManager();

        return instancePtr;
    }

    void add(Entity* entity) {
        entities.push_back(entity);
    }

    std::vector<Entity*> getEntities() {
        return entities;
    }

    void update(float delta) {
        for (Entity *entity : entities) {
            entity->update(delta);
        }
    }

    // Destructor to clean up memory
    ~EntityManager() {
        if (instancePtr != nullptr) {
            delete instancePtr;
            instancePtr = nullptr;
        }
    }
};
