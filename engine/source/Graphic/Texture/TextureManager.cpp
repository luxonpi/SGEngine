

#include "TextureManager.h"

namespace sge {

    TextureManager* TextureManager::instance=NULL;

    TextureManager::TextureManager(){
    

    }

    TextureManager* TextureManager::getInstance(){

        if(!instance) instance= new TextureManager();
        return instance;

    }
    
    void TextureManager::insertIntoCache(Texture* texture){
    
        textures.push_back(texture);
    
    }

    Texture* TextureManager::getTexture(const std::string& file){
    
        // Could be faster
        for (int i=0; i<textures.size(); i++) {
        
            if(textures[i]->getNameID()==file){
            
                return textures[i];
        
            }

        }
        
        return NULL;
        
    }

}