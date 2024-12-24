

#ifndef SGENGINE_MODELRIGGED_H
#define SGENGINE_MODELRIGGED_H

#include <stdio.h>

#include "Model.h"
#include "ModelArmature.h"
#include "ArmatureAnimationController.h"

namespace sge {
    
    class ModelRigged: public Model{

    private:
    
        ArmatureAnimationController _animationController;
        ModelArmature* _armature;
    
        unsigned int _frameCount;
        std::string _currentAnimationName;
    
    public:
    
        static ModelRigged* create(const std::string& file);
        ModelArmature* getArmature();
    
        std::string getCurrentAnimationName();
        void playAnimation(std::string name, float speed, bool loop);
        void playAnimationOnChannel(std::string name, float speed, bool loop, unsigned int channel);
        void setArmature(ModelArmature* armature);

        void stopAnimationOnChannel(unsigned int channel);
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

    };
    
}

#endif