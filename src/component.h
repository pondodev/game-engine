#ifndef COMPONENT_H
#define COMPONENT_H

#include "./entity.h"

class Entity;

class Component {
    public:
        Entity* owner;
        virtual ~Component() {}
        virtual void Initialise() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}
};

#endif