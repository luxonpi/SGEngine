

#include "ActionParallel.h"

namespace sge {
    
    ActionParallel::ActionParallel(){
        
        _time=0;
        
    }
    
    ActionParallel::~ActionParallel(){}
    
    void ActionParallel::updateEntity(Entity* entity){
        
        for (int i=0; i<_actions.size(); i++) {
            
            if(_time>_actions[i]->_endTime){
            
                if( _actions[i]->_isRunning==true){
                    _actions[i]->_time=_actions[i]->_endTime;
                    _actions[i]->end(entity);
                    _actions[i]->_isRunning=false;
                }
            
            }else{
            
                _actions[i]->_time= _time;
                _actions[i]->updateEntity(entity);

                
            }
            
            
        }
        
    }
    
    void ActionParallel::start(Entity* entity){
        
        for (int i=0; i<_actions.size(); i++) {
            
            _actions[i]->_isRunning=true;
            _actions[i]->_time= 0;
            _actions[i]->start(entity);
            
        }
        
    }
    
    void ActionParallel::end(Entity* entity){
        
        
    }
    
    ActionParallel* ActionParallel::create(std::vector<Action*> actions){
        
        ActionParallel* actionParallel= new ActionParallel();
        actionParallel->_actions=actions;
        
        for (int i=0; i<actions.size(); i++) {
            
            actions[i]->_startTime= 0;
            actions[i]->_endTime= actions[i]->_duration;
            
            if(actionParallel->_duration<actions[i]->_duration){
                
                actionParallel->_duration= actions[i]->_duration;
            
            }
            
        }
        
        return actionParallel;
        
    }
    
}
