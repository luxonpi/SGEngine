

#ifndef SGENGINE_SHADERMODULE_H
#define SGENGINE_SHADERMODULE_H

#include "SBase.h"
#include "Shader.h"

#define SHADER_PART_TYPE        0
#define SHADER_PART_DEFINE      1
#define SHADER_PART_INCLUDE     2
#define SHADER_PART_AREA        3
#define SHADER_PART_CONTENT     4
#define SHADER_PART_PLACEHOLDER     5

#define SHADER_PART_DEFINE_IF       0
#define SHADER_PART_DEFINE_IFDEF    1
#define SHADER_PART_DEFINE_IFNDEF   2
#define SHADER_PART_DEFINE_ELSEIF   3
#define SHADER_PART_DEFINE_ELSE     4

namespace sge {
    
    class ShaderParser;
    class ShaderFormat;
    class ShaderModule: public ShaderState::Observer{
        
        friend ShaderParser;
        
    public:
    
        struct ShaderVar{
        
            std::string name;
            std::string type;
            
            std::string function;
            int location;
            std::string initVar;
            bool global;
            
            ShaderVar(){
            
                location=0;
                global=0;
            
            }
    
        };
        
        struct ShaderPart{
    
            int type;
            int subtype;

            std::string name;
            std::string content;
            bool shouldOverride;
            
            std::vector<ShaderPart> subparts;
          
            ShaderPart(){
                
                type=SHADER_PART_TYPE;
                shouldOverride=false;
            }
            
            ShaderPart(int pType){
            
                type=pType;
                shouldOverride=false;

            }
            
        };
        
        class ShaderVarContainer{
        
        public:
            std::vector<ShaderVar> uniforms;
            std::vector<ShaderVar> inputs;
            std::vector<ShaderVar> outputs;
            
            void addShaderVar(const ShaderVar& var);

        };
        
        struct ItHelper{
            
            ShaderPart* shaderPart;
            unsigned int iterator;
            bool lastIfResult;
            
            ItHelper(ShaderPart* pshaderPart){
            
                shaderPart=pshaderPart;
                iterator=0;
                lastIfResult=0;
            
            }
            
        };
        
    private:

        static std::unordered_map<std::string, ShaderModule*> _cache;
        static ShaderParser* _shaderParser;

        ShaderModule();
        ~ShaderModule();

        std::string _name;
        std::string _filePath;

        ShaderState _state;
        
        ShaderPart shaderParts[3];
        std::set<std::string> _shaderDefines;
        std::vector<ShaderState*> _registerShaderStates;

        
        std::string getVertexSource(const std::vector<std::string>& defines, ShaderState* initUniforms);
        std::string getFragSource(const std::vector<std::string>& defines, ShaderState* initUniforms);

        std::unordered_map<std::string, Shader*> _subShaders;
        std::string getSourceForShaderPart(ShaderPart* part, std::string& outIncludes);
        
        
        void shaderStateChanged(ShaderState* state);

    public:
        
        void addDefine(const std::string& define);
        void removeDefine(const std::string& define);
        void replaceDefine(const std::string& defineToBeReplaced, const std::string& define);

        void registerShaderState(ShaderState* shaderState);
        
        void refresh();
        
        ShaderState* getGlobalShaderState();
        
        static ShaderModule* get(const std::string& file);        
        Shader* getShaderForDefines(std::vector<std::string> defines);
    

    };
    
}

#endif
