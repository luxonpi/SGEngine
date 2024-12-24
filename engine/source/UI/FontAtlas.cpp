

#include "FontAtlas.h"
#include "FontManager.h"
#include "glInclude.h"

namespace sge {
    
    FontAtlas::FontAtlas(){
    
    
    }
    
    FontAtlas::~FontAtlas(){
    
    
    }
    
    Texture* FontAtlas::getTexture(){
    
        return _texture;
    
    }
    
    FontAtlas* FontAtlas::createFromFontAndSize(Font* font, float size){
    
        FontAtlas* fontAtlas= new FontAtlas();
        fontAtlas->initWithFontAndSize(font, size);
        return fontAtlas;
    
    }
    
    void FontAtlas::initWithFontAndSize(Font* font, float size){
    
        FT_Set_Pixel_Sizes(font->face, 0, size);
        
        FT_GlyphSlot g = font->face->glyph;
        int w = 0;
        int h = 0;
        
        for(int i = 32; i < 128; i++) {
            
            if(FT_Load_Char(font->face, i, FT_LOAD_RENDER)) {
                
                fprintf(stderr, "Loading character %c failed!\n", i);
                continue;
                
            }
        
            w += g->bitmap.width+1;
            h = std::max(h, g->bitmap.rows);
            
        }
        
        _texture= Texture::create(w, h, TextureFormat::RED,TextureFormat::RED, DataType::UNSIGNED_BYTE);
        _texture->Resource::name="Font Atlas | "+ font->name;

        glBindTexture(GL_TEXTURE_2D, _texture->getID());
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        std::vector<float> emptyData(w * h, 0);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, &emptyData[0]);

        _texture->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
        _texture->setMagFilter(TextureFilter::LINEAR);
        _texture->setMinFilter(TextureFilter::LINEAR);
    
        int x = 0;
        
        for(int i = 32; i < 128; i++) {
         
            if(FT_Load_Char(font->face, i, FT_LOAD_RENDER)){
                continue;
            }
            
            glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
          
           
            checkRenderError();
            
            characters[i].advanceX = g->advance.x >> 6;
            characters[i].advanceY = g->advance.y >> 6;
            
            characters[i].bitmapWidth = g->bitmap.width;
            characters[i].bitmapHeight = g->bitmap.rows;
            
            characters[i].bitmapLeft = g->bitmap_left;
            characters[i].bitmapTop = g->bitmap_top;
            
            characters[i].uvOffsetX = (float) x / (float) (w);
            characters[i].uvOffsetY = 0 / (float) h;
            
            x += (int) g->bitmap.width+1;
        }
        

    }
    
}