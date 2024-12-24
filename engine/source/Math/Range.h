

#ifndef SGENGINE_RANGE_H
#define SGENGINE_RANGE_H

#include "SBase.h"

class Range{

public:
    float min;
    float max;
    
    float getLenght();
    
    Range();
    Range(float min, float max );
    float getRandom();
    
    void set(float min, float max);
    
};

#endif