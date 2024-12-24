

#ifndef SGENGINE_RENDERSTATE_H
#define SGENGINE_RENDERSTATE_H

#include <stdio.h>
#include "Transform.h"
#include "ShaderState.h"

namespace sge {

    class Camera;

class RenderState{
    
private:
    
  
    
public:
    
    // States
    bool cullFaceEnabled;
    bool depthTestEnabled;
    bool depthWriteEnabled;
    bool blendEnabled;
    bool stencilTestEnabled;
    
    SUint depthFunction;
    SUint cullFaceSide;
    SUint stencilFunction;
    SUint drawMode;

    BlendFunc blendFunc;
    
    SUint stencilWrite;
    SUint stencilFunctionMask;
    SUint stencilFunctionRef;
    
    long bits;
 
    RenderState();
    RenderState(RenderState* copy);
    
    Mat4 model;
    Mat4 view;
    Mat4 projection;
    
    ShaderState* shaderState;
    Camera* camera;
    
    
};
    
}

#endif 
