

#ifndef SGENGINE_GLOOM_H
#define SGENGINE_GLOOM_H

#include <stdio.h>
#include "FrameBuffer.h"
#include "Shader.h"
#include "SCamera.h"
#include "Sprite.h"
#include "Compositor.h"

namespace sge {
    
class Bloom{

private:
    
    Compositor _compositor;
    Vec2 _resolution;

    FrameBuffer* _downsamples[4];
    FrameBuffer* _downsamplesHalfBlur[4];

    Vec2 resolutions[4];
    
    
    
    FrameBuffer* _finalBuffer;

    
    float _treshhold;
    ShaderModule* _gloomShader;
    ShaderModule* _blurShader;

    int _maxSubBlooms;
    
public:

    Bloom(const Vec2& resolution, int maxSubBlooms);
    ~Bloom();

    void renderInTexture(Texture* texture);
    void setThreshold(float value);
    
    Texture* getTexture();
    
};
    
}

#endif