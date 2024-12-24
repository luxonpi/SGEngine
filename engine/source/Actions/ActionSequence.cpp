

#include "ActionSequence.h"

namespace sge {

    ActionSequence::ActionSequence(){

        _indexOfRunningAction=0;
        _runningAction=NULL;
        _time=0;
        
    }

    ActionSequence::~ActionSequence(){}
    
    void ActionSequence::runNextAction(Entity* entity){
    
        _runningAction->end(entity);
        
        if(_indexOfRunningAction<_actions.size()-1){
            
            _indexOfRunningAction++;
            _runningAction=_actions[_indexOfRunningAction];
            
            _runningAction->start(entity);
            
            if(_runningAction->_duration==0){
            
                runNextAction(entity);
            
            }else{
                
                _runningAction->_time=_time;
                _runningAction->updateEntity(entity);
                
            }
            
        }

    
    }

    void ActionSequence::updateEntity(Entity* entity){
    
        _runningAction->_time=_time;
        
        // Action finshed
        if(_time >= _runningAction->_endTime){
        
            runNextAction(entity);
            
        }else{
        
            _runningAction->updateEntity(entity);

        }
        
        
    }
    
    void ActionSequence::start(Entity* entity){
    
        _indexOfRunningAction=0;
        _runningAction= _actions[0];
        _runningAction->_time=0;
        _runningAction->start(entity);

    }
    
    void ActionSequence::end(Entity* entity){
    
        //    entity->setPosition(_endPos);
//        for (int i=0; i<_actions.size(); i++) {
//            
//            delete _actions[i];
//            
//        }
    
    }

    ActionSequence* ActionSequence::create(std::vector<Action*> actions){
    
        ActionSequence* actionSequence= new ActionSequence();
        actionSequence->_actions=actions;
        
        for (int i=0; i<actions.size(); i++) {
            
            actions[i]->_startTime= actionSequence->_duration;
            actions[i]->_endTime= actionSequence->_duration+actions[i]->_duration;
            actionSequence->_duration+= actions[i]->_duration;
        
        }
        
        return actionSequence;
    
    }

}
