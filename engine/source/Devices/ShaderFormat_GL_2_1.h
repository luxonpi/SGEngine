

#ifndef SGENGINE_SHADERFORMAT_GL_2_1_H
#define SGENGINE_SHADERFORMAT_GL_2_1_H

#include "SBase.h"
#include "Shader.h"
#include "ShaderFormat.h"
#include "ShaderModule.h"

namespace sge {
    
    class ShaderFormat_GL_2_1: public ShaderFormat{
        
    private:
        
        std::string _prefix;
        
    public:
        
        ShaderFormat_GL_2_1();
        virtual ~ShaderFormat_GL_2_1();
        
        virtual std::string getVertexSource(ShaderModule* shaderModule) override;
        virtual std::string getFragmentSource(ShaderModule* shaderModule) override;
        
    };
    
}


#endif
