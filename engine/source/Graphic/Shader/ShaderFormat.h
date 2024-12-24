

#ifndef SGENGINE_SHADERFORMAT_H
#define SGENGINE_SHADERFORMAT_H

#include "SBase.h"
#include "Shader.h"
#include "ShaderModule.h"

namespace sge {
    
    class ShaderFormat{
        
    private:
        
    public:
        
        ShaderFormat();
        virtual ~ShaderFormat();

        virtual std::string getVertexSource(ShaderModule* shaderModule)=0;
        virtual std::string getFragmentSource(ShaderModule* shaderModule)=0;

    };
    
}


#endif
