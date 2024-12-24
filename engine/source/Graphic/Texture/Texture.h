

#ifndef SGENGINE_TEXTURE_H
#define SGENGINE_TEXTURE_H

#include <iostream>
#include <string>

#include "SBase.h"
#include "GraphicDeviceOpenGL.h"
#include "Resources.h"

namespace sge {

    class TextureManager;
    class Texture: public Resource{

    friend TextureManager;
    friend GraphicDevice;
    friend GraphicDeviceOpenGL;

    protected:
        
        Texture();
        ~Texture();
        
        SUint _id;
        SUint _magFilter;
        SUint _minFilter;
        
        std::string _nameID;
        
        SUint _dataType;
        SUint _format;

        int _type;
        int _warp;

        int _width;
        int _height;
        
        static bool _init;
    
    public:
        
        static void init();
        
        static Texture* color2x2White;
        static Texture* color2x2Normal;
        static Texture* color2x2Black;
        
        SInt getID();
        
        SUint getDataType();
        std::string getNameID();
        
        int getType();
        
        Vec2 getSize();
        
        SUint getFormat();

        void generateMipMap();
        void setAnisotropy();
    
        void setMagFilter(const SUint& filter);
        void setMinFilter(const SUint& filter);

        void setTextureWrap(const SUint& wrap);
        void setSize(int width, int height);
    
        static Texture* get(const std::string& file);
        static Texture* create(int width, int height, SUint format, SUint internalFormat, SUint dataType);
        static Texture* createColorTexture(const Color& color, int width, int height, const std::string& nameID);
        static Texture* create(int width, int height, SUint format, SUint internalFormat, SUint dataType, void* data);

        
    };

}

#endif
