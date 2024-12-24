

#ifndef SGENGINE_GPUINFO_H
#define SGENGINE_GPUINFO_H

#include <stdio.h>

namespace sge {
    
    class GPUInfo{
    
    private:
        
        static float _maxTextureSize;
        static float _max3dTextureSize;
        static unsigned int _maxVertexAttributes;
        static unsigned int _maxVaryingFloats;
        static unsigned int _maxTextureUnits;

    public:
        
        static float getMaxTextureSize();
        static float getMax3dTextureSize();
        static unsigned int getMaxVertexAttributes();
        static unsigned int getMaxVaryingFloats();
        static unsigned int getMaxTextureUnits();
        
        static void print();
        
    };
    
}


#endif