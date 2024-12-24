

#include "ModelInstanced.h"
#include "ModelLoader.h"
#include "Renderer.h"
#include "Director.h"

namespace sge {

// Instance (Child) Part
ModelInstanced::Instance::Instance(){

    _parent=NULL;
    index=0;
    getRenderObject()->setDrawAble(false);

}

ModelInstanced::Instance::~Instance(){}

void ModelInstanced::Instance::transformChanged(){
    
    Node::transformChanged();
    if(_parent) _parent->instanceChanged(this, index);

}
    
// Instance (Parent) Part
void ModelInstanced::instanceChanged(ModelInstanced::Instance* instance, unsigned int index){
    
//    glm::mat4 mvp= renderState->projection*(renderState->view*renderState->model);
    buffered=false;
    if(index>=_instances.size()) return;
    
//    _modelMatrix[index]=(_instances[index]->getModelMatrix());
//    _normalMatrix[index]=(_instances[index]->getNormalMatrix());

  //  updateVBO((int)_instances.size(), true, true);

}
    
ModelInstanced* ModelInstanced::create(std::string file){
    
        ModelInstanced* instanceObject= new ModelInstanced();
    
//        ModelLoader::loadIntoRenderObject(file, instanceObject->getRenderObject());
//        instanceObject->_vaoInstanced->copy(instanceObject->getRenderObject()->getMesh()->getVAO());
//    
//        // Vertexarray buffer muss matrix handeln können
//        AttributePointer ap1=AttributePointer(instanceObject->_bufferModel, 16, DataType::FLOAT, 0, 0, 0);
//        ap1.divisor=1;
//        instanceObject->_vaoInstanced->addAttributePointer(ap1);
//    
//        AttributePointer ap2=AttributePointer(instanceObject->_bufferNormal, 9, DataType::FLOAT, 0, 0, 0);
//        ap2.divisor=1;
//        instanceObject->_vaoInstanced->addAttributePointer(ap2);
//    
//        instanceObject->_attributePointerModel = instanceObject->_vaoInstanced->getAttributePointerForBuffer(instanceObject->_bufferModel);
//        instanceObject->_attributePointerNormal = instanceObject->_vaoInstanced->getAttributePointerForBuffer(instanceObject->_bufferNormal);
//
//        instanceObject->buffered=false;
//        instanceObject->modeule=NULL;

    
        return instanceObject;
    
}
    
ModelInstanced::Instance* ModelInstanced::createChild(){
    
        ModelInstanced::Instance* instance= new ModelInstanced::Instance();
        instance->_parent=this;
        instance->index=(unsigned int) _instances.size();
        instance->getRenderObject()->setFrustumCulling(FrustumCulling::SPHERE);
        instance->getRenderObject()->setDrawAble(false);
        this->addChild(instance);

        _instances.push_back(instance);
    
        return instance;
        
    }
    
    
    void ModelInstanced::renderWithRenderer(Renderer* renderer, RenderState* renderState){
        
       // if(!buffered){
        
//        instancesToRender.clear();
//        Vec3 camera= renderState->camera->getPosition();
//        
//        for (int i=0; i<_instances.size(); i++) {
//            
//            if(_instances[i]->getRenderObject()->hiddenForCamera[renderState->camera]) continue;
//            if(!_instances[i]->getRenderObject()->isVisible()) continue;
//            if(_instances[i]->getPosition().distance(camera)>8) continue;
//
//            instancesToRender.push_back(_instances[i]);
//            
//        }
//
//        
//
//        std::sort(instancesToRender.begin(), instancesToRender.end(), [camera](Instance* a, Instance* b) {
//        
//            return a->getPosition().distance(camera) < b->getPosition().distance(camera);
//        
//        });
//        
//        _modelMatrix.resize(instancesToRender.size());
//        _normalMatrix.resize(instancesToRender.size());
//        
//        int count=0;
//        
//        for (int i=0; i<instancesToRender.size(); i++) {
//            
//            _modelMatrix[count]=(instancesToRender[i]->getModelMatrix());
//            _normalMatrix[count]=(instancesToRender[i]->getNormalMatrix());
//            count++;
//            
//        }
//
//        if(count==0) return;
//
//        updateVBO(count, true, true);
//        buffered=true;
//            
//       // }
//        
//        renderer->renderInstancedModelWithRenderState(this, renderState);
//
//        
    }
    
    void ModelInstanced::updateVBO(int count, bool model, bool normal){
//        
//         _bufferModel->setData(&_modelMatrix[0][0][0], sizeof( glm::mat4 ) * count);
//         _bufferNormal->setData(&_normalMatrix[0][0], sizeof( glm::mat3 ) * count);

    }
    
    void ModelInstanced::updateMatrices(){
        
        
    
    }
    
    unsigned int ModelInstanced::getCount(){
        
        return (unsigned int)instancesToRender.size();
    
    }
    
    void ModelInstanced::setShaderModules(std::vector<ShaderModule*> modules){
    
//        ShaderModule* module=ShaderModule::createFromFile("support/shader/vert/VertexInstanced.glsl");
//
//        modules.push_back(module);
//        
//        ShaderModule* moduleColor= ShaderModule::getMergedModules(modules);
//        
//        Shader* shader=moduleColor->getShader();
        
     //   this->getRenderObject()->setShaderState(shader->getState());
        
    
    }
    
    void ModelInstanced::addShaderModuleExtension(ShaderModule* module, const std::string& configId){
    
//        ShaderModule* moduleInst=ShaderModule::createFromFile("support/shader/vert/VertexInstanced.glsl");
//        ShaderModule* moduleMix= ShaderModule::getMergedModules({module, moduleInst});
//
//        modeule=module;
      //  getRenderObject()->addShaderModuleExtension(moduleMix, "vertex");

    }

    
    ModelInstanced::ModelInstanced(){
        
//        ShaderModule* module=ShaderModule::createFromFile("support/shader/vert/VertexInstanced.glsl");
//        ShaderModule* diffuse=ShaderModule::createFromFile("support/shader/frag/Diffuse.glsl");
//        
//        ShaderModule* moduleColor= ShaderModule::getMergedModules({module, diffuse});
//        
////        getRenderObject()->addShaderModuleExtension(module, "vertex");
////        this->getRenderObject()->setShaderState(moduleColor->getShader()->getState());
////        this->getRenderObject()->setAlpha(false);
//        
//        getRenderObject()->setDrawAble(true);
//        getRenderObject()->setFrustumCulling(FrustumCulling::NONE);
//        
//        _bufferModel= VertexBuffer::create(NULL, 0);
//        _bufferNormal= VertexBuffer::create(NULL, 0);
//        
//        _bufferModel->setDrawType(BufferDrawType::STREAM);
//        _bufferNormal->setDrawType(BufferDrawType::STREAM);
//        
//        _vaoInstanced= VertexArrayObject::create();
        
    }
    
    ModelInstanced::~ModelInstanced(){}

}