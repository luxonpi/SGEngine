

#include "FrameBuffer.h"
#include "Director.h"

#include "glInclude.h"

namespace sge {
    
    bool FrameBuffer::initialized=false;
    
    // Fetch Gl Informations
    void FrameBuffer::initialize(){
        
        #ifndef MOBILE_TARGET
        GLint val;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &val);
        _maxRenderTargets = (unsigned int)std::max(1, val);
        #else
        _maxRenderTargets = 1;
        #endif
        
        checkRenderError();
        initialized=true;
    
    }
    
    std::vector<FrameBuffer*> FrameBuffer::_framebufferStack;
    
    unsigned int FrameBuffer::_maxRenderTargets = 0;
    
    FrameBuffer* FrameBuffer::_defaultBuffer=NULL;
    
    FrameBuffer* FrameBuffer::getDefaultBuffer(){

        if(!_defaultBuffer){
        
            _defaultBuffer= Director::getInstance()->getGraphicDevice()->getScreenFrameBuffer();
            _defaultBuffer->bind();
    
        }
        
        checkRenderError();
        return _defaultBuffer;
    
    }
    
    unsigned int FrameBuffer::getID(){
    
        return _fboID;
    
    }
    
    // Creating
    FrameBuffer::FrameBuffer(int w, int h){
    
        _width=w;
        _height=h;
        _prevDepth=true;
        _renderTargetCount=1;
 
    }
    
    FrameBuffer* FrameBuffer::create(int width, int height, SInt colorAttachment,  SInt depthAttachment,  SInt stencilAttachment){
    
        if(!initialized) initialize();

        // Frame can not be zero sized
        assert(width > 0 &&  height > 0);

        RenderTarget* renderTarget = NULL;

        // Create the frame buffer
        FrameBuffer* frameBuffer = new FrameBuffer(width, height);
        Director::getInstance()->getGraphicDevice()->generateFramebuffer(frameBuffer);
    
        frameBuffer->_depthTarget=NULL;
        frameBuffer->_stencilTarget=NULL;
    
        // Create the render target array for the new frame buffer
        frameBuffer->_renderTargets.resize(_maxRenderTargets);
        for (int i=0; i<_maxRenderTargets; i++) {
            frameBuffer->_renderTargets[i]=NULL;
        }
    
        frameBuffer->bind();
        
        // Create a default RenderTarget with same ID.
        if(colorAttachment!=0){

            renderTarget = RenderTarget::createColorTarget(Vec2(width, height), colorAttachment, DataType::UNSIGNED_BYTE, 0);
            frameBuffer->attachRenderTarget(renderTarget);
        
        }else{
        
#ifdef no_mobile
            glDrawBuffer(GL_NONE); // No color buffer is drawn to.
        
#endif
        
            glReadBuffer(GL_NONE);
        }
        
        
        if(stencilAttachment!=0){
            
            RenderTarget* str= RenderTarget::createStencil(Vec2(width, height), stencilAttachment);
            frameBuffer->attachRenderTarget(str);
        
        }else if(depthAttachment!=0){
        
            RenderTarget* dtr= RenderTarget::createDepthTarget(Vec2(width, height), depthAttachment);
            frameBuffer->attachRenderTarget(dtr);
            
        }
    
       
        
        if(colorAttachment!=0 || depthAttachment!=0 || stencilAttachment!=0)
        Director::getInstance()->getGraphicDevice()->checkFrameBufferStatus(frameBuffer);
        
        frameBuffer->unbind();
        checkRenderError();
        
        return frameBuffer;
    
    }
    
    // Clearing
    void FrameBuffer::clear(bool color, bool depth, bool stencil){
        
        checkRenderError();

        bind();
        Director::getInstance()->getGraphicDevice()->clearFrameBuffer(this, color, depth, stencil);
        unbind();
        
        checkRenderError();
        
    }
    
    void FrameBuffer::setClearColor(const Color& color){
        
        _clearColor.r=color.r;
        _clearColor.g=color.g;
        _clearColor.b=color.b;
        _clearColor.a=color.a;
    }
    
    // Attaching
    void FrameBuffer::attachRenderTarget(RenderTarget* target){
    
        if(!target) assert(0);
        
        target->_framebuffer=this;
        if(target->_renderTargetType==RENDERTARGET_TYPE_COLOR){
            
            if(target->_index >= _maxRenderTargets) return;

            if(target!=_renderTargets[target->_index]){
            
                // Release our reference to the current RenderTarget at this index.
                if (_renderTargets[target->_index]){
                    
                    delete _renderTargets[target->_index];
                    _renderTargets[target->_index]=NULL;
                    
                    _renderTargetCount--;
                }
        
                _renderTargets[target->_index] = target;
        
                _renderTargetCount++;
            }
            
        }else if (target->_renderTargetType==RENDERTARGET_TYPE_DEPTH){
        
            _depthTarget=target;
        
        }else if (target->_renderTargetType==RENDERTARGET_TYPE_STENCIL){
            
            _stencilTarget=target;
            _depthTarget=target;

        }
        
        
        bind();
        glReadBuffer(GL_COLOR_ATTACHMENT0);

        Director::getInstance()->getGraphicDevice()->setRenderTargetToFramebuffer(this, target);
        Director::getInstance()->getGraphicDevice()->checkFrameBufferStatus(this);

        // Restore the FBO binding
        unbind();
        
        checkRenderError();
        
    }
    
    void FrameBuffer::removeRenderTarget(RenderTarget* target){

        error("Remove render target not implemented yet");
        checkRenderError();
        
    }

    
    // Getter
    RenderTarget* FrameBuffer::getRenderTargetDepth(){
    
        return _depthTarget;
    
    }
    
    RenderTarget* FrameBuffer::getRenderTargetStencil(){
    
        return _stencilTarget;
    
    }
    
    RenderTarget* FrameBuffer::getRenderTarget(int index){
    
        if(index >= _maxRenderTargets) return NULL;
        return _renderTargets[index];

    }
    


    // Binding
    void FrameBuffer::bind(){
    
        if(FrameBuffer::_framebufferStack.size()!=0 && FrameBuffer::_framebufferStack.back()==this) return;
    
        FrameBuffer::_framebufferStack.push_back(this);
        
        
        if(!_depthTarget && this!=_defaultBuffer){
            
            GLboolean depth;
            glGetBooleanv(GL_DEPTH_TEST, &depth);
            _prevDepth=depth;
            
            glDisable(GL_DEPTH_TEST);
            
        }
        
        Director::getInstance()->getGraphicDevice()->bindFrameBuffer(this);
        Director::getInstance()->getGraphicDevice()->setViewPort(0, 0, _width, _height);
        
        
        #ifdef MULTIPLE_RENDER_TARGETS
        
        if(_renderTargetCount>1){
            
            std::vector<GLenum> buffers;
            
            for(int i=0; i<_renderTargetCount; i++){
            
                if(_renderTargets[i])
                buffers.push_back(GL_COLOR_ATTACHMENT0+i);
            
            }
            
            glDrawBuffers((int) buffers.size(), &buffers[0]);
        
        }

        #endif

        if(_renderTargetCount==0){
            
            glDrawBuffers(0, GL_NONE);
            glReadBuffer(GL_NONE);

        }

        
        checkRenderError();

    }


    void FrameBuffer::unbind(){
    
        if(!_depthTarget){
            
            if(_prevDepth) glEnable(GL_DEPTH_TEST);
            
        }

        
        for (int i=0; i<FrameBuffer::_framebufferStack.size(); i++) {
        
            if(FrameBuffer::_framebufferStack.at(i)==this){
            
                FrameBuffer::_framebufferStack.erase(FrameBuffer::_framebufferStack.begin()+i);
                break;
            
            }
        
        }
    
    
        if(FrameBuffer::_framebufferStack.size()>0){
    
            FrameBuffer* fbo=FrameBuffer::_framebufferStack.back();
            fbo->bind();
        
        }else{
            
            Director::getInstance()->getGraphicDevice()->bindFrameBuffer(_defaultBuffer);
    
        }

    }

    void FrameBuffer::setSize(int w, int h){
 
        _height=h;
        _width=w;
        
        bind();
      
        for(int i=0; i<_renderTargets.size(); i++){
            
            if(_renderTargets[i]) _renderTargets[i]->setSize(Vec2(w, h));
            
        }
  
        unbind();

    
    }
    
    float FrameBuffer::getWidth(){
    
        return _width;
    }
    
    
    float FrameBuffer::getHeight(){

        return _height;
    }

    const Color& FrameBuffer::getClearColor(){
    
        return _clearColor;
    
    
    }

    FrameBuffer::~FrameBuffer(){
    
        for (int i=0; i<FrameBuffer::_framebufferStack.size(); i++) {
        
            if(FrameBuffer::_framebufferStack.at(i)==this){
        
                FrameBuffer::_framebufferStack.erase(FrameBuffer::_framebufferStack.begin()+i);
                break;
            
            }
        
        }
    
        Director::getInstance()->getGraphicDevice()->releaseFramebuffer(this);
        
    }

    
}
