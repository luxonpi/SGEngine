

#include "KeyboardDispenser.h"

namespace sge {
    
    KeyboardReceiver::KeyboardReceiver(int priority){
        
        _priority=priority;
        _enabled=true;
        
    }
    
    
    void KeyboardReceiver::keyReleased(KeyEvent* event){

        if(releaseCallback)releaseCallback(event);
    }
    
    void KeyboardReceiver::keyPressed(KeyEvent* event){

       if(pressCallback) pressCallback(event);

    }
    
    void KeyboardReceiver::setEnabled(const bool& enabled){
        
        _enabled=enabled;
       
    }
    
    bool KeyboardReceiver::isEnabled(){
        
        return _enabled;
        
    }
    
    
    
    
    void KeyboardDispenser::keyReleased(KeyEvent* event){
    
        for (int i=0; i<_receiver.size(); i++) {
            
            if(!_receiver[i]->isEnabled()) continue;
            _receiver[i]->keyReleased(event);
            
        }
    }
    
    
    void KeyboardDispenser::keyPressed(KeyEvent* event){
    
        for (int i=0; i<_receiver.size(); i++) {

            if(!_receiver[i]->isEnabled()) continue;
            _receiver[i]->keyPressed(event);
            
        }
    
    }
    
    
    void KeyboardDispenser::addReceiver(KeyboardReceiver* receiver){
        
        _receiver.push_back(receiver);
        
    }
    
    
    void KeyboardDispenser::removeReceiver(KeyboardReceiver* receiver){
        
        for (int i=0; i<_receiver.size(); i++) {
            
            if(_receiver[i]==receiver){
                
                _receiver.erase(_receiver.begin()+i);
                return;
                
            }
            
        }
        
        
    }
    
    
    
}