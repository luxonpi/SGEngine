

#ifndef SGENGINE_ARMATUREANIMATIONCONTROLLER_H
#define SGENGINE_ARMATUREANIMATIONCONTROLLER_H

#include <stdio.h>
#include "ModelArmature.h"
#include "ArmatureAnimation.h"
#include <unordered_map>

namespace sge {
    
    class ControlledAnimation{

    public:
    
        ArmatureAnimation* animation;
        bool loop;
        float time;
        float speed;
    };

    
    class ArmatureAnimationController{


    private:
        ControlledAnimation* runningAnimation;
        float _lastFrame;
        
        std::map<unsigned int, ControlledAnimation*> _channels;
    
    public:
    
        ArmatureAnimationController();
    
        void update();
    
        bool isRunningAnimation();
        void setToArmature(ModelArmature* armature);
        
        void setSpeed(float speed);
        
        void playAnimation(ArmatureAnimation* animation, unsigned int channel, float speed, bool loop);
        void stopAnimationOnChannel(unsigned int channel);
    
    };
    
}

#endif