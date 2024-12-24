

#include "Compositor.h"
#include "Director.h"
#include "Renderer.h"

namespace sge {

Compositor::Compositor(){

    _view= View::create(1, 1, Color::white);
    _view->setPosition(0, 0);
    _view->setZOrder(10000);
    _view->getQuad()->setFlipUVVertical(true);
    _view->getRenderObject()->getMaterial()->setAlpha(true);
    
    _view->getRenderObject()->setMaterial(Director::getInstance()->viewDefaultMaterial->getCopy());
    _view->getRenderObject()->getMaterial()->setDepthFunction(DepthFunc::ALWAYS);
    _view->getRenderObject()->setRenderLayer(NULL);
    _view->setContentSize(Vec2(1, 1));

    _camera= Camera::create2D(100, 100);
    _camera->setWindowsSize(1, 1);

}
    
void Compositor::compose(Texture* texture, FrameBuffer* buffer, const BlendFunc& blendfunc,  ShaderModule* shaderModule, float opacity){
    
    if(shaderModule==NULL){
        
        _view->getRenderObject()->getMaterial()->setShaderModule(ShaderModule::get("sge/shader/View.glsl"));
        
    }else{
        
        _view->getRenderObject()->getMaterial()->setShaderModule(shaderModule);
        
    }
    
    
    _view->setTexture(texture);
    

    _view->getRenderObject()->getMaterial()->setBlendFunc(blendfunc);
    _view->getRenderObject()->getMaterial()->_isDirty=true;

    _view->setTintColor(Color(255, 255, 255, opacity));

    Director::getInstance()->getRenderer()->renderObject(_view->getRenderObject(), buffer, _camera);
    
}
    

}
