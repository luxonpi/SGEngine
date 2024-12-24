

#include "GPUInfo.h"
#include "SBase.h"

#include "glInclude.h"

namespace sge {

    float GPUInfo::getMaxTextureSize(){
    
        float val=0;;
        glGetFloatv(GL_MAX_TEXTURE_SIZE, &val);

        return val;
        
    }
    
    float GPUInfo::getMax3dTextureSize(){
    
        float val=0;;
        
#ifndef MOBILE_TARGET
        glGetFloatv(GL_MAX_3D_TEXTURE_SIZE, &val);
#endif

        return val;
    
    }
    
    unsigned int GPUInfo::getMaxVertexAttributes(){
    
        float val=0;;
        glGetFloatv(GL_MAX_VERTEX_ATTRIBS, &val);
        checkRenderError();

        return val;
    
    }
    
    unsigned int GPUInfo::getMaxVaryingFloats(){
    
        float val=0;;
        glGetFloatv(GL_MAX_VARYING_VECTORS, &val);

        return val;
    
    }
    
    unsigned int GPUInfo::getMaxTextureUnits(){
    
        float val=0;;
        glGetFloatv(GL_MAX_TEXTURE_IMAGE_UNITS, &val);

        return val;

    }
    
    void GPUInfo::print(){
    
        std::cout << "Max Texture Size: " << getMaxTextureSize() << std::endl;
        std::cout << "Max 3d Texture Size: " << getMax3dTextureSize() << std::endl;
        std::cout << "Max Vertex Attributes: " << getMaxVertexAttributes() << std::endl;
        std::cout << "Max Varying Components: " << getMaxVaryingFloats() << std::endl;
        std::cout << "Max Texture Units: " << getMaxTextureUnits() << std::endl;
        
        checkRenderError();

    }


    
    
    
};