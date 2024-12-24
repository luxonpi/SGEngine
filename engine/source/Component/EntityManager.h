

#ifndef SGENGINE_ENTITYMANAGER_H
#define SGENGINE_ENTITYMANAGER_H

#include <stdio.h>
#include <stdint.h>
#include <unordered_map>

#include "Entity.h"

namespace sge {
    
    class EntityManager{
        
    private:
        
        // Könnte probleme bereiten
        unsigned int _count;
        
        std::unordered_map<int32_t, Entity*> _entityMap;
        
        EntityManager();
        ~EntityManager();
        
        static EntityManager* _instance;
        
    public:
        
        static EntityManager* getInstance();
       
        int32_t addEntity(Entity* entity);
        void removeEntity(Entity* entity);
        
        
    };
    
}

#endif
