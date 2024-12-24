

#ifndef SGENGINE_SHADERFORMAT_GL_ES_H
#define SGENGINE_SHADERFORMAT_GL_ES_H

#include "SBase.h"
#include "Shader.h"
#include "ShaderFormat.h"
#include "ShaderModule.h"

namespace sge {
    
    class ShaderFormat_GL_ES: public ShaderFormat{
        
    private:
        
        std::string _prefix;
        
    public:
        
        ShaderFormat_GL_ES();
        virtual ~ShaderFormat_GL_ES();
        
        virtual std::string getVertexSource(ShaderModule* shaderModule) override;
        virtual std::string getFragmentSource(ShaderModule* shaderModule) override;
        
    };
    
}


#endif
