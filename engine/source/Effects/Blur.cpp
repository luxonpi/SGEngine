

#include "Blur.h"

#include "Director.h"

namespace sge {
    
    Blur::Blur(float width, float height){
        
//        ShaderModule* module=ShaderModule::createFromFiles(std::vector<std::string> {"support/shader/vert/VertexView.glsl", "support/shader/post/Blur.glsl"});
//        
//        _blurShader= ShaderModule::getShaderOfModules(std::vector<ShaderModule *>{module});
//        
//        _blurShader->getState()->setUniform1f("radius", 7);
//        _blurShader->getState()->setUniform1f("sampleNum", 7);
//        
//        _pass1= FrameBuffer::create(width, height, TextureFormat::RGBA, 0, 0);
//        _pass2= FrameBuffer::create(width, height, TextureFormat::RGBA, 0, 0);
//        
//        _pass1->setClearColor(Color::clear);
//        _pass2->setClearColor(Color::clear);
//        
//        _resolution= Vec2(width, height);
//        
//        _pass1->getRenderTarget(0)->getTexture()->setTextureWrap(TextureWrap::CLAMP);
//        _pass2->getRenderTarget(0)->getTexture()->setTextureWrap(TextureWrap::CLAMP);
//        
//        
//    }
//    
//    Blur::~Blur(){
//        
//        
//        
//        
//    }
//    
//    void Blur::clear(){
//        
//        _pass1->clear(true,false,false);
//        _pass2->clear(true,false,false);
//        
//    }
//    
//    void Blur::renderInTexture(Texture* texture){
//        
//        _blurShader->setUniform2f( 1, 0, _blurShader->getUniformLocation("dir"));
//        _blurShader->setUniform2f(_resolution.x, _resolution.y, _blurShader->getUniformLocation("resolution"));
//        
//        _compositor.compose(texture, _pass2, BlendFunc::NORMAL, _blurShader);
//        
//        _blurShader->setUniform2f( 0, 1, _blurShader->getUniformLocation("dir"));
//        _pass1->clear(true,false,false);
//        
//        _compositor.compose(_pass2->getRenderTarget(0)->getTexture(), _pass1, BlendFunc::NORMAL, _blurShader);
//        
//    }
//    
//    Texture* Blur::getTexture(){
//        
//        if(!_pass1) return NULL;
//        return _pass1->getRenderTarget(0)->getTexture();
//        
    }
    
}