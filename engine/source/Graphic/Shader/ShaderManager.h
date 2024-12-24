

#ifndef SGENGINE_SHADERMANAGER_H
#define SGENGINE_SHADERMANAGER_H

#include <stdio.h>
#include "SBase.h"
#include "Shader.h"

namespace sge {
    
    class ShaderManager{
        
    private:
        
        unsigned long _shaderCount;
        Shader* _activeShader;
        
        // Statics
        std::unordered_map<std::string, Shader*> _shaderMap;
     
    public:
        
        Shader* findChachedShader(const std::string& nameID);
        Shader* createNewShader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& nameID);
        
        
        static ShaderManager* getInstance();
        
        void bindShader(Shader* shader);
        Shader* getActiveShader();
        
        
    };
    
}


#endif 
