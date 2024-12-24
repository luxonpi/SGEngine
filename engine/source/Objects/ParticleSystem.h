

#ifndef ParticleSystem_H
#define ParticleSystem_H

#include <stdio.h>

#include "SBase.h"
#include "Particle.h"
#include "Entity.h"

#include "VertexBuffer.h"
#include "VertexArrayObject.h"

#define MOVE_MODE_RELATIVE 0
#define MOVE_MODE_ABSOLUTE 1

namespace sge {
    
    class ParticleSystem: public Entity{

private:
        
        float _time;
        
        int _amountOfParticles;
        
        Texture* _texture;
        
        std::vector<Vec4> _positionData;
        std::vector<Vec4> _colorData;
        
        Shader* _shader;
        
        Mesh* _mesh;

        VertexBuffer* _billboardBuffer;
        VertexBuffer* _positionBuffer;
        VertexBuffer* _colorBuffer;
        
        VertexArrayObject* _vao;

        std::vector<Particle> _particles;
    
        ParticleSystem();
        ~ParticleSystem();
    
        void updateBuffer();
        
        int _moveMode;
        Vec3 _lastPos;


public:


    void setMoveMode(int mode);
    
    void update(float delta);
    virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

    static ParticleSystem* create();
	
};
    
}

#endif
