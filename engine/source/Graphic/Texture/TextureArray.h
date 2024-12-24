

#ifndef SGENGINE_TEXTUREARRAY_H
#define SGENGINE_TEXTUREARRAY_H

#include <stdio.h>
#include <vector>
#include <string>

#include "Texture.h"

namespace sge {
    
    class TextureArray: public Texture{

    private:
    
        TextureArray();
        ~TextureArray();
        
        int _numberOfLayers;

    
    public:
    
        static TextureArray* create(int depth, int width, int height);
        void setTextureAtIndex(std::string file, int index);


    };

}

#endif