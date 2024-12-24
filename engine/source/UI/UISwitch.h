

#ifndef SGENGINE_UISWITCH_H
#define SGENGINE_UISWITCH_H

#include <stdio.h>
#include <map>

#include "SBase.h"

#include "View.h"
#include "Label.h"
#include "TouchDispenser.h"

namespace sge {
    
    class UISwitch: public View{
        
    protected:
        
        bool _isOn;
        
        std::function<void(UISwitch*)> _changeCallback;
        
        View* _bg;
        View* _bg2;
        View* _button;
        
        UISwitch();
        ~UISwitch();
        
        void touchBegan(sge::TouchEvent* event);
        void touchMoved(sge::TouchEvent* event);
        void touchEnded(sge::TouchEvent* event);
        
    public:
        
        bool isOn();
        void setOn(bool on);
        
        static UISwitch* create();
        
        void setCallback(std::function<void(UISwitch*)> callback);
        
        
    };
    
}

#endif
