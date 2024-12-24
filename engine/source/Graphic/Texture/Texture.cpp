

#include "Texture.h"

#include <iostream>

#include "stb_image.h"

#include "TextureManager.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {
    
    bool Texture::_init=false;
    
    Texture* Texture::color2x2White=NULL;
    Texture* Texture::color2x2Normal=NULL;
    Texture* Texture::color2x2Black=NULL;

    void Texture::init(){
        
        if(_init) return;
        _init=true;
        
        color2x2White=createColorTexture(Color::white,2,2, "");
        color2x2Normal=createColorTexture(Color(128,128,255,1),2,2, "");
        color2x2Black=createColorTexture(Color(0,0,0,1),2,2, "");

    }
    
    
    Texture::Texture(): Resource("texture"){
        
        _id=0;
        _warp=TextureWrap::CLAMP;
        _type=TextureType::NORMAL2D;
        _dataType= DataType::UNSIGNED_BYTE;
        _magFilter= TextureFilter::LINEAR;
        _minFilter= TextureFilter::LINEAR;
    
    }
    
    Texture* Texture::get(const std::string& file){
        
        // If cached return it
        Texture* tex= TextureManager::getInstance()->getTexture(file);
        if(tex) return tex;
    
        // Check for file validity
        if(file.length()==0) return NULL;
        
        std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
        
        int channels=0;
        if(Director::getInstance()->getFileUtils()->doesFileExistForFullPath(fullPath+".ini")){
            
            std::string content=Director::getInstance()->getFileUtils()->getStringFromFullPath(fullPath+".ini");
            std::stringstream ss;
            ss<<content;
            
            ss>>channels;
            
        }
        
        
        int n=0, width=0, height=0;
        unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &n, channels);
    
        if(channels!=0) n=channels;
        
        if (data == NULL) {

//            assert(0);
            error("Could not load image: " + file  + " Reason: " + std::string(stbi_failure_reason()));
//            
            // Release STB Data
            stbi_image_free(data);
        
            return NULL;
            
        }
        
  
        
        unsigned long sizeInBits=width*height*8*n;
        
        SInt teFormat=TextureFormat::RGB;
        
        if(n==4) teFormat=TextureFormat::RGBA;
        if(n==3) teFormat=TextureFormat::RGB;
        if(n==2) assert(0);
        if(n==1) teFormat=TextureFormat::RED;

        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        Texture* t= new Texture();
        gDevice->generateTexture(t);
        t->_width=width;
        t->_height=height;
        t->_nameID=file;
        t->_dataType= DataType::UNSIGNED_BYTE;
        t->_format=teFormat;

        // Load file data into texture
        gDevice->setTextureData(t, 0, teFormat, width, height, teFormat, data);
        
        // Release Stb Data
        stbi_image_free(data);
        
        // Parameter
        t->setMagFilter(TextureFilter::LINEAR);
        t->setMinFilter(TextureFilter::LINEAR);
        t->setTextureWrap(TextureWrap::REPEAT);
        
        checkRenderError();
        
        t->sizeInByte=sizeInBits/8;
        t->Resource::name=file;

        TextureManager::getInstance()->insertIntoCache(t);
        
        return t;

    }

    Texture* Texture::create(int width, int height, SUint format, SUint internalFormat, SUint dataType){
        
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        Texture* t= new Texture();
        gDevice->generateTexture(t);
        t->_width=width;
        t->_height=height;
        t->_dataType=dataType;
        t->_format=format;

        gDevice->setTextureData(t, 0, internalFormat, width, height, format, 0);

        // Parameter
        t->setMagFilter(TextureFilter::LINEAR);
        t->setMinFilter(TextureFilter::LINEAR);
        t->setTextureWrap(TextureWrap::REPEAT);
        
        
        t->sizeInByte=width*height*TextureFormat::getByteOfType(format);
        t->Resource::name="Custom | ";

        return t;
        
    }
    
    Texture* Texture::create(int width, int height, SUint format, SUint internalFormat, SUint dataType, void* data){
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        Texture* t= new Texture();
        gDevice->generateTexture(t);
        t->_width=width;
        t->_height=height;
        t->_nameID="";
        t->_dataType= dataType;
        t->_format=format;
        // Load file data into texture
        gDevice->setTextureData(t, 0, internalFormat, width, height, format, data);
        
        // Parameter
        t->setMagFilter(TextureFilter::LINEAR);
        t->setMinFilter(TextureFilter::LINEAR);
        t->setTextureWrap(TextureWrap::REPEAT);
        
        checkRenderError();
        
        t->sizeInByte=width*height*4;
        t->Resource::name="Custom | ";
        
        return t;

    
    }
  
    Texture* Texture::createColorTexture(const Color& color, int width, int height, const std::string& nameID){
        
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        Texture* t= new Texture();
        gDevice->generateTexture(t);
        t->_width=width;
        t->_height=height;
        t->_nameID=nameID;
        t->_dataType= DataType::UNSIGNED_BYTE;

        unsigned char *data = new unsigned char[width * height* 4];
        for(int i = 0; i < width * height * 4; i+=4){
            
            data[i] =   255*color.r;
            data[i+1] = 255*color.g;
            data[i+2] = 255*color.b;
            data[i+3] = 255*color.a;
            
        }
        
        t->_format=TextureFormat::RGBA;
        // Load file data into texture
        gDevice->setTextureData(t, 0, TextureFormat::RGBA, width, height, TextureFormat::RGBA, data);
        
        // Delete Data
        delete[] data;

        // Parameter
        t->setMagFilter(TextureFilter::LINEAR);
        t->setMinFilter(TextureFilter::LINEAR);
        t->setTextureWrap(TextureWrap::REPEAT);
        
        t->sizeInByte=width*height*4;
        t->Resource::name="ColorTex | " + color.getHex();
        
        checkRenderError();
        
        TextureManager::getInstance()->insertIntoCache(t);
       
        return t;
        
    }
    
    
    SUint Texture::getFormat(){
    
        return _format;
    }
    
    std::string Texture::getNameID(){

        return _nameID;
        
    }

    SInt Texture::getID(){

        return _id;

    }

    Vec2 Texture::getSize(){
    
        return Vec2(_width, _height);
    
    }
    
    int Texture::getType(){

        return _type;

    }
    
    void Texture::setAnisotropy(){
    
       // Anisotropic filtering (avoid blurred mimpaps)
        glBindTexture(GL_TEXTURE_2D, _id);

        GLfloat maxAnsitropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnsitropy);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnsitropy );
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        checkRenderError();

    }
    
    void Texture::generateMipMap(){
    
        glBindTexture(GL_TEXTURE_2D, _id);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
       
        glBindTexture(GL_TEXTURE_2D, 0);
        
        checkRenderError();
        
    }
    
    void Texture::setTextureWrap(const SUint& wrap){
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();

        checkRenderError();

        _warp=wrap;
        gDevice->setTextureWrap(this);
        
        checkRenderError();

    }
    
    void Texture::setMagFilter(const SUint& filter){
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        _magFilter=filter;
        gDevice->setTextureFilter(this);
        
    }
    
    void Texture::setMinFilter(const SUint& filter){
    
        GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
        
        _minFilter=filter;
        gDevice->setTextureFilter(this);
        
    }
    
    SUint Texture::getDataType(){
    
        return _dataType;
    
    }

   Texture::~Texture(){

       GraphicDevice* gDevice= Director::getInstance()->getGraphicDevice();
       if(_id) gDevice->releaseTexture(this);
    
   }

    void Texture::setSize(int Width, int Height){

        _width= Width;
        _height= Height;

    }

  
  
}
