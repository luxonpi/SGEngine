

#include "ExposureMeasurer.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {

    void ExposureMeasurer::initWithDimensions(float width, float height){
    
        _buffer[0]= FrameBuffer::create(width*0.5, height*0.5, TextureFormat::RGB16F, 0, 0);
        _buffer[1]= FrameBuffer::create(width*0.5, height*0.5, TextureFormat::RGB16F, 0, 0);

        _finalBuffer= FrameBuffer::create(2, 2, TextureFormat::RGB16F, 0, 0);
        
        _buffer[0]->setClearColor(Color(0, 0, 0, 0));
        _buffer[1]->setClearColor(Color(0, 0, 0, 0));
        
        _buffer[0]->getRenderTarget(0)->getTexture()->setMagFilter(TextureFilter::LINEAR);
        _buffer[0]->getRenderTarget(0)->getTexture()->setMinFilter(TextureFilter::LINEAR);

        _buffer[1]->getRenderTarget(0)->getTexture()->setMagFilter(TextureFilter::LINEAR);
        _buffer[1]->getRenderTarget(0)->getTexture()->setMinFilter(TextureFilter::LINEAR);


        _finalBuffer->setClearColor(Color(0, 0, 0, 0));
        
        initSize.set(width*0.5, height*0.5);

        _view= View::create(1, 1, Color::white);
        _view->setPosition(0, 0);
      //  _view->getRenderObject()->setDepthFunction(DepthFunc::ALWAYS);
        _view->getQuad()->setFlipUVVertical(true);
        
        _camera= Camera::create2D(100, 100);

    
    }
    
    ExposureMeasurer::ExposureMeasurer(){
    
    
    }
    
    ExposureMeasurer::~ExposureMeasurer(){
    
        
    
    }
    
    
    ExposureMeasurer* ExposureMeasurer::create(float width, float height){
    
        ExposureMeasurer* expo= new ExposureMeasurer();
        expo->initWithDimensions(width, height);
        return expo;
    
    }
    
    float ExposureMeasurer::getExposure(Texture* texture){
        
        Vec2 size= Vec2(initSize.x, initSize.y);
        
        _buffer[0]->clear(true, 0, 0);
        _buffer[1]->clear(true, 0, 0);

        _finalBuffer->clear(true, 0, 0);
        _buffer[0]->setSize(size.x, size.y);
        _buffer[1]->setSize(size.x, size.y);

        
        _camera->setWindowsSize(size.x,size.y);
        _view->setContentSize(size);
        _view->setTexture(texture);
        Director::getInstance()->getRenderer()->renderObject(_view->getRenderObject(), _buffer[0], _camera);
        
        int targetBuffer=1;
        
        for (int i=0; i<10 && size.x>=4; i++) {
            
            size*=0.5;
            _buffer[targetBuffer]->setSize(size.x, size.y);
            
            _camera->setWindowsSize(size.x,size.y);
            _view->setTexture(_buffer[!targetBuffer]->getRenderTarget(0)->getTexture());
            _view->setContentSize(size);
        
            Director::getInstance()->getRenderer()->renderObject(_view->getRenderObject(), _buffer[targetBuffer],_camera);

        }
        


    
        
        
        _camera->setWindowsSize(_finalBuffer->getWidth(), _finalBuffer->getHeight());
        _view->setTexture(_buffer[targetBuffer]->getRenderTarget(0)->getTexture());
        _view->setContentSize(Vec2(_finalBuffer->getWidth(), _finalBuffer->getHeight()));
        Director::getInstance()->getRenderer()->renderObject(_view->getRenderObject(), _finalBuffer,_camera);

        
//        Texture* finalText= _finalBuffer->getRenderTarget(0)->getTexture();
//
//        Director::getInstance()->getRenderer()->bindTextureToPosition(finalText, 0);

//        
        _finalBuffer->bind();

        GLfloat luminescence[12];
       
        glReadPixels(0,0, 2, 2, GL_RGB, GL_FLOAT, &luminescence[0]);
        GLfloat lum = 0.2126 * luminescence[0] + 0.7152 * luminescence[1] + 0.0722 * luminescence[2];
        lum=0.001;
       
        for (int i=0; i<12-1; i+=3) {
         
            lum+=luminescence[i]*0.2126;
            lum+=luminescence[i+1]*0.7152;
            lum+=luminescence[i+2]*0.0722;

        }

       
        
        //float exposure = lerp(exposure, 0.5 / lum, 0.05); // slowly adjust exposure based on average brightness
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        _finalBuffer->unbind();
//
//        GLfloat luminescence[3];
//
//        glGetTexImage(GL_TEXTURE_2D,2,GL_RGB,GL_UNSIGNED_BYTE,&luminescence[0]);
//        GLfloat lum = 0.2126 * luminescence[0] + 0.7152 * luminescence[1] + 0.0722 * luminescence[2];

        
        return lum;
    }


}