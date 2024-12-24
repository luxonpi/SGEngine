

#include "UpdateDispenser.h"

namespace sge {
    
    UpdateReceiver::UpdateReceiver(std::function< void(float) > callback, float interval, int priority){
    
        _interval=interval;
        _callback=callback;
        _priority=priority;
        _pastTime=interval;
        _enabled=true;
    
    }
    
    void UpdateReceiver::setEnabled(const bool& enabled){
    
        _enabled=enabled;
        
        if(_enabled){
            _pastTime=0;
        
        }
    
    }

    bool UpdateReceiver::isEnabled(){
    
        return _enabled;
        
    }
    
    void UpdateReceiver::update(float delta){
    
        _pastTime+=delta;
        if(_pastTime>=_interval){
        
            _callback(_pastTime);
            _pastTime=0;
            
        }
    
    }
    
    
    void UpdateDispenser::update(float delta){
    
        for (int i=0; i<_receiver.size(); i++) {
    
            if(!_receiver[i]->isEnabled()) continue;
            _receiver[i]->update(delta);
            
        }
    
    }
    
    void UpdateDispenser::addReceiver(UpdateReceiver* receiver){
    
        _receiver.push_back(receiver);
        
    }
    
    
    void UpdateDispenser::removeReceiver(UpdateReceiver* receiver){
    
        for (int i=0; i<_receiver.size(); i++) {
            
            if(_receiver[i]==receiver){
            
                _receiver.erase(_receiver.begin()+i);
                return;
            
            }
            
        }
        
        
    }
    
    
    
}