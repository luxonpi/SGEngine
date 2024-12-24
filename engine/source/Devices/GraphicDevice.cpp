

#include "GraphicDevice.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "VertexArrayObject.h"
#include "GraphicDeviceDefines.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"


namespace sge {
    
  
    FrameBuffer* GraphicDevice::getScreenFrameBuffer(){
       
        return _screenFramebuffer;
        
    }
    
    
    GraphicDevice::GraphicDevice(){
        
        _screenFramebuffer=NULL;
        
    }
    
    GraphicDevice::~GraphicDevice(){
        
        
    }
    
    void GraphicDevice::unbindBuffer(SUint bufferType){
    
    
    }

    
    void GraphicDevice::bindShader(Shader* shader){
    
    
    }

    
    void GraphicDevice::startUp(){}
    

    // Shader
    void GraphicDevice::generateShader(Shader* shader){
    
        
    }
    
    void GraphicDevice::releaseShader(Shader* shader){}
    void GraphicDevice::attachSource(Shader* shader, const std::string& source, const SUint& type){}
    void GraphicDevice::bindAttribLocation(Shader* shader, const SUint& location, const std::string& name){}
    void GraphicDevice::linkShader( Shader* shader ){}
    
    // States
    void GraphicDevice::setCullFace(const SUint& cullface){
    
    }

    void GraphicDevice::setBlendFunc(const BlendFunc& blendFunc){
        
    
    }
   
    void GraphicDevice::setBlendingEnabled(const bool& enabled){
    
    
    }
    
    void GraphicDevice::setDepthFunc( const SUint& depthFunc ){
    
    
    }
    
    void GraphicDevice::setDepthWritingEnabled(const bool& enabled){
    
    
    }
    
    void GraphicDevice::setDepthTestEnabled(const bool& enabled){
    
    
    }
    
    
    // Data
    
    void GraphicDevice::bindVertexBuffer(VertexBuffer* buffer){
    
    }
    
    void GraphicDevice::bufferVertexBufferData(VertexBuffer* buffer){
    
    }
    
    void GraphicDevice::generateVertexBuffer(VertexBuffer* buffer){
    
    }
    
    void GraphicDevice::releaseVertexBuffer(VertexBuffer* buffer){
    
    }
    
    void GraphicDevice::generateVertexArrayObject(VertexArrayObject* vao){
    
    }
    
    void GraphicDevice::releaseVertexArrayObject(VertexArrayObject* vao){
    
    }
    
    void GraphicDevice::bindVertexArrayObject(VertexArrayObject* vao){
    
    }
    
    void GraphicDevice::bindTexture(Texture* texture, const SUint& location){
    
    
    }
    
    void GraphicDevice::generateTexture(Texture* texture){
    
    
    }

    void GraphicDevice::releaseTexture(Texture* texture){
    
    }
    
    void GraphicDevice::setTextureData(Texture* texture, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data){
    
    
    }
    
    void GraphicDevice::setCubeMapTextureData(Texture* texture, SUint side, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data){
    
    }
    
    void GraphicDevice::setTextureFilter(Texture* texture){
    
    
    }
    
    void GraphicDevice::setTextureWrap(Texture* texture){
    
    
    }

    //Draw
    void GraphicDevice::drawElements(const SUint& drawType, const SUint& indicesCount, const void * indices){
    
    
    }

    void GraphicDevice::drawArraysInstanced(const SUint& drawType,  const SUint& first,  const SUint& count, const SUint& instancecount){
    
    
    }

    void GraphicDevice::setVertexAttributeDivisor(const SUint& location, const SUint& divisor){
    
    
    }
    
    void GraphicDevice::enableVertexAttributeArray(const SUint& location){}
    void GraphicDevice::setVertexAttributePointer(const SUint& index, const SInt& size, const SUint& dataType, const bool& normalized, const SUint& stride, SInt pointer){}

    void GraphicDevice::clearFrameBuffer(FrameBuffer* framebuffer, bool color, bool depth, bool stencil){}

    void GraphicDevice::generateFramebuffer(FrameBuffer* framebuffer){
    
    
    }
    
    void GraphicDevice::releaseFramebuffer(FrameBuffer* framebuffer){
    
    }
    
    void GraphicDevice::bindFrameBuffer(FrameBuffer* framebuffer){
    
        
    }
    
    void GraphicDevice::checkFrameBufferStatus(FrameBuffer* framebuffer){
    
    
    }

    void GraphicDevice::setViewPort(SInt x, SInt y, SInt w, SInt h){
    
    
    }

    void GraphicDevice::setRenderTargetToFramebuffer(FrameBuffer* buffer, RenderTarget* renderTarget){
    
    
    }
    
    SInt GraphicDevice::getUniformLocation(Shader* shader, const std::string& name){
    
        return 0;
    
    }

    
    
    
}