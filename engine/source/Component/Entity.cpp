

#include "Entity.h"
#include "ActionComponent.h"

namespace sge {

    Entity::Entity(){
    
        _actionComponent= new ActionComponent();
        addComponent(_actionComponent);
   
    }
    
    Entity::~Entity(){
    
    
    }
    
    ActionComponent* Entity::getActionComponent(){

        return _actionComponent;
    
    }
    
    void Entity::addComponent(Component* component){
    
        _components.push_back(component);
        component->_entity=this;
        component->setEnabled(true);
        component->addedToEntity(this);
    
    }
    
    void Entity::removeComponent(Component* component){
    
    
    
    }
    
    Component* Entity::getComponentByName(std::string name){
    
        for(unsigned int i=0; i<_components.size(); i++) {
            
            if(_components[i]->getComponentKey()==name) return _components[i];
            
        }
        
        return NULL;
    }
    
    
    Component* Entity::getComponentByType(){
    
        return NULL;
    }
    
    int32_t Entity::getUID(){
    
        return _uID;
    
    }

    
}