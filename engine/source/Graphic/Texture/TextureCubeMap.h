

#ifndef SGENGINE_CUBEMAPTEXTURE_H
#define SGENGINE_CUBEMAPTEXTURE_H

#include <stdio.h>
#include <vector>
#include <string>

#include "Texture.h"

namespace sge {
    
    class TextureCubeMap: public Texture{
        
        friend GraphicDevice;
        friend GraphicDeviceOpenGL;
        
    private:
        
        TextureCubeMap();
        ~TextureCubeMap();
        
        
    public:
        
        static TextureCubeMap* create(std::vector<std::string> files);
        static TextureCubeMap* createEmpty(int width, int height, SInt format);

        
        
    };
    
}

#endif