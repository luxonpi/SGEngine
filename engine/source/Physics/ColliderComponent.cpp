

#include "ColliderComponent.h"

#include "Director.h"
#include "Entity.h"

namespace sge {
    
    ColliderComponent::ColliderComponent(){
        
        setEnabled(false);
        
    }
    
    void ColliderComponent::setTypeName(){
        
        _componentKey="ColliderComponent";
        
    }
    
    void ColliderComponent::addSphere(Vec3 offset, float radius){
    
    
    }
    
    void ColliderComponent::addBox(Vec3 offset, Vec3 size, Vec3 rotation){
    
    
    }
    
    void ColliderComponent::setEnabled(bool enabled){
        
        Component::setEnabled(enabled);
        
    }
    
    ColliderComponent::~ColliderComponent(){
        
        
    }
    
}

