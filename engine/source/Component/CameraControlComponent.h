

#ifndef SGENGINE_FLYOVERCAMERA_H
#define SGENGINE_FLYOVERCAMERA_H

#include <iostream>
#include "Node.h"
#include "SCamera.h"
#include "TouchDispenser.h"
#include "KeyboardDispenser.h"
#include "UpdateDispenser.h"
#include "Component.h"

#define PERSON_FIRST 0
#define PERSON_THIRD 1

namespace sge {
    
    class CameraControlComponent: public Component{
        
    protected:
        
        UpdateReceiver* _updateReceiver;
        KeyboardReceiver* _keyBoardReceiver;
        TouchReceiver* _touchReceiver;
        
        // Camera movements
        float _angleHorizontal;
        float _angleVertikal;
        
        Vec2 _mouseMomentum;
    
        // How fast does the entity move
        float _velocity;
        
        // Buttons pressed
        bool _forward;
        bool _backward;
        bool _left;
        bool _right;
        bool _up;
        bool _space;
        bool _down;
        bool _run;
        
        Vec2 _moveVec;
        
        float _cameraDistance;
        Vec2 _cameraOffset;

        bool _anglesLocked;
        
        // Is it third person or thirst person
        int _mode;
        
        virtual void setTypeName();
        
        Entity* _followEntity;
        
        
    public:
                
        CameraControlComponent();
        ~CameraControlComponent();
        
        void setCameraDistance(float distance);
        void setCameraOffset(sge::Vec2 offset);
        
        void setFollowEntity(Entity* followEntity);
        
        virtual void setEnabled(bool enabled);
        void setLockAngles(bool lock);
        
        void setVelocity(float velocity);
        
        bool isRunning();
        void setMode(int mode);
        
        // Registered Functions
        void update(float delta);
        
        void didReleaseKey(KeyEvent* event);
        void didPressKey(KeyEvent* event);
        
        void touchBegan(TouchEvent* event);
        void touchMoved(TouchEvent* event);
        void touchEnded(TouchEvent* event);
        
    };
    
}

#endif
