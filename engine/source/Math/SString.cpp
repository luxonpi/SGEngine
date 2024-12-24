

#include "SString.h"
#include <sstream>

namespace sge {

    std::vector<std::string> SString::getStringArrayFromCommaSeperatedString(const std::string& string){
    
        std::vector<std::string> array;
        std::string text=string;
      
        size_t rightPos = 0;

        while((rightPos = text.find(",")) != std::string::npos) {
        
            array.push_back(text.substr(0, rightPos));
            text.erase(0,rightPos+1);
                  
        }
        
        if(text.length()!=0){
        
            array.push_back(text);

        }
    
        return array;
    }
    
    void SString::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    
        size_t start_pos = 0;
    
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    
    }

    void SString::replaceFirst(std::string& str, const std::string& from, const std::string& to) {
    
        size_t pos = str.find(from, 0);
        if( pos != std::string::npos) {
            str.replace(pos, from.length(), to);
        }
    
    }

    void SString::removeWhiteSpaceAtFront(std::string& string){
    
        while(string.length()>0 && string[0]==' ') {
        
            string.replace(0, 1, "");
        
        }
    
    }
    
    bool SString::containsString(const std::string& sourcestring, const std::string& stringToFind){
    
        if(sourcestring.find(stringToFind)!=std::string::npos){
        
            return true;
        
        }
        
        return false;
    
    }
    
    
    void SString::removeAllCharsExcept(std::string& string, const std::string& allowedChars){
    
        std::string::iterator it;
        for (it = string.begin(); it < string.end(); ++it){
            bool found = allowedChars.find(*it) != std::string::npos;
            if(!found){

                it = string.erase(it);
                it--;

            }
        }
    
    
    }
    
    void SString::removeChars(std::string& string, const std::string& charsToBeRemoved){
    
        std::string::iterator it;
        for (it = string.begin() ; it < string.end() ; ++it){
            bool found = charsToBeRemoved.find(*it) != std::string::npos;
            if(found){
                it = string.erase(it);
                it--;
            }
        }
    
    }

    
    
    void SString::getArrayFromString(const std::string& string, std::vector<float>& array){
    
        std::string internString= string+",";
        std::stringstream ss;
        
        int commaPos= (int) internString.find(",");
        while (commaPos!=std::string::npos) {
            
            std::string subString= internString.substr(0, commaPos);
            internString.erase(0, commaPos+1);
            
            if(subString.length()>0){
            
                ss.clear();
                ss.str("");
                
                ss<<subString;
                float b=0;
                ss>>b;
                array.push_back(b);
            
            }
            
            commaPos= (int) internString.find(",");
            
        }
    
    
    }

    
}
