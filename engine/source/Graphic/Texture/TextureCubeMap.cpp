

#include "TextureCubeMap.h"
#include "stb_image.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {

    TextureCubeMap::TextureCubeMap(){
        
        _type=TextureType::CUBE_MAP;
        
    }
    
    TextureCubeMap::~TextureCubeMap(){
        
    }
    
    TextureCubeMap* TextureCubeMap::createEmpty(int width, int height, SInt format){
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();

        TextureCubeMap* t= new TextureCubeMap();
        gDevice->generateTexture(t);
        
        t->_width=width;
        t->_height=height;
        t->_warp= TextureWrap::CLAMP_TO_EDGE;
        t->_magFilter= TextureFilter::LINEAR;
        t->_minFilter= TextureFilter::LINEAR;
        
        gDevice->setTextureFilter(t);
        gDevice->setTextureWrap(t);
        
        // Set textures
        for (int i = 0; i < 6; ++i)
            gDevice->setCubeMapTextureData(t, i, 0, format, width, height, TextureFormat::RGB, 0);
        
        checkRenderError();
        
        return t;

    
    }
    
    TextureCubeMap* TextureCubeMap::create(std::vector<std::string> files){
        
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();

        TextureCubeMap* t= new TextureCubeMap();
        gDevice->generateTexture(t);
        
        t->_warp= TextureWrap::CLAMP_TO_EDGE;
        t->_magFilter= TextureFilter::LINEAR;
        t->_minFilter= TextureFilter::LINEAR;
        
        gDevice->setTextureFilter(t);
        gDevice->setTextureWrap(t);
        
        t->_nameID=files[0];
        t->_dataType= DataType::UNSIGNED_BYTE;
        
        t->Resource::name="TexCube | "+ files[0];

        
        for(int i = 0; i < files.size(); i++){
            
            std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(files[i]);
            
            int n;
            unsigned char *data = stbi_load(fullPath.c_str(), &t->_width, &t->_height, &n, 3);
            checkRenderError();
            
            if (data == NULL) {
                
                std::cout << "Could not load image: " << files[i] <<" Reason: "<< stbi_failure_reason() << std::endl;
                
                // Release STB Data
//                stbi_image_free(data);
//                
//                glDeleteTextures(1, &t->_id);
//                glBindTexture(GL_TEXTURE_2D, 0);
                
                return NULL;
                
            }

    
            gDevice->setCubeMapTextureData(t, i, 0, TextureFormat::RGB, t->_width, t->_height, TextureFormat::RGB, data);
          
            unsigned long sizeInBits=t->_width*t->_height*8*n;
            t->sizeInByte+=sizeInBits/8;


            // Release Stb Data
            stbi_image_free(data);
       
        }
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, t->_id);
        
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    
        
        checkRenderError();
        
        return t;
        
    }








}