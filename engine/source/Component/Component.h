

#ifndef SGENGINE_COMPONENT_H
#define SGENGINE_COMPONENT_H

#include <stdio.h>

#include "SBase.h"

namespace sge {

    class Entity;
    
    class Component{
    
    friend Entity;
        
    protected:
        
        Entity* _entity;
        std::string _componentKey;
        bool _enabled;
        
        Component();
        ~Component();
        
        virtual void setTypeName()=0;
        
        virtual void addedToEntity(Entity* entity);
        
    public:
        
        std::string getComponentKey();
        Entity* getEntity();

        virtual void setEnabled(bool enabled);
        
    
    
    };
    
    
}


#endif