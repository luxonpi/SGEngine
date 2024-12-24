

#include "SSAO.h"
#include "Director.h"



namespace sge {
    
    float lerp(float t, float a, float b){
        return (1-t)*a + t*b;
    }
    
    SSAO::SSAO(float width, float height){
        
        _ssaoShader= ShaderModule::get("sge/shader/post/SSAO.glsl");
//        _blurShader= Shader::getShaderFromModules({"support/shader/vert/VertexView.glsl", "assets/shader/post/SSAOBlur.glsl"});
//        
        //_blurShader->getState()->setUniform2f("u_texelSize", Vec2(1.0/width, 1.0/height));
        
        
        
        std::vector<Vec3> ssaoNoise;
        for (SUint i = 0; i < 16; i++)
        {
            Vec3 noise(
                            (rand()%200-100)/100.,
                            (rand()%200-100)/100.,
                            0.0f); 
            ssaoNoise.push_back(noise);
        }
        
//        
        _noiseTexture= Texture::create(4, 4, TextureFormat::RGB, TextureFormat::RGB16F, DataType::FLOAT, &ssaoNoise[0]);
        _noiseTexture->setMagFilter(TextureFilter::NEAREST);
        _noiseTexture->setMinFilter(TextureFilter::NEAREST);
//        
 
        
        Vec2 winS= Director::getInstance()->getWindowSize();
    
        _camera2d= Camera::create2D(width, height);
        
        _pass1= FrameBuffer::create(width, height, TextureFormat::RGB, 0, 0);
        _pass2= FrameBuffer::create(width, height,  TextureFormat::RED, 0, 0);
        _pass3= FrameBuffer::create(width, height,  TextureFormat::RED, 0, 0);

        _pass1->setClearColor(Color::black);
        _pass2->setClearColor(Color::black);
        _pass3->setClearColor(Color::black);
        
        _pass1->getRenderTarget(0)->getTexture()->setMagFilter(TextureFilter::LINEAR);
        _pass1->getRenderTarget(0)->getTexture()->setMinFilter(TextureFilter::LINEAR);

        _pass2->getRenderTarget(0)->getTexture()->setMagFilter(TextureFilter::LINEAR);
        _pass2->getRenderTarget(0)->getTexture()->setMinFilter(TextureFilter::LINEAR);
        
        _pass3->getRenderTarget(0)->getTexture()->setMinFilter(TextureFilter::LINEAR);
        _pass3->getRenderTarget(0)->getTexture()->setMagFilter(TextureFilter::LINEAR);

        _resolution= Vec2(width, height);
        
        //	generate kernel:
        int kernelSize= 32;
        
        std::vector<Vec3> kernel;
        kernel.resize(kernelSize);

        for (int i = 0; i < kernelSize; ++i) {
            kernel[i] = Vec3(
                                   (rand()%200-100)/100.,
                                   (rand()%200-100)/100.,
                                   (rand()%100)/100.
                                   );
            kernel[i].normalize();
            
            kernel[i] *= float(rand()%100)/100.;

            
            float scale = (float)i / (float) kernelSize;
            kernel[i] *= lerp(0.1f, 1.0f, scale * scale);
            
    
        }

        _ssaoShader->getGlobalShaderState()->setUniformVec3Array("uKernelOffsets", kernel);
        _ssaoShader->getGlobalShaderState()->setUniform1i("uKernelSize", kernelSize);
    
        
    }
    
    SSAO::~SSAO(){
        
        
        
        
    }
    
    void SSAO::clear(){
        
        _pass1->clear(true,false,false);
        _pass2->clear(true,false,false);
        _pass3->clear(true,false,false);

    }
    
    void SSAO::render(DeferredBuffer* deferrredBuffer, Camera* camera){
        
        clear();
        
        _ssaoShader->getGlobalShaderState()->setUniformTexture("noiseTex", _noiseTexture, 5);

        _ssaoShader->getGlobalShaderState()->setUniformTexture("depthTex", deferrredBuffer->getDepthTexture(), 2);
        _ssaoShader->getGlobalShaderState()->setUniformTexture("normalTex", deferrredBuffer->getNormalTexture(), 3);
        _ssaoShader->getGlobalShaderState()->setUniformTexture("positionTex", deferrredBuffer->getPositionTexture(), 4);
        
        _ssaoShader->getGlobalShaderState()->setUniform2f("u_resolution", Vec2(deferrredBuffer->getBuffer()->getWidth(), deferrredBuffer->getBuffer()->getHeight()));
        
        Mat4 _worldNormalMatrix=camera->getViewMatrix();
        _worldNormalMatrix.inverse();
        _worldNormalMatrix.transpose();
     
        Mat4 proj= camera->getProjectionMatrix();
        _ssaoShader->getGlobalShaderState()->setUniform4m("u_ViewMat", &_worldNormalMatrix[0], false);

        
        _compositor.compose(NULL, _pass1, BlendFunc::NORMAL, _ssaoShader);
        
//        
//        _blurShader->setTexture(depth,  3, _blurShader->getUniformLocation( "depth"));
//
//        _compositor.compose(_pass1->getRenderTarget(0)->getTexture(), _pass2, BlendFunc::NORMAL, _blurShader);
//
//
//        _blurShader->getState()->setUniformTexture("depthText",depth, 3);
//
//        _blurShader->getState()->setUniform2f("dir", Vec2(1, 0));
//        _blurShader->getState()->setUniform2f("resolution", Vec2(_resolution.x*2, _resolution.y*2));
//        
//        _compositor.compose(_pass1->getRenderTarget(0)->getTexture(), _pass2, BlendFunc::NORMAL, _blurShader);
//        _blurShader->getState()->setUniform2f("dir", Vec2(0, 1));
//        
//        _pass3->clear(true, true, false);
//        _compositor.compose(_pass2->getRenderTarget(0)->getTexture(), _pass3, BlendFunc::NORMAL, _blurShader);
        
        
    }
    
    Texture* SSAO::getTexture(){
        
        return _pass1->getRenderTarget(0)->getTexture();
        
    }
    
}
