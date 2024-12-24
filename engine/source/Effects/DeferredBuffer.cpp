

#include "DeferredBuffer.h"
#include "Director.h"

namespace sge {

DeferredBuffer::DeferredBuffer(const std::string& moduleFile,const Vec2& resolution){
    
    _resolution=resolution;
//    _shaderModuleDeferred= ShaderModule::createFromFile(moduleFile);
//    _shaderModuleDeferred->setConfigID("vertex");

    _positionTarget= RenderTarget::createColorTarget(Vec2(resolution.x,  resolution.y), TextureFormat::RGB16F, DataType::FLOAT, 2);
    _normalTarget= RenderTarget::createColorTarget(Vec2(resolution.x,  resolution.y), TextureFormat::RGB, DataType::FLOAT, 1);
    _glossTarget= RenderTarget::createColorTarget(Vec2(resolution.x,  resolution.y), TextureFormat::RGB, DataType::UNSIGNED_BYTE, 3);
    
    
    _normalTarget->getTexture()->setMinFilter(TextureFilter::NEAREST);
    _normalTarget->getTexture()->setMagFilter(TextureFilter::NEAREST);
    
    _positionTarget->getTexture()->setMinFilter(TextureFilter::NEAREST);
    _positionTarget->getTexture()->setMagFilter(TextureFilter::NEAREST);
    
    _glossTarget->getTexture()->setMinFilter(TextureFilter::NEAREST);
    _glossTarget->getTexture()->setMagFilter(TextureFilter::NEAREST);
    
    _buffer= FrameBuffer::create(resolution.x, resolution.y, TextureFormat::RGBA16F, TextureFormat::DEPTH16, 0);
    
    _buffer->attachRenderTarget(_glossTarget);
    _buffer->attachRenderTarget(_positionTarget);
    _buffer->attachRenderTarget(_normalTarget);
    _buffer->setClearColor(Color::clear);
    _buffer->clear(true,true,true);
    
    _camera2d= Camera::create2D(resolution.x, resolution.y);

}
    
DeferredBuffer::~DeferredBuffer(){
    
    
}
    
void DeferredBuffer::clear(){
    
    _buffer->clear(true,true,false);


}
    
FrameBuffer* DeferredBuffer::getBuffer(){
    
    return _buffer;

}
    
void DeferredBuffer::renderInLayer(RenderLayer* layer, Camera* camera){
    
    Renderer* renderer= Director::getInstance()->getRenderer();
    renderer->renderLayer(layer, _buffer, camera, "DEFERRED_RENDERING");

}

Texture* DeferredBuffer::getNormalTexture(){
        
    return _buffer->getRenderTarget(1)->getTexture();
    
}
    
Texture* DeferredBuffer::getPositionTexture(){
    
    return _buffer->getRenderTarget(2)->getTexture();

}
    
Texture* DeferredBuffer::getGlossTexture(){
        
    return _buffer->getRenderTarget(3)->getTexture();
        
}
    

    
Texture* DeferredBuffer::getDepthTexture(){
    
    return _buffer->getRenderTargetDepth()->getTexture();


}
    
Texture* DeferredBuffer::getColorTexture(){
    
    return _buffer->getRenderTarget(0)->getTexture();

}
    

    

}
