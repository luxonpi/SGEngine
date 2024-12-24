

#ifndef SGENGINE_TOUCHEVENT_H
#define SGENGINE_TOUCHEVENT_H

#include <stdio.h>
#include <vector>

#include "Vec2.h"

namespace sge {
    
    class TouchDispenser;
    
    class TouchEvent{
     
        friend TouchDispenser;
        
    private:
    
        int _touchID;
        Vec2 _previousLocation;
        Vec2 _startLocation;
        Vec2 _location;
        
        Vec2 _relativeMovement;
        
        bool _isDragging;
        bool _passToLowerPriorities;
        bool _isMouse;
        
    public:
        TouchEvent();
        ~TouchEvent();
        
        Vec2 getPreviousLocation();
        Vec2 getCurrentLocation();
        Vec2 getStartLocation();
        Vec2 getRelativeMovement();
        
        bool isDragging();
        bool isMouse();

        void operator=(const TouchEvent& touch);

        
    };
    

}


#endif 
