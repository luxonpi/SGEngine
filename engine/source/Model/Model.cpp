

#include "Model.h"
#include "Texture.h"
#include "Renderer.h"
#include "ModelLoader.h"
#include "Director.h"

namespace sge {
    
    // Const/ Destructor
    Model::Model(){

        initBase();
    
    }
    Model::~Model(){}
    
    // Basic init
    void Model::initBase(){
    
        getRenderObject()->setMaterial(Director::getInstance()->modelDefaultMaterial->getCopy());
        getRenderObject()->setFrustumCulling(FrustumCulling::SPHERE);
        getRenderObject()->setDrawAble(true);
        getRenderObject()->setRenderLayer(Director::getInstance()->getRenderer()->getRenderLayer(RENDER_LAYER_SCENE));
        
    }
    
    // Load with the model loader
    Model* Model::create(const std::string& file){
        
        Model* model= new Model();
        ModelLoader::getInstance()->loadIntoModel(model, NULL, file, 0);
        return model;
        
    }
    
    Model* Model::create(){
        
        Model* model= new Model();
        return model;
    
    }
    
    // Render visitor
    void Model::renderWithRenderer(Renderer* renderer, RenderState* renderState){
        
        renderer->renderMeshWithRenderState(this, getRenderObject()->getMesh(), renderState);
        
    }
    
    
}