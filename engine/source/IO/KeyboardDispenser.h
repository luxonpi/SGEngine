

#ifndef SGENGINE_KEYBOARDDISPENSER_H
#define SGENGINE_KEYBOARDDISPENSER_H

#include <stdio.h>
#include <functional>
#include <vector>
#include "KeyEvent.h"
#include "Dispenser.h"

namespace sge {
    
    class KeyboardReceiver{
        
    private:
    
        int _priority;
        bool _enabled;
        
    public:
        
        std::function< void(KeyEvent*) > releaseCallback;
        std::function< void(KeyEvent*) > pressCallback;
        
        KeyboardReceiver(int priority);
        void keyReleased(KeyEvent* event);
        void keyPressed(KeyEvent* event);
        
        void setEnabled(const bool& enabled);
        bool isEnabled();

    };
    
    
    class KeyboardDispenser{
        
        
    private:
        std::vector<KeyboardReceiver*> _receiver;
        
    public:
        
        void addReceiver(KeyboardReceiver* receiver);
        void removeReceiver(KeyboardReceiver* receiver);
        
        void keyReleased(KeyEvent* event);
        void keyPressed(KeyEvent* event);
        
        
    };
    
}

#endif 