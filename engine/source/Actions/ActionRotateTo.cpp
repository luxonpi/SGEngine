

#include "ActionRotateTo.h"

namespace sge {
    
    ActionRotateTo* ActionRotateTo::create(float time, const Vec3& position){
        
        ActionRotateTo* action= new ActionRotateTo();
        action->_endRotation=position;
        action->_duration=time;
        return action;
        
    }
    
    void ActionRotateTo::updateEntity(Entity* entity){
        
        float intValue= (_time-_startTime)/_duration;
        
        Quaternion quad;
        Quaternion::slerp(_starRotation, _endRotation, intValue, &quad);
        
        entity->transform().setRotation(quad);
        
    }
    
    void ActionRotateTo::start(Entity* entity){
        
        _starRotation=entity->transform().getRotation();
        
    }
    
    void ActionRotateTo::end(Entity* entity){
        
         entity->transform().setRotation(_endRotation);
        
    }
    
    ActionRotateTo::ActionRotateTo(){}
    ActionRotateTo:: ~ActionRotateTo(){}
    
}