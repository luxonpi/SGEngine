

#ifndef SGENGINE_SSAO_H
#define SGENGINE_SSAO_H

#include <stdio.h>
#include "FrameBuffer.h"
#include "Shader.h"
#include "RenderLayer.h"
#include "SCamera.h"
#include "Sprite.h"
#include "DeferredBuffer.h"
#include "View.h"
#include "Compositor.h"

namespace sge {
    
    class SSAO{
        
    private:
        
        Vec2 _resolution;
        
        FrameBuffer* _pass1;
        FrameBuffer* _pass2;
        FrameBuffer* _pass3;

        ShaderModule* _ssaoShader;
        Shader* _blurShader;
        
        Camera* _camera2d;
        Compositor _compositor;
        
        Texture* _noiseTexture;
        
        
       
    public:
        
        
        SSAO(float width, float height);
        ~SSAO();
        
        void clear();
        void render(DeferredBuffer* deferrredBuffer, Camera* camera);
        
        Texture* getTexture();
        
    };
    
}

#endif
