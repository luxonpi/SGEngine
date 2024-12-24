

#include "TouchDispenser.h"

namespace sge {
    
    TouchReceiver::TouchReceiver(int priority){
        
        _priority=priority;
        _enabled=true;
        
    }
    
    void TouchReceiver::setEnabled(bool enabled){
    
        _enabled=enabled;
    }
    
    
    bool TouchReceiver::isEnabled(){
    
        return _enabled;
        

    }
    
    
    void TouchReceiver::touchBegan(TouchEvent* event){
    
        if(touchBeganCallback) touchBeganCallback(event);
    
    }
    
    void TouchReceiver::touchMoved(TouchEvent* event){
    
        if(touchMovedCallback) touchMovedCallback(event);
    
    }
    
    void TouchReceiver::touchEnded(TouchEvent* event){
    
        if(touchEndedCallback) touchEndedCallback(event);
    
    }
    
    void TouchReceiver::mouseWheel(TouchEvent* event){
        
        if(mouseWheelCallback) mouseWheelCallback(event);
        
    }
    
    TouchDispenser::TouchDispenser(){
    
        _mouseEvent._isMouse=true;
        _mouseEvent._isDragging=false;
    
    }

    void TouchDispenser::touchBegan(Vec2 position, bool isMouse){
        
        if (isMouse) {
            
            _mouseEvent._startLocation=position;
            _mouseEvent._location=position;
            _mouseEvent._isDragging=true;
            
            for (int i=0; i<_receiver.size(); i++) {
                
                _receiver[i]->touchBegan(&_mouseEvent);
                
            }
            
            return;
            
        }
    
        TouchEvent touch;
        touch._location=position;
        touch._startLocation=position;
        touch._previousLocation=position;
        touch._touchID=(int) _activeTouches.size();
        
        _activeTouches.push_back(touch);

        
        for (int i=0; i<_receiver.size(); i++) {
            
            if(!_receiver[i]->isEnabled()) continue;
            _receiver[i]->touchBegan(&touch);
            
        }
        
    }
    
    void TouchDispenser::mouseWheel(Vec2 position, bool isMouse){
    
        for (int i=0; i<_receiver.size(); i++) {
            
            _mouseEvent._location=position;

            _receiver[i]->mouseWheel(&_mouseEvent);
            
        }
    
    }
    
    void TouchDispenser::mouseMovedRelative(Vec2 offset, bool isMouse){
    
        if (isMouse) {
            
            _mouseEvent._relativeMovement=offset;
            
            for (int i=0; i<_receiver.size(); i++) {
                
                if(!_receiver[i]->isEnabled()) continue;
                _receiver[i]->touchMoved(&_mouseEvent);
                
            }
            
            return;
            
        }

    
    }

    
    void TouchDispenser::touchMoved(Vec2 position, bool isMouse){
    
        if (isMouse) {
            
            _mouseEvent._location=position;
            
            
            for (int i=0; i<_receiver.size(); i++) {
                
                if(!_receiver[i]->isEnabled()) continue;
                _receiver[i]->touchMoved(&_mouseEvent);
                
            }
            
            _mouseEvent._previousLocation=position;

            return;
            
        }
        
        TouchEvent touch;
        double minDistance=-1;
        for (int i=0; i<_activeTouches.size(); i++) {
            
            if(minDistance==-1 || minDistance>_activeTouches[i]._location.distance(position)){
                
                minDistance=_activeTouches[i]._location.distance(position);
                touch=_activeTouches[i];
                
            }
            
        }
        
        touch._location=position;
      
        for (int i=0; i<_receiver.size(); i++) {
            
            _receiver[i]->touchMoved(&touch);
            
        }
        
        touch._previousLocation=position;

    }
    
    void TouchDispenser::touchEnded(Vec2 position, bool isMouse){
        
        if (isMouse) {
            
            _mouseEvent._location=position;
            _mouseEvent._isDragging=false;
            
            for (int i=0; i<_receiver.size(); i++) {
                
                if(!_receiver[i]->isEnabled()) continue;
                _receiver[i]->touchEnded(&_mouseEvent);
                
            }
            
            return;
            
        }
        
        TouchEvent touch;
        double minDistance=-1;
        for (int i=0; i<_activeTouches.size(); i++) {
            
            if(minDistance==-1 || minDistance>_activeTouches[i]._location.distance(position)){
                
                minDistance=_activeTouches[i]._location.distance(position);
                touch=_activeTouches[i];
                
            }
            
            
        }
        
        touch._location=position;

        for (int i=0; i<_receiver.size(); i++) {
            
            _receiver[i]->touchEnded(&touch);
            
        }
        
        for (int i=0; i<_activeTouches.size(); i++) {
            
            if(_activeTouches[i]._touchID==touch._touchID){
                
                _activeTouches.erase(_activeTouches.begin()+i);
                break;
                
            }
            
            
        }

        
    }
    

    void TouchDispenser::addReceiver(TouchReceiver* receiver){
        
        _receiver.push_back(receiver);
        
    }
    
    
    void TouchDispenser::removeReceiver(TouchReceiver* receiver){
        
        for (int i=0; i<_receiver.size(); i++) {
            
            if(_receiver[i]==receiver){
                
                _receiver.erase(_receiver.begin()+i);
                return;
                
            }
            
        }
        
        
    }
    
    
    
}