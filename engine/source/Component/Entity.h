

#ifndef SGENGINE_ENTITY_H
#define SGENGINE_ENTITY_H

#include <stdio.h>
#include <vector>

#include "Node.h"
#include "Component.h"

namespace sge {
   
    class EntityManager;
    class ActionComponent;
    
    class Entity: public Node{
    
    friend EntityManager;
        
    private:
        
        std::vector<Component*> _components;
        
        ActionComponent* _actionComponent;
        
        int32_t _uID;
        
    public:
        
        ActionComponent* getActionComponent();
        
        Entity();
        ~Entity();
        
        void addComponent(Component* component);
        void removeComponent(Component* component);

        Component* getComponentByName(std::string name);
        Component* getComponentByType();
        
        int32_t getUID();
    
    
    };
    
}

#endif