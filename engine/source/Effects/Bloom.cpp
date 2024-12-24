

#include "Bloom.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {
    
Bloom::Bloom(const Vec2& resolution, int maxSubBlooms){
    
    _gloomShader= ShaderModule::get("sge/shader/post/Bloom.glsl");
    _blurShader= ShaderModule::get("sge/shader/post/Blur.glsl");
    
    _resolution= resolution;
    _maxSubBlooms=maxSubBlooms;
 
    resolutions[0].set(resolution.x, resolution.y);
    resolutions[1].set(resolution.x*0.5, resolution.y*0.5);
    resolutions[2].set(resolution.x*0.25, resolution.y*0.25);
    resolutions[3].set(resolution.x*0.125, resolution.y*0.125);
    
    for (int i=0; i<_maxSubBlooms; i++) {
        
        _downsamples[i]= FrameBuffer::create(resolutions[i].x,resolutions[i].y, 0, 0, 0);
        RenderTarget* rt1= RenderTarget::createColorTarget(resolutions[i], TextureFormat::RGB, DataType::UNSIGNED_BYTE, 0);

        _downsamples[i]->attachRenderTarget(rt1);

        _downsamples[i]->setClearColor(Color::black);
        _downsamples[i]->clear(1, 1, 1);
        
        rt1->getTexture()->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
        rt1->getTexture()->setMagFilter(TextureFilter::LINEAR);
        rt1->getTexture()->setMinFilter(TextureFilter::LINEAR);
        
    }
    
    for (int i=0; i<_maxSubBlooms; i++) {
        
        _downsamplesHalfBlur[i]= FrameBuffer::create(resolutions[i].x, resolutions[i].y, 0, 0, 0);
        RenderTarget* rt1= RenderTarget::createColorTarget(resolutions[i], TextureFormat::RGB, DataType::UNSIGNED_BYTE, 0);
        
        _downsamplesHalfBlur[i]->attachRenderTarget(rt1);
        
        _downsamplesHalfBlur[i]->setClearColor(Color::black);
        _downsamplesHalfBlur[i]->clear(1, 1, 1);
        
        rt1->getTexture()->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
        rt1->getTexture()->setMagFilter(TextureFilter::LINEAR);
        rt1->getTexture()->setMinFilter(TextureFilter::LINEAR);
        
    }
    
    
    _finalBuffer= FrameBuffer::create(_resolution.x, _resolution.y, 0, 0, 0);
    RenderTarget* rt1= RenderTarget::createColorTarget(_resolution, TextureFormat::RGB, DataType::UNSIGNED_BYTE, 0);
    _finalBuffer->attachRenderTarget(rt1);
    _finalBuffer->setClearColor(Color::black);
    _finalBuffer->clear(1, 1, 1);
    rt1->getTexture()->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
    rt1->getTexture()->setMagFilter(TextureFilter::LINEAR);
    rt1->getTexture()->setMinFilter(TextureFilter::LINEAR);

    _blurShader->getGlobalShaderState()->setUniform1f("radius", 5);
    _blurShader->getGlobalShaderState()->setUniform1f("sampleNum", 5);
    
}
    
void Bloom::setThreshold(float value){

    _treshhold=value;
    _gloomShader->getGlobalShaderState()->setUniform1f("u_threshold", _treshhold);

}

Bloom::~Bloom(){}

void Bloom::renderInTexture(Texture* texture){
    
    // Downsample
    _compositor.compose(texture, _downsamples[0], BlendFunc::NORMAL, _gloomShader);
    
    for (int i=0; i<_maxSubBlooms-1; i++) {
        
        _compositor.compose(_downsamples[i]->getRenderTarget(0)->getTexture(), _downsamples[i+1], BlendFunc::NORMAL, NULL);
        
    }
    
    //Blur Horizontal
    _blurShader->getGlobalShaderState()->setUniform2f("dir", Vec2(1, 0));

    for (int i=0; i<_maxSubBlooms; i++) {
        
        _blurShader->getGlobalShaderState()->setUniform2f("resolution", resolutions[i]);

        _compositor.compose(_downsamples[i]->getRenderTarget(0)->getTexture(), _downsamplesHalfBlur[i], BlendFunc::NORMAL, _blurShader);
        
    }

    
    //Blur Vertical
    _blurShader->getGlobalShaderState()->setUniform2f("dir", Vec2(0, 1));

    for (int i=0; i<_maxSubBlooms; i++) {
        
        _blurShader->getGlobalShaderState()->setUniform2f("resolution", resolutions[i]);

        _compositor.compose(_downsamplesHalfBlur[i]->getRenderTarget(0)->getTexture(), _downsamples[i], BlendFunc::NORMAL, _blurShader);
        
    }
    
    
    //Combine
    glBlendEquation(GL_MAX);
    
    _finalBuffer->clear(1, 0, 0);
    for (int i=0; i<_maxSubBlooms; i++) {
        
        _compositor.compose(_downsamples[i]->getRenderTarget(0)->getTexture(), _finalBuffer, BlendFunc::NORMAL, NULL, 1);

    }
   
    glBlendEquation(GL_FUNC_ADD);

    
    
}

Texture* Bloom::getTexture(){
    
    if(!_finalBuffer) return NULL;
    return _finalBuffer->getRenderTarget(0)->getTexture();

}

}