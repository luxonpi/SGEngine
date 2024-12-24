

#ifndef SString_H
#define SString_H

#include <stdio.h>
#include <string>
#include <vector>
#include "SBase.h"

namespace sge {
    
    class SString{

    public:
        
        static void replaceAll(std::string& str, const std::string& from, const std::string& to);
        static void replaceFirst(std::string& str, const std::string& from, const std::string& to);
        static void removeWhiteSpaceAtFront(std::string& string);
        static bool containsString(const std::string& sourcestring, const std::string& stringToFind);
    
        static void removeAllCharsExcept(std::string& string, const std::string& allowedChars);
        static void removeChars(std::string& string, const std::string& charsToBeRemoved);

        static void getArrayFromString(const std::string& string, std::vector<float>& array);
        
        static std::vector<std::string> getStringArrayFromCommaSeperatedString(const std::string& string);

	
    };
    
}

#endif
