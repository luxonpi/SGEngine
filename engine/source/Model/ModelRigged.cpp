

#include "ModelRigged.h"
#include "Renderer.h"
#include "Director.h"
#include "ModelLoader.h"

namespace sge {
    
ModelRigged* ModelRigged::create(const std::string& file){
    
    ModelRigged* model= new ModelRigged();
    model->_armature= new ModelArmature();
    
    ModelLoader::getInstance()->loadIntoModel(model, model->_armature, file, ML_FLAG_ANIMATION | ML_FLAG_RIGGED);
    
    model->getRenderObject()->setMaterial(Director::getInstance()->modelDefaultMaterial->getCopy());
    model->getRenderObject()->setFrustumCulling(FrustumCulling::SPHERE);
    model->getRenderObject()->setDrawAble(true);
    model->getRenderObject()->getMaterial()->addDefine("SGE_RIGGED");
    model->getRenderObject()->setRenderLayer(Director::getInstance()->getRenderer()->getRenderLayer(RENDER_LAYER_SCENE));

    return (ModelRigged* )model;
     
}
    
    
void ModelRigged::renderWithRenderer(Renderer* renderer, RenderState* renderState){
    
    // Make sure that this is only, updates once per frame
    if(_armature->_lastFrame!=Director::getInstance()->getFrameCount()){
    
        _armature->_lastFrame=Director::getInstance()->getFrameCount();

        if (_armature) {
            
            _animationController.update();
           
            // 10%
            _animationController.setToArmature(_armature);
            if(_armature->_dirty){
                
                _armature->_dirty=false;
                _armature->updateMatrixArray();
            
            }
            
             getRenderObject()->getMaterial()->getShaderState()->setUniformMat4Array("u_bones", _armature->getMatrixArray(), false);

        }
        
    }
    
    renderer->renderMeshWithRenderState(this,getRenderObject()->getMesh(), renderState);
    
}
    
void ModelRigged::playAnimationOnChannel(std::string name, float speed, bool loop, unsigned int channel){
    
    ArmatureAnimation* animation= _armature->getAnimationWithName(name);
    
    if(animation){
        
        if(_currentAnimationName==name){
            
            _animationController.setSpeed(speed);
            
        }else{
            
            _currentAnimationName=name;
            _animationController.playAnimation(animation, channel ,speed, loop);
            
        }
        
        return;
    }
    
    std::cout << "Could not find animation named: " << name << std::endl;
    
  

}
    
void ModelRigged::stopAnimationOnChannel(unsigned int channel){
    
    
    _animationController.stopAnimationOnChannel(channel);
 
}

void ModelRigged::playAnimation(std::string name, float speed, bool loop){
    
    ArmatureAnimation* animation= _armature->getAnimationWithName(name);
    
    if(animation){
        
        if(_currentAnimationName==name){
        
            _animationController.setSpeed(speed);
        
        }else{
        
        _currentAnimationName=name;
        _animationController.playAnimation(animation,0, speed, loop);
       
        }
        
        return;
    }

    std::cout << "Could not find animation named: " << name << std::endl;

}
    
std::string ModelRigged::getCurrentAnimationName(){
    
    return _currentAnimationName;
 
}
    
ModelArmature* ModelRigged::getArmature(){

    return _armature;

}
    
void ModelRigged::setArmature(ModelArmature* armature){
        
    _armature=armature;
        
}

    
    
}