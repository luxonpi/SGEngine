

#include "EntityManager.h"

namespace sge {

    EntityManager::EntityManager(){
    
    }
    
    EntityManager::~EntityManager(){
    
    }

    EntityManager* EntityManager::_instance=NULL;
    
    EntityManager* EntityManager::getInstance(){
    
        if(!_instance) _instance= new EntityManager();
        return _instance;
    
    }

    int32_t EntityManager::addEntity(Entity* entity){
    
        entity->_uID=_count;
        _entityMap.insert(std::make_pair(_count, entity));
        
        _count++;
        
        return entity->_uID;
        
    }
    
    void EntityManager::removeEntity(Entity* entity){
    
    
    }

}