

#ifndef Blur_H
#define Blur_H

#include <stdio.h>
#include "FrameBuffer.h"
#include "Shader.h"
#include "SCamera.h"
#include "Sprite.h"
#include "Compositor.h"

namespace sge {
    

class Blur{


public:
    Compositor _compositor;
    
    Vec2 _resolution;
    
    FrameBuffer* _pass1;
    FrameBuffer* _pass2;
    
    float _treshhold;
    Shader* _blurShader;
    
    
public:
    
    Blur(float width, float height);
    ~Blur();
    
    void clear();
    void renderInTexture(Texture* texture);
    
    Texture* getTexture();
	
};

}
#endif
