

#include "ActionMoveTo.h"

namespace sge {
    
    ActionMoveTo* ActionMoveTo::create(float time, const Vec3& position){
    
        ActionMoveTo* action= new ActionMoveTo();
        action->_endPos=position;
        action->_duration=time;
        return action;
    
    }
    
    void ActionMoveTo::updateEntity(Entity* entity){
    
        float intValue= (_time-_startTime)/_duration;
        entity->transform().setTranslation(lerp(_starPos, _endPos, intValue));
    
    }
    
    void ActionMoveTo::start(Entity* entity){
    
        _starPos=entity->transform().getTranslation();
    
    }
    
    void ActionMoveTo::end(Entity* entity){
    
        entity->transform().setTranslation(_endPos);
    
    }
    
    ActionMoveTo::ActionMoveTo(){}
    ActionMoveTo:: ~ActionMoveTo(){}

}