

#include "PhysicComponent.h"

#include "Director.h"
#include "Entity.h"

namespace sge {
    
    int PhysicsComponent::MODE_STATIC=0;
    int PhysicsComponent::MODE_DYNAMIC=1;
    
    PhysicsComponent::PhysicsComponent(){
        
        _velocity.set(0, 0, 0);
        
        _minimalHeight=-100;
        _mass=0;
        _friction=1;
        _bounciness=0;
        _inverseMass=0;
        
        _mode= MODE_DYNAMIC;
        setTypeName();

        setEnabled(false);
        
    }
    
    void PhysicsComponent::setTypeName(){
        
        _componentKey="PhysicsComponent";
        
    }
    
    void PhysicsComponent::setEnabled(bool enabled){
        
        Component::setEnabled(enabled);
               
    }
    
    void PhysicsComponent::setMode(int mode){
    
        _mode=mode;
    
    }
 
    
    void PhysicsComponent::setMass(float mass){
    
        _mass=mass;
        
        if(mass==0){
    
            _inverseMass=0;
    
        }else{
        
            _inverseMass=1.0/mass;
        
        }
        
    }
    
    void PhysicsComponent::setMinimalHeight(float minimalHeight){
    
        _minimalHeight=minimalHeight;
    
    }
    
    void PhysicsComponent::setFriction(float friction){
    
        _friction=friction;
    
    }
    
    void PhysicsComponent::setBounciness(float bounciness){
    
        _bounciness=bounciness;
    
    }
    
    void PhysicsComponent::setMoveVec(Vec3 vec, float velocity){
    
        _velocity=vec;
        velocity=velocity;
    
    }
    
    void PhysicsComponent::applyForce(Vec3 force){
    
        _velocity+=force;
    
    }

    PhysicsComponent::~PhysicsComponent(){
        
        
    }
    
}

