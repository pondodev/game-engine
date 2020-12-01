#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "./entity_manager.h"
#include "./component.h"

class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;

    public:
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        // generic way of adding components to an entity
        template <typename T, typename... TArgs> // T == type of component
                                                 // TArgs == type of args for constructing component
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args)...)); // construct the component itself
            newComponent->owner = this;
            components.emplace_back(newComponent);
            newComponent->Initialise();
            return *newComponent;
        }
};

#endif