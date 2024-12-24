

#include "ActionComponent.h"
#include "Director.h"
#include "Entity.h"

namespace sge {
    
    ActionComponent::ActionComponent(){
        
        setTypeName();

        _updateReceiver= new UpdateReceiver(CALLBACK_SELECTOR(ActionComponent::update, this), 1/60. , 0);
        Director::getInstance()->getUpdateDispenser()->addReceiver(_updateReceiver);
        
        setEnabled(false);
        
        _testAction=NULL;
        _entity=NULL;
        
    }
   
    void ActionComponent::setTypeName(){
        
        _componentKey="ActionComponent";
        
    }
    
    void ActionComponent::runAction(Action* action){
    
        _testAction=action;
        _testAction->_startTime=0;
        _testAction->_endTime=_testAction->_startTime+_testAction->_duration;
        _testAction->start(_entity);
    
    }
    
    void ActionComponent::setEnabled(bool enabled){
        
        Component::setEnabled(enabled);
        // ToDo deactivate all key state
        if(!enabled){
            
            _updateReceiver->setEnabled(false);
            
        }else{
            
            _updateReceiver->setEnabled(true);
            
        }
        
    }
    
    void ActionComponent::update(float delta){
        
        if(_testAction && _entity){
        
            _testAction->_time+=delta/10.;
            
            if(_testAction->_time> _testAction->_duration){
            
                _testAction->_time=_testAction->_duration;
                
            }
            
            _testAction->updateEntity(_entity);
            
            // End Action
            if(_testAction->_time== _testAction->_duration){
            
                _testAction->end(_entity);
                
                if(_testAction->_repeats>0){
                
                    runAction(_testAction);
                    _testAction->_repeats--;
                    
                }else{
                    
                    delete _testAction;
                    _testAction=NULL;
                
                }
            }
            
        
        }
        
    }
    
    bool ActionComponent::isRunningAction(){
    
        return _testAction!=NULL;
        
    }

    
    ActionComponent::~ActionComponent(){
        
        
    }
    
}

