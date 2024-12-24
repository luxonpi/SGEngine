#ifndef SGENGINE_INIREADER_H
#define SGENGINE_INIREADER_H

#include "SBase.h"
#include <unordered_map>

namespace sge {

class IniReader{

public:
 
    class Section{
        
    public:
    
        std::string name;
        
        std::unordered_map<std::string, std::string> entries;

        Section();
        ~Section();
        

        std::string getValue(const std::string& key);
        
        sge::Vec2 getValueAsVec2(const std::string& key);
        sge::Vec3 getValueAsVec3(const std::string& key);
        sge::Vec4 getValueAsVec4(const std::string& key);
        int getValueAsInt(const std::string& key);
        double getValueAsDouble(const std::string& key);
        float getValueAsFloat(const std::string& key);
    
    };

    IniReader() {}
    ~IniReader() {}

    std::vector<Section*> sections;

    void parseString(const std::string& string);
    void parseFile(const std::string& file);

    Section* getSection(const std::string& section);

};

} // Namespaces End

#endif