#include "IniParser.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

namespace sge {

void str_replace( std::string &s, const std::string &search, const std::string &replace ){
    
    for( size_t pos = 0; ; pos += replace.length() ){
    
        pos = s.find( search, pos );
        if( pos == std::string::npos ) break;
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}
    
std::string& ltrim(std::string& s) {
    
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        std::ptr_fun<int, int>(std::isgraph)));
    return s;

}
    
std::string& rtrim(std::string& s) {

    s.erase(std::find_if(s.rbegin(), s.rend(),
    std::ptr_fun<int, int>(std::isgraph)).base(), s.end());
    return s;
}
    
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}
    
void IniReader::parseFile(const std::string& file){
    
    std::string line;
    std::ifstream infile(file);
    
    assert(infile);
    
    IniReader::Section* currentSection=NULL;
    
    while (std::getline(infile, line)){
        
        long pos;
        
        // Remove comments
        pos = line.find(";");
        if (pos >= 0) {
            line.erase(pos, line.length());
        }
        
        if (line.empty())
            continue;
        
        // Check for section
        pos = line.find("[");
        if (pos == 0) {
            long sectionEnd = line.find("]");
            //assert(sectionEnd > pos && "Invalid Section!");
            if (sectionEnd > pos)
            {
                line.erase(0, pos + 1);
                line.erase(sectionEnd - 1, line.length());
                trim(line);
                currentSection= new IniReader::Section();
                currentSection->name=line;
                sections.push_back(currentSection);
                continue;
            }
        }
        
        //assert(!currentSection.empty() && "Key without section found");
        
        pos = line.find("=");
        if (pos >= 0 && currentSection)
        {
            std::string key(line);
            key.erase(pos, line.length());
            
            std::string value(line);
            value.erase(0, pos + 1);
            
            key= trim(key);
            value=trim(value);
            str_replace(value, "\\n", "\n");
            
            currentSection->entries[key] = value;
        }
    }

}

void IniReader::parseString(const std::string& string){
    
    // Not implemented correctly
    assert(0);
    std::string line;
    std::ifstream infile(string);

    assert(infile);
    
    IniReader::Section* currentSection=NULL;

    while (std::getline(infile, line)){
        
        long pos;

        // Remove comments
        pos = line.find(";");
        if (pos >= 0) {
            line.erase(pos, line.length());
        }

        if (line.empty())
            continue;

        // Check for section
        pos = line.find("[");
        if (pos == 0) {
            long sectionEnd = line.find("]");
            //assert(sectionEnd > pos && "Invalid Section!");
            if (sectionEnd > pos)
            {
                line.erase(0, pos + 1);
                line.erase(sectionEnd - 1, line.length());
                trim(line);
                currentSection= new IniReader::Section();
                currentSection->name=line;
                sections.push_back(currentSection);
                continue;
            }
        }

        //assert(!currentSection.empty() && "Key without section found");

        pos = line.find("=");
        if (pos >= 0 && currentSection)
        {
            std::string key(line);
            key.erase(pos, line.length());

            std::string value(line);
            value.erase(0, pos + 1);

            key= trim(key);
            value=trim(value);
            str_replace(value, "\\n", "\n");

            currentSection->entries[key] = value;
        }
    }

   
}

int IniReader::Section::getValueAsInt(const std::string& key){
    
    std::string val = getValue(key);
    return atoi(val.c_str());
}
    
sge::Vec2 IniReader::Section::getValueAsVec2(const std::string& key){
    
    std::string val = getValue(key);
    
    if(!SString::containsString(val, "vec2")){
    
        std::cout<< "IniReader key ("<< key << ")" << "does not contain any Vec2"<< std::endl;
        return sge::Vec2(0,0);
    
    }

    SString::replaceAll(val, "vec2", "");
    SString::removeAllCharsExcept(val, "1234567890,.");
    
    std::vector<float> array;
    SString::getArrayFromString(val, array);
    
    if(array.size()>=2){
    
        return sge::Vec2(array[0],array[1]);

    
    }
    
    return sge::Vec2(0,0);

}

 
sge::Vec3 IniReader::Section::getValueAsVec3(const std::string& key){

    std::string val = getValue(key);
    
    if(!SString::containsString(val, "vec3")){
        
        std::cout<< "IniReader key ("<< key << ")" << "does not contain any vec3"<< std::endl;
        return sge::Vec3(0,0,0);
        
    }
    
    SString::replaceAll(val, "vec3", "");
    SString::removeAllCharsExcept(val, "1234567890,.");
    
    std::vector<float> array;
    SString::getArrayFromString(val, array);
    
    if(array.size()>=3){
        
        return sge::Vec3(array[0],array[1],array[2]);
        
        
    }
    
    return sge::Vec3(0,0,0);


 
}
   
sge::Vec4 IniReader::Section::getValueAsVec4(const std::string& key){

    std::string val = getValue(key);
    
    if(!SString::containsString(val, "vec4")){
        
        std::cout<< "IniReader key ("<< key << ")" << "does not contain any Vec4"<< std::endl;
        return sge::Vec4(0,0);
        
    }
    
    SString::replaceAll(val, "vec4", "");
    SString::removeAllCharsExcept(val, "1234567890,.");
    
    std::vector<float> array;
    SString::getArrayFromString(val, array);
    
    if(array.size()>=4){
        
        return sge::Vec4(array[0],array[1],array[2],array[3]);
        
        
    }
    
    return sge::Vec4(0,0,0,0);


}
    
double IniReader::Section::getValueAsDouble(const std::string&  key){
    
    std::string val = getValue(key);
    
    SString::removeAllCharsExcept(val, "1234567890.");
    
    return atof(val.c_str());
}

float IniReader::Section::getValueAsFloat(const std::string&  key){
    
    return float(getValueAsDouble(key));
}

std::string IniReader::Section::getValue(const std::string&  key){
    
    return entries[key];
}

IniReader::Section* IniReader::getSection(const std::string& section){
    
    for (int i=0; i<sections.size(); i++) {
        
        if(sections[i]->name==section) return sections[i];
        
    }
    
    return NULL;
}

IniReader::Section::Section(){
    
    
}
    
IniReader::Section::~Section(){
        
        
}


} // namespaces end
