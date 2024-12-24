

#ifndef SGENGINE_RENDERTARGET_H
#define SGENGINE_RENDERTARGET_H

#include <stdio.h>

#include "SBase.h"
#include "Texture.h"

namespace sge{
    
    enum RenderTargetType{
    
        RENDERTARGET_TYPE_COLOR=0,
        RENDERTARGET_TYPE_DEPTH=1,
        RENDERTARGET_TYPE_STENCIL=2
        
    };
    
    class RenderTarget{
        
        friend GraphicDevice;
        friend GraphicDeviceOpenGL;
        friend class FrameBuffer;
        
    private:
        
        RenderTarget(const char* id);
        ~RenderTarget();
        
        RenderTarget& operator=(const RenderTarget&);
        
        std::string _id;
        Texture* _texture;
        SUint _textureTarget;
        SUint _index;
        
        FrameBuffer* _framebuffer;
        
    public:
        
        void setIndex(unsigned int index);
        
        static RenderTarget* createColorTarget(Vec2 size, SUint internalFormat, SUint dataType ,SUint index);
        static RenderTarget* createDepthTarget(Vec2 size, SUint internalFormat);
        static RenderTarget* createStencil(Vec2 size, SUint internalFormat);

        static RenderTarget* create(const char* id, Texture* texture);
        static RenderTarget* getRenderTarget(const char* id);
        
        const char* getId() const;
        Texture* getTexture() ;
        
        void setSize(const Vec2& size);
    
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        
        void setTextureTarget(SUint textureTarget);
        SUint getTextureTarget();
        
        RenderTargetType _renderTargetType;
       
    };
    
}



#endif