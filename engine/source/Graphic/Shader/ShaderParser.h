

#ifndef SGENGINE_SHADERPARSER_H
#define SGENGINE_SHADERPARSER_H

#include "SBase.h"
#include "ShaderModule.h"

namespace sge {

#define LOCATION_TARGET_APP_BUNDLE 0
#define LOCATION_TARGET_PROJECT 1

    class ShaderParser{

    private:
    
        SUint _locationTarget;
        
    public:
        
        void setLocationTarget(SUint target);
        
        void parseIOUfromSource(std::string& string, ShaderModule::ShaderVarContainer* varContainer);
        
        void parseFileIntoShaderPart(const std::string& file, ShaderModule::ShaderPart* part, ShaderModule* module);
        
        std::string getFilePathFromLine(const std::string& text);
        std::string getDefineFromLine(const std::string& text);
    
        void filterShaderPart(ShaderModule::ShaderPart* part, const std::vector<std::string>& defines);
        void handleAreasForPart(ShaderModule::ShaderPart* part);
        
        void clearWhiteSpace(std::string& string);
        void parseShaderIntoModule(const std::string& file, ShaderModule* module);
        void removeCommentsFromLine(std::string& string);
        std::string getSourceFromFile(const std::string& file);
        
        void replaceVariables(std::string& source, const std::string& from, const std::string& to);
        std::vector<std::pair<std::string, std::string>> getReplacmentsFromLine(const std::string& line);
        
        ShaderModule::ShaderVar parserShaderVarFromLine(const std::string& line);

    };
    
}

#endif
