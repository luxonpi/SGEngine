#include "View.h"
#include "Director.h"

namespace sge {
    


void View::addChild(Node* Node){}
    
View::View(): Sprite(){

    getRenderObject()->setMaterial(Director::getInstance()->viewDefaultMaterial->getCopy());
    getRenderObject()->setDrawAble(false);
    
    getRenderObject()->getMaterial()->addDefine("SGE_TEXTURE");
}
    
View* View::create(float Width, float Height, Color backgroundColor){

    View* view= new  View();
    view->initWithSizeColorTexture(Width, Height, backgroundColor, NULL);
    view->getRenderObject()->setDrawAble(true);
    return view;
}
    
    
View* View::create(float Width, float Height, std::string imageFile){

    View* view= new  View();
    Texture* texture= Texture::get(imageFile);
    view->initWithSizeColorTexture(Width, Height, Color::white, texture);
    view->getRenderObject()->setDrawAble(true);
    return view;
}
    
View* View::create(float Width, float Height, Texture* texture){

    View* view= new  View();
    view->initWithSizeColorTexture(Width, Height, Color::white, texture);
    view->getRenderObject()->setDrawAble(true);
    return view;
}

void View::setMaskTexture(Texture* texture){
    
    _maskTexture=texture;
    
    if(_maskTexture) getRenderObject()->getMaterial()->addDefine("SGE_STENCIL_MASK");
    else getRenderObject()->getMaterial()->removeDefine("SGE_STENCIL_MASK");
    
    getRenderObject()->getMaterial()->getShaderState()->setUniformTexture("maskTexture", _maskTexture, 1);
    
}
    
void View::initWithSizeColorTexture(float x, float y,const Color& color, Texture* texture){

    _parentView=NULL;
    _maskTexture=NULL;
    _order=0;
    getRenderObject()->setDrawAble(true);
    getRenderObject()->setFrustumCulling(FrustumCulling::NONE);
    getRenderObject()->getMaterial()->setAlpha(true);
    getRenderObject()->setRenderLayer(Director::getInstance()->getRenderer()->getRenderLayer(RENDER_LAYER_UI));

    setOverlayColor(Color::clear);
    setSize(Vec2(x, y));
    _internalZ=0;
    _transform.setTranslationZ(_internalZ);
    _userInteractionEnabled=false;
    
    setTintColor(color);
    
    if(texture) setTexture(texture);
    else setTexture(Texture::color2x2White);
    
}
    
    void View::setTexture(Texture* texture){
    
        _texture=texture;
        if(texture) getRenderObject()->getMaterial()->addDefine("SGE_TEXTURE");
        else getRenderObject()->getMaterial()->removeDefine("SGE_TEXTURE");
        
        getRenderObject()->getMaterial()->getShaderState()->setUniformTexture("u_sge_mainTex", texture, 0);
        
    }
    
    
bool View::isUserInteractionEnabled(){
    
    return _userInteractionEnabled;

}
    
Vec2 View::getSize(){
    
    return _size;
 
}
    
void View::setSize(const Vec2& size){
    
    Sprite::setContentSize(size);
    _size.set(size);
    setContentSize(Vec2(size.x, size.y));

}
    
void View::setTextureRect(const Rectangle& rect){
    
    _textureRect=rect;
    _quad->setUVCoords(Vec2(rect.x, rect.y), Vec2(rect.x, rect.y+rect.height), Vec2(rect.x+rect.width, rect.y+rect.height), Vec2(rect.x+rect.width, rect.y));
    
    getRenderObject()->getMaterial()->getShaderState()->setUniform4f("normalTexcords", Vec4(rect.x, rect.y, rect.width, rect.height));
    
}
    
void View::setOverlayColor(Color color){

    getRenderObject()->getMaterial()->getShaderState()->setUniform4f("u_overlay_color", color.getVec4());

}
    
void View::shouldReorderSubview(View* view){
    
    
 
}
    
void View::addSubview(View* view){
    
    view->_internalZ=_internalZ+0.1;
    view->_transform.setTranslationZ(view->_internalZ);
    
    _parentView=this;
    shouldReorderSubview(view);
    Node::addChild(view);
 
}

void View::setZOrder(int order){
    
    if(_parentView) _parentView->shouldReorderSubview(this);
    _order=order;

}
    
void View::setTintColor(Color color){
    
   // if(_tintColor==color) return;
    
    _tintColor=color;
    getRenderObject()->getMaterial()->getShaderState()->setUniform4f("u_tint_color", color.getVec4());

}
    
void View::setBackgroundTexture(Texture* texture){

    Sprite::setTexture(texture);

}
 
void View::setPosition(Vec2 point){

   _transform.setTranslation(point.x, point.y,_internalZ);

}

void View::setPosition(float x, float y){

    _transform.setTranslation(x, y,_internalZ);

}






}
