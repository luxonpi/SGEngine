

#ifndef SGENGINE_UISLIDER_H
#define SGENGINE_UISLIDER_H

#include <stdio.h>
#include <map>

#include "SBase.h"

#include "View.h"
#include "Label.h"
#include "TouchDispenser.h"

namespace sge {
    
    class UISlider: public View{
        
    protected:
        
        bool _isDragging;
        
        std::function<void(UISlider*)> _changeCallback;
        
        View* _bg;
        View* _bg2;
        View* _button;
        
        float _minX;
        float _maxX;
        
        UISlider();
        ~UISlider();
        
        void touchBegan(sge::TouchEvent* event);
        void touchMoved(sge::TouchEvent* event);
        void touchEnded(sge::TouchEvent* event);
        
    public:
        
        float getValue();
        
        static UISlider* create();
        
        void setCallback(std::function<void(UISlider*)> callback);
        
        
    };
    
}

#endif
