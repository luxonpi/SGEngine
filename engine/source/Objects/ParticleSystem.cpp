

#include "ParticleSystem.h"
#include "Director.h"

namespace sge {
    
    static const SFloat g_vertex_buffer_data[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f,  0.0f,
         0.5f, 0.5f,  0.0f,
    };
    
    ParticleSystem* ParticleSystem::create(){
    
        ParticleSystem* ps= new ParticleSystem();
        return ps;
    
    }
    
    void ParticleSystem::setMoveMode(int mode){

        _moveMode=mode;

    }
    
    
    ParticleSystem::ParticleSystem(){
    
        // Input register
        UpdateReceiver* newReceiver= new UpdateReceiver(CALLBACK_SELECTOR(ParticleSystem::update, this), 1/60. , 0);
        
        _amountOfParticles=5000;
        _moveMode=0;
        
        _particles.resize(_amountOfParticles);
        
        for (int i=0; i<_amountOfParticles; i++) {
            
            _particles[i].position.set((rand()%1000)/10.-50,(rand()%200)/10.,(rand()%1000)/10.-50, (rand()%20)/100.+0.1);
            _particles[i].color.set(1,1,1,0.3);
            _particles[i].direction.set((rand()%100)/50.-1, -((rand()%500)/100+0.5), (rand()%100)/50.-1);

        }
        
        _positionData.resize(_particles.size());
        _colorData.resize(_particles.size());
        
        for (int i=0; i<_particles.size(); i++) {
            
            _positionData[i]=_particles[i].position;
            _colorData[i]=_particles[i].color;
            
        }
        
        Director::getInstance()->getUpdateDispenser()->addReceiver(newReceiver);
        
        getRenderObject()->setDrawAble(true);
        
        _billboardBuffer= VertexBuffer::create((void*) &g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
        
        _positionBuffer= VertexBuffer::create(NULL, (unsigned int) _particles.size()* sizeof(Vec4));
        _positionBuffer->setDrawType(BufferDrawType::STREAM);
    
        _colorBuffer= VertexBuffer::create(NULL, (unsigned int) _particles.size()* sizeof(Vec4));
        _colorBuffer->setDrawType(BufferDrawType::STREAM);

        _vao= VertexArrayObject::create();
        
        // Not Normalized
        AttributePointer ap=AttributePointer(_positionBuffer, 4,  DataType::FLOAT, 0 ,0, POSITION_LOCATION);
        ap.divisor=1;
        _vao->addAttributePointer(ap);
        
        //Not normalized
        _vao->addAttributePointer(AttributePointer(_billboardBuffer, 3, DataType::FLOAT, 0 ,0, NORMAL_LOCATION));
        
        // Normalized
        AttributePointer ap1=AttributePointer(_colorBuffer, 4,  DataType::FLOAT, 0 ,0, COLOR_LOCATION);
        ap1.divisor=1;
        //ap.normalized=true;
        
        _vao->addAttributePointer(ap1);
        
      //  ShaderModule* m= ShaderModule::createFromFile("support/shader/frag/Particle.glsl");
       // this->getRenderObject()->setShaderState(m->getShader()->getState());
        
      //  _shader= m->getShader();
        
        _texture= Texture::get("assets/sprites/snow.png");
        
        _mesh= new Mesh(_vao);
        // Vao not working anymore, needs mesh!
        //assert(0);
        
        getRenderObject()->setMesh(_mesh);
        _time=0;

    }
    
    
    ParticleSystem::~ParticleSystem(){
    
    
    }
    
    void ParticleSystem::update(float delta){
        
        Vec3 winddir= Vec3(0, 0, 0);
        _time=delta;
        
        Vec3 addition;
        
        if(_moveMode==MOVE_MODE_RELATIVE){
        
            addition= _transform.getTranslation()-_lastPos;
            _lastPos=_transform.getTranslation();
        
        }
    
        for (int i=0; i<_amountOfParticles; i++) {
            
            _particles[i].position.x+=_particles[i].direction.x*delta*0.1+winddir.x*delta+addition.x;
            _particles[i].position.y+=_particles[i].direction.y*delta*0.2+addition.y;
            _particles[i].position.z+=_particles[i].direction.z*delta*0.1+winddir.z*delta+addition.z;

//            _particles[i].position.x+=sin(_time+_particles[i].position.y+_particles[i].position.z)*delta*0.05;
//            _particles[i].position.z+=cos(_time+_particles[i].position.y+_particles[i].position.x)*delta*0.05;
//
//            if(_particles[i].position.y<getPosition().y-20 || _particles[i].position.x<-50+getPosition().x || _particles[i].position.x>50+getPosition().x || _particles[i].position.z<-50+getPosition().z || _particles[i].position.z>50+getPosition().z){
//                
//                _particles[i].position.set((rand()%1000)/10.-50+getPosition().x,(rand()%200)/10.+getPosition().y,(rand()%1000)/10.-50+getPosition().z, 0.1*(rand()%100)/100.0+0.05);
//                
//                _particles[i].direction.set((rand()%100)/50.-1, -((rand()%500)/100+0.5), (rand()%100)/50.-1);
//                _particles[i].color.w=((rand()%80)/100.+0.2);
//
//            }
        
        }
        
        updateBuffer();
    
    }

    void ParticleSystem::renderWithRenderer(Renderer* renderer, RenderState* renderState){
    
        if(_particles.size()==0) return;
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        gDevice->setCullFace(CullFace::NONE);
        gDevice->setBlendingEnabled(true);
        gDevice->setDepthWritingEnabled(false);
        
        _vao->bind();
        
        _shader->bind();
        renderer->setGlobalUniformsToShader(this, renderState, _shader);
        
        checkRenderError();
    
        gDevice->drawArraysInstanced(DrawMode::TRIANGLE_STRIP, 0, 4, (SUint) _particles.size());
        checkRenderError();

        _vao->unbind();
        
        gDevice->setDepthWritingEnabled(true);

    
    }

    
    void ParticleSystem::updateBuffer(){
        
        if(_particles.size()==0) return;
        
        for (int i=0; i<_particles.size(); i++) {
            
            _positionData[i]=_particles[i].position;
            _colorData[i]=_particles[i].color;
            
        }
        
        _positionBuffer->setData(&_positionData[0],  _particles.size() * sizeof(_positionData[0]));
        _colorBuffer->setData(&_colorData[0], _particles.size() * sizeof(_colorData[0]));
    
        _vao->updateImmediately();

    
    }
    
    
}