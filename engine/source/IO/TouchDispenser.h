

#ifndef SGENGINE_TOUCHDISPENSER_H
#define SGENGINE_TOUCHDISPENSER_H

#include <stdio.h>
#include <functional>
#include <vector>

#include "Vec2.h"
#include "TouchEvent.h"
#include "Dispenser.h"

namespace sge {
    
    class TouchReceiver{
        
    private:
        
        int _priority;
        bool _enabled;
        
    public:
        
        void setEnabled(bool enabled);
        bool isEnabled();
        
        std::function< void(TouchEvent*) > touchBeganCallback;
        std::function< void(TouchEvent*) > touchMovedCallback;
        std::function< void(TouchEvent*) > touchEndedCallback;
        std::function< void(TouchEvent*) > mouseWheelCallback;

        TouchReceiver(int priority);
      
        void touchBegan(TouchEvent* event);
        void touchMoved(TouchEvent* event);
        void touchEnded(TouchEvent* event);
        void mouseWheel(TouchEvent* event);

    };
    
    
    class TouchDispenser{
        
        
    private:
        std::vector<TouchReceiver*> _receiver;
        std::vector<TouchEvent> _activeTouches;
        
        TouchEvent _mouseEvent;

    public:
        TouchDispenser();
        
        void addReceiver(TouchReceiver* receiver);
        void removeReceiver(TouchReceiver* receiver);
        
        void touchBegan(Vec2 position, bool isMouse);
        void touchMoved(Vec2 position, bool isMouse);
        void touchEnded(Vec2 position, bool isMouse);
        void mouseWheel(Vec2 position, bool isMouse);
        void mouseMovedRelative(Vec2 offset, bool isMouse);

        
    };
    
}

#endif