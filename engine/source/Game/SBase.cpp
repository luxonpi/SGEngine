

#include "SBase.h"

void _Error(const char* file, int line, const std::string& message){

    std::cerr << "🔴: " << message << "  ( " << file << ":" << line << " )" <<std::endl;
    
}

void _Log(const std::string& message){

    std::cerr << "📗: " << message << std::endl;

}