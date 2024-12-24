

#ifndef SGENGINE_COMPOSITOR_H
#define SGENGINE_COMPOSITOR_H

#include <stdio.h>
#include "View.h"
#include "FrameBuffer.h"

namespace sge {

class Compositor{

protected:
    
    View* _view;
    Camera* _camera;
    

public:
    
    Compositor();
    
    void compose(Texture* texture, FrameBuffer* buffer,const BlendFunc& blendfunc, ShaderModule* shaderModule, float opacity=1.0);

};
    
    
}

#endif