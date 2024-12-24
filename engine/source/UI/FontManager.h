

#ifndef SGENGINE_FONTMANAGER_H
#define SGENGINE_FONTMANAGER_H

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "SBase.h"
#include "FontAtlas.h"

namespace sge {
    
class Font{

public:
  
    std::string file;
    std::string name;
    FT_Face     face;

};
    
class FontManager{

private:
    
    Font* createNewFontFromFile(const std::string& file);
    FontAtlas* createNewFontAtlasFromFileAndSize(Font* font, float size);

    std::map<std::string, Font*> _fontMap;
    std::map<std::string, FontAtlas*> _fontAtlasMap;

    FT_Library library;
    static FontManager* _instance;
    
    FontManager();
    ~FontManager();
    
public:
    
    Font* getFont(const std::string& file);
    FontAtlas* getFontAtlasForFontAndSize(Font* font, float size);
    
    static FontManager* getInstance();

};

}

#endif