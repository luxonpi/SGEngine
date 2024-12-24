

#include "Label.h"
#include "Director.h"

using namespace std;

namespace sge {
    
Label::Label(){

    //getRenderObject()->setAlpha(true);
    getRenderObject()->setDrawAble(true);

}
    
Label::~Label(){}

Label* Label::create(std::string text, std::string file, float size){
    
    Label* label= new Label();
    label->initWithFile(file, size);
    label->_fontSize=size;
    label->setText(text);
    label->getRenderObject()->setDrawAble(true);
    return label;
}
    
void Label::setMaxWidth(float maxWidth){

    if(maxWidth!=_maxWidth) _dirty=true;
    _maxWidth=maxWidth;
    
    if(_dirty){
        updateMesh();
        _dirty=false;
    
    }

}
    
void Label::setLetterSpacing(float letterSpacing){

    if(letterSpacing!=_letterSpacing) _dirty=true;
    _letterSpacing=letterSpacing;
 
    if(_dirty){
        updateMesh();
        _dirty=false;
        
    }
}
    
void Label::setWordSpacing(float wordSpacing){

    if(wordSpacing!=_wordSpacing) _dirty=true;
    _wordSpacing=wordSpacing;

    if(_dirty){
        updateMesh();
        _dirty=false;
        
    }
}
    
void Label::setLineHeight(float lineHeight){

    if(_lineHeight!=lineHeight) _dirty=true;
    _lineHeight=lineHeight;
    
    if(_dirty){
        updateMesh();
        _dirty=false;
        
    }
}
    
void Label::setColor(const Color& color){
    
    bool change= _mainColor==color;
    _mainColor=color;
    
    if(!change) updateColorStatic();

}
    
void Label::renderWithRenderer(Renderer* renderer, RenderState* renderState){

    if(_dirty){
    
        updateMesh();
        _dirty=false;
    
    }
    
    renderer->renderMeshWithRenderState(this, _mesh, renderState);
}
    
void Label::initWithFile(std::string file, float size){
    
    std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
    
    _font= FontManager::getInstance()->getFont(fullPath);
    
    if(!_font){
    
        std::cout<< "Could not load font: "<< file << endl;
        return;

    }
    
    _mesh= new Mesh(MESH_COLORS | MESH_TEXCOORDS);
    getRenderObject()->setMesh(_mesh);
    
    _dirty=false;
    _mainColor=Color::white;
    
    _wordSpacing=2;
    _letterSpacing=1;
    _lineHeight=size*0.9;
    _maxWidth=-1;
    
    _fontAtlas= FontManager::getInstance()->getFontAtlasForFontAndSize(_font, size);
    
    getRenderObject()->setMaterial(Director::getInstance()->fontDefaultMaterial->getCopy());
    getRenderObject()->getMaterial()->setDepthFunction(DepthFunc::ALWAYS);
    

    setZOrder(10000);
    

   // _mesh->material.setAlbedoTexture(_fontAtlas->getTexture());
 //   this->getRenderObject()->getMaterial()->setAlbedoTexture(_fontAtlas->getTexture());

    this->getRenderObject()->getMaterial()->getShaderState()->setUniformTexture("u_sge_mainTex", _fontAtlas->getTexture(), 0);
    
    this->setTexture(_fontAtlas->getTexture());
    
    _size.set(_fontAtlas->getTexture()->getSize().x ,_fontAtlas->getTexture()->getSize().y);
    this->setContentSize(Vec2(_fontAtlas->getTexture()->getSize().x ,_fontAtlas->getTexture()->getSize().y));

}
    
void Label::setText(const std::string& text){

    if(text==_text) return;
    
    _text=text;
    updateMesh();
    
}
    
void Label::updateMesh(){
    
    _mesh->clear();
    
    float x=0;
    float y=0;
    
    float fw=_fontAtlas->getTexture()->getSize().x;
    float fh=_fontAtlas->getTexture()->getSize().y;
    
    bool hasMax= !(_maxWidth==-1);
    
    for (int i=0; i<_text.size(); i++) {
        
        int c=_text[i];
        
        float x2 = x + _fontAtlas->characters[c].bitmapLeft;
        float y2 = -y - _fontAtlas->characters[c].bitmapTop;
        float w = _fontAtlas->characters[c].bitmapWidth;
        float h = _fontAtlas->characters[c].bitmapHeight;
        
        x += _fontAtlas->characters[c].advanceX+_letterSpacing;
        y += _fontAtlas->characters[c].advanceY;
        
        if(hasMax && x>= _maxWidth){
            
            x=0;
            y-=_lineHeight;
            
        }
        
        if(c==10){
           
           x=0;
           y-=_lineHeight;
           
        }
        
        if(c==32) x+= _wordSpacing;
        
        if (!w || !h)
            continue;
        
        Vec3 color=_mainColor.getVec3();
        
        // Triangle 1
        _mesh->indices.push_back((unsigned int) _mesh->positions.size());
        _mesh->positions.push_back(Vec3(x2 ,-y2 ,0));
        _mesh->texCoords.push_back(Vec2(_fontAtlas->characters[c].uvOffsetX, _fontAtlas->characters[c].uvOffsetY));
        _mesh->colors.push_back(color);
        
        _mesh->indices.push_back((unsigned int) _mesh->positions.size());
        _mesh->positions.push_back(Vec3(x2 ,-y2-h ,0));
        _mesh->texCoords.push_back(Vec2(_fontAtlas->characters[c].uvOffsetX, _fontAtlas->characters[c].uvOffsetY+ _fontAtlas->characters[c].bitmapHeight / fh));
        _mesh->colors.push_back(color);
        
        _mesh->indices.push_back((unsigned int) _mesh->positions.size());
        _mesh->positions.push_back(Vec3(x2 + w ,-y2 ,0));
        _mesh->texCoords.push_back(Vec2( _fontAtlas->characters[c].uvOffsetX + _fontAtlas->characters[c].bitmapWidth /fw, _fontAtlas->characters[c].uvOffsetY));
        _mesh->colors.push_back(color);
        
   
        // Triangle 2
        _mesh->indices.push_back((unsigned int) _mesh->positions.size()-2);
        
        _mesh->indices.push_back((unsigned int) _mesh->positions.size());
        _mesh->positions.push_back(Vec3(x2+w ,-y2-h ,0));
        _mesh->texCoords.push_back(Vec2(_fontAtlas->characters[c].uvOffsetX+ _fontAtlas->characters[c].bitmapWidth / fw, _fontAtlas->characters[c].uvOffsetY + _fontAtlas->characters[c].bitmapHeight / fh ));
        _mesh->colors.push_back(color);
        
        _mesh->indices.push_back((unsigned int) _mesh->positions.size()-2);
        
    }
    
    if(hasMax) x= _maxWidth;
    
    _size.set(x ,_fontSize);
    this->setContentSize(Vec2(x ,_fontSize));
    
    
    _mesh->update();

}
    
void Label::updateColorStatic(){
    
    Vec3 color= _mainColor.getVec3();
    for (int i=0; i<_mesh->colors.size(); i++) {
        
        _mesh->colors[i]= color;
        
    }
    
    _mesh->update();


}

    

    

}