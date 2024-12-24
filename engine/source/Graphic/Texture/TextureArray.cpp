

#include "TextureArray.h"
#include "Director.h"
#include "stb_image.h"

#include "glInclude.h"

namespace sge {

TextureArray::TextureArray(){

    _type=TextureType::ARRAY;
    _numberOfLayers=0;

}

TextureArray::~TextureArray(){}


void TextureArray::setTextureAtIndex(std::string file, int index){
    
    checkRenderError();

    glBindTexture( GL_TEXTURE_2D_ARRAY, _id);

    if(index>=_numberOfLayers){

        _numberOfLayers=index+1;
        checkRenderError();
        
    }

    std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
    
    int n,w,h;
    unsigned char *data = stbi_load(fullPath.c_str(), &w, &h, &n, 4);
    
    if (data == NULL) {
        
        std::cout << "Could not Load: " << file <<" Reason: "<< stbi_failure_reason() << std::endl;
        assert(0);
        // Release Stb Data
        stbi_image_free(data);
        return;
        
    }

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, _width, _height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    checkRenderError();
    
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    
    glBindTexture( GL_TEXTURE_2D_ARRAY, 0);
    checkRenderError();

}

    
TextureArray* TextureArray::create(int depth, int width, int height){

    TextureArray* t= new TextureArray();
    
    t->_width=width;
    t->_height=height;
    t->_numberOfLayers=depth;
    
    glGenTextures(1, &t->_id);
    glBindTexture( GL_TEXTURE_2D_ARRAY, t->_id);
    
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB8, width, height,  depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    checkRenderError();

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
#ifdef GL_GENERATE_MIPMAP
    glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
#endif

    checkRenderError();
    
    return t;
 
}
    
}
