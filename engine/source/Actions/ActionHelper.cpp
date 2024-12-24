

#include "ActionHelper.h"

namespace sge {
    
    // Wait
    ActionWait* ActionWait::create(float time){
        
        ActionWait* action= new ActionWait();
        action->_duration=time;
        return action;
        
    }
    
    void ActionWait::updateEntity(Entity* entity){
        
    }
    
    void ActionWait::start(Entity* entity){
        
        
    }
    
    void ActionWait::end(Entity* entity){
        
        
    }
    
    ActionWait::ActionWait(){}
    ActionWait:: ~ActionWait(){}
    
    //Function
    ActionFunction* ActionFunction::create(std::function< void() > callback){
        
        ActionFunction* action= new ActionFunction();
        action->_duration=0;
        action->_callback=callback;
        return action;
        
    }
    
    void ActionFunction::updateEntity(Entity* entity){
        
    }
    
    void ActionFunction::start(Entity* entity){
        
        
    }
    
    void ActionFunction::end(Entity* entity){
        
        if(_callback) _callback();
        
    }
    
    ActionFunction::ActionFunction(){}
    ActionFunction::~ActionFunction(){}
    
}