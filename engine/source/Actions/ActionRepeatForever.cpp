

#include "ActionRepeatForever.h"

namespace sge {
    
    ActionRepeatForever::ActionRepeatForever(){
        
        _time=0;
        _action=NULL;
        _repeats=1;
        
    }
    
    ActionRepeatForever::~ActionRepeatForever(){}
    
    void ActionRepeatForever::updateEntity(Entity* entity){
        
        _action->_time=_time;
        _action->updateEntity(entity);
        
    }
    
    void ActionRepeatForever::start(Entity* entity){
        
        _action->start(entity);
        
    }
    
    void ActionRepeatForever::end(Entity* entity){
        
        _action->end(entity);
        _time=0;
        _repeats=1;

    }
    
    ActionRepeatForever* ActionRepeatForever::create(Action* action){
        
        ActionRepeatForever* repeatAction= new ActionRepeatForever();
        repeatAction->_action=action;
        
        repeatAction->_duration= action->_duration;
        action->_startTime= 0;
        action->_endTime= repeatAction->_duration;
        
        return repeatAction;
        
    }
    
}
