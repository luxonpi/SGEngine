#include "Sprite.h"
#include "Renderer.h"
#include "Director.h"

namespace sge {

void Sprite::init(){
    
    getRenderObject()->setMaterial(Director::getInstance()->viewDefaultMaterial);
  
    _quad= new Quad2D();
    _quad->setColor(Color::white);
    
    getRenderObject()->setMesh(_quad->mesh);

    setContentSize(Vec2(1, 1));
    
    getRenderObject()->setFrustumCulling(FrustumCulling::NONE);
//    _scale=1;
//    _pivot.set(0.5, 0.5, 0.5);
    getRenderObject()->setDrawAble(true);

}

Sprite::Sprite(){
    init();

   // getRenderObject()->setAlpha(true);
}
    
Sprite::Sprite(Texture* texture){
    
    init();
    
    this->_texture= texture;
    _contentSize.set(texture->getSize().x, texture->getSize().y);
    _tag=2;
    //getRenderObject()->setAlpha(true);
    //getRenderObject()->setDepthFunction(DepthFunc::LEQUAL);

}
    
Sprite::Sprite(std::string file){

    init();

    _texture= Texture::get(file);
    _quad->setColor(Color::white);
    _contentSize.set(_texture->getSize().x, _texture->getSize().y);
   // getRenderObject()->setAlpha(true);
    //getRenderObject()->setDepthFunction(DepthFunc::LEQUAL);
    
}

Sprite::Sprite(int width, int height){

    init();

    _texture=NULL;
    _texture= Texture::color2x2White;
    _contentSize.set(width, height);
    //getRenderObject()->setAlpha(true);
    //getRenderObject()->setDepthFunction(DepthFunc::LEQUAL);
}

Sprite::Sprite(Color color,int width, int height){

    init();

    _texture= Texture::color2x2White;
    _quad->setColor(color);
    _contentSize.set(width, height);
    //getRenderObject()->setAlpha(true);
    //getRenderObject()->setDepthFunction(DepthFunc::LEQUAL);
}
    


void Sprite::setTexture(Texture* Texture){

    _texture=Texture;
    this->getRenderObject()->getMaterial()->getShaderState()->setUniformTexture("u_sge_mainTex", Texture, 0);
    
    if(_texture){
    
        this->getRenderObject()->getMaterial()->addDefine("SGE_TEXTURE");
    
    }else{
    
        this->getRenderObject()->getMaterial()->removeDefine("SGE_TEXTURE");

    }

//    _quad->setTexture(_texture);
   // getRenderObject()->getMaterial()->setAlbedoTexture(Texture);
// _contentSize.set(_texture->width, _texture->height, _contentSize.z);

}
    


Quad2D* Sprite::getQuad(){
    
    return _quad;
}
    

Sprite::~Sprite(){


    if(_quad) delete _quad;
    
}

void Sprite::setContentSize(const Vec2& size){
    
    _quad->setRect(0, 0, size.x, size.y);
    _contentSize=size;
    _contentBox.set(0, 0, 0, size.x, size.y, 1);
 
}
    
void Sprite::renderWithRenderer(Renderer* renderer, RenderState* renderState){
    
    renderer->renderMeshWithRenderState(this, _quad->mesh, renderState);

}

Sprite* Sprite::create(std::string file){

    return new Sprite(file);

}

Sprite* Sprite::create(int width, int height){

    return new Sprite(width, height);

}

Sprite* Sprite::create(Color color,int width, int height){

    return  new Sprite(color, width,  height);

}
    
Sprite* Sprite::create(Texture* texture){
    
    return new Sprite(texture);
        
}

}