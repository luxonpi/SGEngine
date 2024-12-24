

#ifndef SGENGINE_DEFFEREDBUFFER_H
#define SGENGINE_DEFFEREDBUFFER_H

#include <stdio.h>
#include "FrameBuffer.h"
#include "Shader.h"
#include "Light.h"
#include "Sprite.h"
#include "ShadowMap.h"
#include "View.h"

namespace sge {
    
class DeferredBuffer{

private:
    
    ShaderModule* _shaderModuleDeferred;

    RenderTarget* _positionTarget;
    RenderTarget* _normalTarget;
    RenderTarget* _glossTarget;

    FrameBuffer* _buffer;
    
    Camera* _camera2d;
    
    Vec2 _resolution;
    
public:
    
    FrameBuffer* getBuffer();
    
    Texture* getColorTexture();
    Texture* getNormalTexture();
    Texture* getPositionTexture();
    Texture* getDepthTexture();
    Texture* getGlossTexture();

    DeferredBuffer(const std::string& moduleFile, const Vec2& resolution);
    ~DeferredBuffer();
    
    void clear();
    void renderInLayer(RenderLayer* layer, Camera* camera);
    

};

}

#endif
