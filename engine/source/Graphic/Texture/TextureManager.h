

#ifndef SGENGINE_TEXTUREMANAGER_H
#define SGENGINE_TEXTUREMANAGER_H

#include <iostream>
#include <vector>

#include "Texture.h"

namespace sge {
    
    class TextureManager{
        
        friend Texture;

    private:
    
        static TextureManager* instance;
        TextureManager();
        std::vector<Texture*> textures;
        
        void insertIntoCache(Texture* texture);
        
    public:
    
        static TextureManager* getInstance();
        
        Texture* getTexture(const std::string& file);
        
    
    };
    
}

#endif
