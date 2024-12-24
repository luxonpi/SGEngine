

#ifndef SGENGINE_FRAMEBUFFER_H
#define SGENGINE_FRAMEBUFFER_H

#include "SBase.h"

#include "Texture.h"
#include "Color.h"
#include "RenderTarget.h"

namespace sge {
        
    class FrameBuffer{

        friend GraphicDevice;
        friend GraphicDeviceOpenGL;
        
    private:
    
        static std::vector<FrameBuffer*> _framebufferStack;
        static FrameBuffer* _defaultBuffer;
        
        static void initialize();
        static bool initialized;
        static unsigned int _maxRenderTargets;
    
        std::vector<RenderTarget*> _renderTargets;
        int _renderTargetCount;
    
        RenderTarget* _depthTarget;
        RenderTarget* _stencilTarget;

        int _width;
        int _height;

        Color _clearColor;
        bool _prevDepth;
    
        SUint _fboID;
    
        FrameBuffer(int w, int h);
        ~FrameBuffer();

    public:
        
        const Color& getClearColor();
        unsigned int getID();
    
        // Creating
        static FrameBuffer* getDefaultBuffer();
        static FrameBuffer* create(int width, int height, SInt colorAttachment,  SInt depthAttachment,  SInt stencilAttachment );
    
        // Clearing
        void setClearColor(const Color& color);
        void clear(bool color, bool depth, bool stencil);
    
        // Attaching
        void attachRenderTarget(RenderTarget* target);
        void removeRenderTarget(RenderTarget* target);

    
        // Binding
        void bind();
        void unbind();

        // Getter
        RenderTarget* getRenderTargetDepth();
        RenderTarget* getRenderTargetStencil();
        RenderTarget* getRenderTarget(int index);
        
        float getWidth();
        float getHeight();
    
        void setSize(int w, int h);

        // Statics
        static unsigned int getMaxRenderTargets();

    };

}

#endif
