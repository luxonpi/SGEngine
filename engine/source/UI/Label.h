

#ifndef SGENGINE_LABEL_H
#define SGENGINE_LABEL_H

#include <stdio.h>
#include "Sprite.h"
#include "View.h"

#include "FontManager.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace sge {

    
    
    
class Label: public View{
    
protected:
    
    bool _dirty;
    Color _mainColor;
    Mesh* _mesh;
    
    Font* _font;
    FontAtlas* _fontAtlas;
    float _fontSize;
    
    std::string _text;
    
    float _wordSpacing;
    float _letterSpacing;
    float _lineHeight;
    
    float _maxWidth;

    unsigned int numbeOfChars;
    
    Vec2 _rectSize;
   
    Label();
    ~Label();
    
    void render();
    
    void updateMesh();
    
    void updateColorStatic();
    
public:
    
    virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

    void setColor(const Color& color);
    void setMaxWidth(float maxWidth);
    void setLetterSpacing(float letterSpacing);
    void setWordSpacing(float wordSpacing);
    void setLineHeight(float lineHeight);
    void setText(const std::string& text);
    
    static Label* create(std::string text, std::string file, float size);
    
    void initWithFile(std::string file, float size);
    
    
};
    
}

#endif
