

#include "Component.h"

namespace sge {
    
    void Component::setTypeName(){
    
        _componentKey="";

    }
        
    Component::Component(){
      
        _entity=NULL;
        _componentKey="";
        _enabled=false;
        
    }
    
    Entity* Component::getEntity(){
    
        return _entity;
        
    }
   
    Component::~Component(){
        
    }

    void Component::setEnabled(bool enabled){
    
        _enabled=enabled;
    
    }
    
    std::string Component::getComponentKey(){
    
        return _componentKey;
    
    }

    void Component::addedToEntity(Entity* entity){
    
    
    }

 
}