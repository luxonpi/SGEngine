

#include "PhysicWorld.h"
#include "Director.h"

#include "ColliderComponent.h"
#include "PhysicComponent.h"

namespace sge {
    
    PhysicsWorld::PhysicsWorld(){

        setGravity(Vec3(0, -0.1, 0));
        
        // Register update
        _updateReceiver= new UpdateReceiver(CALLBACK_SELECTOR(PhysicsWorld::update, this), 1/60. , 0);
        Director::getInstance()->getUpdateDispenser()->addReceiver(_updateReceiver);
        
    }
    
    void PhysicsWorld::update(float delta){
    
        
    }

    void PhysicsWorld::addEntity(Entity* entity){
        
        //ColliderComponent* collider= (ColliderComponent*) entity->getComponentByName("ColliderComponent");
      
        _entities.push_back(entity);
        
    }
    
    void PhysicsWorld::setGravity(const Vec3& gravity){
    
        _gravity=gravity;
    
    }
    
    void PhysicsWorld::drawDebug(){
    
              
    }
    
    PhysicsWorld::~PhysicsWorld(){
        
        Director::getInstance()->getUpdateDispenser()->removeReceiver(_updateReceiver);
        delete _updateReceiver;
    
    }
    
}