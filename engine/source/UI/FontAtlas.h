

#ifndef SGENGINE_FONTATLAS_H
#define SGENGINE_FONTATLAS_H

#include "SBase.h"
#include "Texture.h"

namespace sge {

    class Font;

    struct Character {
        
        float advanceX;
        float advanceY;
        
        float bitmapWidth;
        float bitmapHeight;
        
        float bitmapLeft;
        float bitmapTop;
        
        float uvOffsetX;
        float uvOffsetY;
        
    };
    
    class FontAtlas{
        
    private:
        

        Texture* _texture;
        
        Vec2 size;
        
        FontAtlas();
        ~FontAtlas();

        void initWithFontAndSize(Font* font, float size);
        
    public:
        
        Character characters[128];

        Texture* getTexture();
        
        static FontAtlas* createFromFontAndSize(Font* font, float size);
        
        
    };
    
    
}

#endif 