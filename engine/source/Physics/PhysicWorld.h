

#ifndef SGENGINE_PHYSICWORLD_H
#define SGENGINE_PHYSICWORLD_H

#include <stdio.h>
#include "SBase.h"
#include "Entity.h"
#include "UpdateDispenser.h"

namespace sge {
    
class PhysicsWorld{

protected:
    
    UpdateReceiver* _updateReceiver;

    Vec3 _gravity;
    
   
    
public:
    
    std::vector<Entity*> _entities;

    PhysicsWorld();
    ~PhysicsWorld();
    
    void update(float delta);

    void setGravity(const Vec3& gravity);
    void addEntity(Entity* entity);

    
    void drawDebug();

};
    
}

#endif
