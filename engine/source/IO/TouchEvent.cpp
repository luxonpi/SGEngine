

#include "TouchEvent.h"
#include "Director.h"

namespace sge {
    
    TouchEvent::TouchEvent(){
    
        _touchID=-1;
        _isDragging=true;
        _passToLowerPriorities=true;
        _isMouse=false;
        
    }
    
    TouchEvent::~TouchEvent(){}
    
    
//    Vec2 Touch::convertToNode(Node* node){
//        
//        Transformation b=node->getGlobalTransformation();
//        return Vec2(location.x-b.position.x, location.y-b.position.y);
//
//    }
    
    
  
    void TouchEvent::operator=(const TouchEvent& touch){
    
        _touchID=touch._touchID;
        _location=touch._location;
        _previousLocation=touch._previousLocation;
        _startLocation=touch._startLocation;
    
    }
    
    Vec2 TouchEvent::getRelativeMovement(){
        
        return _relativeMovement;
        
    }
    

    Vec2 TouchEvent::getPreviousLocation(){
    
       return _previousLocation;
    
    }
    
    Vec2 TouchEvent::getCurrentLocation(){

        return _location;

    }
    
    
    Vec2 TouchEvent::getStartLocation(){
    
        return _startLocation;
    
    }
    
    bool TouchEvent::isDragging(){
    
        return _isDragging;
        
    }
    
    bool TouchEvent::isMouse(){
    
        return _isMouse;
    
    }
    
}// Namespace end