

#ifndef Particle_H
#define Particle_H

#include <stdio.h>
#include "SBase.h"

namespace sge {
    
class Particle{

private:

        
public:
    
    Vec4 position;
    Vec3 rotation;
    Vec3 scale;
    
    Vec3 speed;
    Vec4 color; // Color
    Vec3 direction;

    float angle;
    float weight;
    float life;

    
	Particle();
	~Particle();
	
};

}
#endif
