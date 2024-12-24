

#include "Renderer.h"

#include <sstream>

#include "SMath.h"
#include "Shader.h"
#include "Mesh.h"
#include "Director.h"
#include "Benchmark.h"
#include "Compositor.h"

#include "glInclude.h"

using namespace std;

namespace sge {

    Renderer::~Renderer(){}
    Renderer::Renderer(){
    
        for (int i=0; i<16; i++) {
            _boundTextures[i]=NULL;
        }
        
        _uploadedMaterial=NULL;
        _uploadedShader=NULL;
        blendingEnabled=false;
        blendFunc= BlendFunc::NORMAL;
        depthFunc=-1;
        cullFace=-1;
        
        for (int i=0; i<20; i++) {
            
            _layer[i]= RenderLayer::create();
            
        }
        
        _layer[RENDER_LAYER_UI]->depthTest=false;
        
    }
    
    RenderLayer* Renderer::getRenderLayer(unsigned int index){
    
        return _layer[index];
    
    }
    
    void Renderer::uploadTexture(Texture* texture, uint position){
        
        if(!texture) return;
        if(position>GL_MAX_TEXTURE_UNITS) return;
        if(_boundTextures[position]==texture) return;
        
        GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
        
        if(texture==NULL){
            
            gdevice->bindTexture(NULL, position);
            _boundTextures[position]=NULL;
            
            return;
        }
        
        gdevice->bindTexture(texture, position);
        checkRenderError();
        
        _boundTextures[position]=texture;
        
        Benchmark::getInstance()->addToCounter("texSwitches", 1);
        
        checkRenderError();
        
    }

    void Renderer::uploadMaterial(Material* material, const std::string& defines){
        
        if(_uploadedMaterial==material && defines.length()==0 && !material->_isDirty) return;

        material->_isDirty=false;
        
        _uploadedMaterial=material;
    
        GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
        
        Shader* shader=material->getActiveShader();
        if(defines.length()>0){
        
            Shader* s=material->getActiveShader(defines);
            if(s) shader=s;
        
        }

        shader->bind();
        shader->updateDirtyShaderStates();
        _uploadedShader=shader;
        
//        Director::getInstance()->globalShaderState.uploadToShader(_uploadedShader);
//        shader->getParentModule()->getGlobalShaderState()->uploadToShader(shader);
        material->getShaderState()->uploadToShader(shader);
        
        if(material->hasAlpha()){
        
            blendingEnabled=true;
            
            if(!blendingEnabled) gdevice->setBlendingEnabled(true);
            
            if(material->getBlendFunc().src!=blendFunc.src || material->getBlendFunc().dst!=blendFunc.dst){
                
                gdevice->setBlendFunc(material->getBlendFunc());
                blendFunc=material->getBlendFunc();
        
            }
        
        }else if(blendingEnabled){
        
            blendingEnabled=false;
            gdevice->setBlendingEnabled(false);

        }
        
        if(material->getDepthFunction()!=depthFunc){
        
            depthFunc=material->getDepthFunction();
            gdevice->setDepthFunc(material->getDepthFunction());
        
        }
        
        if(material->getCullFaceSide()!=cullFace){
            
            cullFace=material->getCullFaceSide();
            gdevice->setCullFace(material->getCullFaceSide());
            
        }
        
        
        
    }
    
    

    void Renderer::renderObject(RenderObject* renderObject, FrameBuffer* framebuffer, Camera* camera, const std::string& defines){
    
        _state.camera=camera;
        
        GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
        SUint vao=0;
        
        RenderObject* ro =renderObject;
        
        checkRenderError();
        framebuffer->bind();
        
        if(vao!=ro->getMesh()->getVAO()->getID()){
                
            vao=ro->getMesh()->getVAO()->getID();
            ro->getMesh()->getVAO()->bind();
                
        }
        
        uploadMaterial(ro->getMaterial(),defines);
            
        _state.model=ro->getNode()->getModelMatrix();
        _state.view=camera->getViewMatrix();
        _state.projection=camera->getProjectionMatrix();
     
        ro->getNode()->renderWithRenderer(this, &_state);
        
        gdevice->bindVertexArrayObject(NULL);
        framebuffer->unbind();
        
        checkRenderError();
        
    
    }
    
    void Renderer::renderLayer(RenderLayer* layer, FrameBuffer* framebuffer, Camera* camera, const std::string& defines){
    
        _state.camera=camera;
        
        GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
        gdevice->setDepthTestEnabled(layer->depthTest);
        gdevice->setDepthFunc(layer->depthFunc);
        gdevice->setDepthWritingEnabled(layer->depthWritingEnabled);
                
        SUint vao=0;
        
        checkRenderError();
        framebuffer->bind();
        
        std::set<RenderObject*>::iterator it;
        for (it=layer->_dynamicObjects.begin(); it!=layer->_dynamicObjects.end(); ++it) {
            
            RenderObject* ro =(*it);
            if(ro->hiddenForCamera[camera]) continue;
            if(!ro->isVisible()) continue;
            if(!ro->getMesh()) continue;
            
            
            if(defines=="posOnly" && ro->getMesh()->getVAO_PositionOnly()){
            
                if(vao!=ro->getMesh()->getVAO_PositionOnly()->getID()){
                    
                    vao=ro->getMesh()->getVAO_PositionOnly()->getID();
                    ro->getMesh()->getVAO_PositionOnly()->bind();
                    
                }
            
            }else{
            
                if(vao!=ro->getMesh()->getVAO()->getID()){
                    
                    vao=ro->getMesh()->getVAO()->getID();
                    ro->getMesh()->getVAO()->bind();
                    
                }
            
                
            }
            
            uploadMaterial(ro->getMaterial(), defines);
            
            _state.model=ro->getNode()->getModelMatrix();
            _state.view=camera->getViewMatrix();
            _state.projection=camera->getProjectionMatrix();
            
            ro->getNode()->renderWithRenderer(this, &_state);
            
        }
        
        
        
        std::unordered_map<Material*, Batch*>::iterator itb;
        
        for (itb=layer->_batches.begin(); itb!=layer->_batches.end(); ++itb) {
    
            Batch* ro = itb->second;
            
            if(ro){
                
                if(ro->dirtyIndex.size()>0){
                    
                    ro->recalc();
                
                }
                
                ro->mesh->getVAO()->bind();
                
                uploadMaterial(ro->material, defines);
                
                _state.model=Mat4::identity();
                _state.view=camera->getViewMatrix();
                _state.projection=camera->getProjectionMatrix();
                
                Benchmark::getInstance()->addToCounter("drawCalls", 1);
                Benchmark::getInstance()->addToCounter("triCount", ro->mesh->indices.size()/3.);
                
                GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
                
                setGlobalUniformsToShader(ro, &_state, _uploadedShader);
                
                timer.pause();
                
                gdevice->drawElements(DrawMode::TRIANGLES, (unsigned int) ro->mesh->indices.size(), 0);
                
            }

            
            
        }
        
    
    
    

        gdevice->bindVertexArrayObject(NULL);
        framebuffer->unbind();
        
        checkRenderError();
        
    }

  
  
    void Renderer::renderMeshWithRenderState(Node* node, Mesh* mesh, RenderState* renderState){
    
        if(node==NULL) return;
        timer.run();

        Benchmark::getInstance()->addToCounter("drawCalls", 1);
        Benchmark::getInstance()->addToCounter("triCount", mesh->indices.size()/3.);
        
        GraphicDevice* gdevice=Director::getInstance()->getGraphicDevice();
        
        setGlobalUniformsToShader(node, renderState, _uploadedShader);

        timer.pause();
        
        gdevice->drawElements(renderState->drawMode, (unsigned int) mesh->indices.size(), 0);
 
        checkRenderError();
            
    }
    
    void Renderer::renderInstancedModelWithRenderState(ModelInstanced* instance,RenderState* renderState){
    
        timer.run();

        Benchmark::getInstance()->addToCounter("drawCalls", 1);
        Benchmark::getInstance()->addToCounter("triCount", instance->getRenderObject()->getMesh()->indices.size()/3.* instance->getCount());

        
        instance->getRenderObject()->getMaterial()->getShaderState()->uploadToShader(_uploadedShader);

//        gdevice->setCullFace(CullFace::NONE);
//        setGlobalUniformsToShader(instance, renderState, shader);
//
//        int modelpos = glGetAttribLocation(shader->getID(), "instance_model");
//        int normalpos = glGetAttribLocation(shader->getID(), "instance_normal");
//        
//        instance->_attributePointerNormal->position=normalpos;
//        instance->_attributePointerModel->position=modelpos;
//        instance->_vaoInstanced->updateImmediately();
//        
//        
   
        instance->_vaoInstanced->bind();
        timer.pause();

        sirnicDrawElementsInstanced( GL_TRIANGLES, (unsigned int) instance->getRenderObject()->getMesh()->indices.size(),
                                        GL_UNSIGNED_INT, (GLvoid*)(0),
                                        instance->getCount());
     
        instance->_vaoInstanced->unbind();


    }
    
    void Renderer::setGlobalUniformsToShader(Node* node, RenderState* renderState, Shader* shader){
    
        
    
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_MVP_MATRIX)){
            
            Mat4 mvp= renderState->camera->getViewProjectionMatrix()*renderState->model;
            shader->setUniform4m(&mvp[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_MVP_MATRIX]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_MODEL_MATRIX)){
            
            shader->setUniform4m(&renderState->model[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_MODEL_MATRIX]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_VIEW_MATRIX)){
            
            Mat4 view=renderState->camera->getViewMatrix();
            shader->setUniform4m(&view[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_VIEW_MATRIX]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_NORMAL_MATRIX)){
            
            Mat4 normalMatrix =node->getNormalMatrix();
            shader->setUniform3m(&normalMatrix.getMat3Array()[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_NORMAL_MATRIX]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_PROJECTION_MATRIX)){
            
            Mat4 proj=renderState->camera->getProjectionMatrix();
            shader->setUniform4m(&proj[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_PROJECTION_MATRIX]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_INVERSEPROJECTION)){
            
            Mat4 inverseproj=renderState->camera->getInverseViewProjectionMatrix();
            shader->setUniform4m(&inverseproj[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_INVERSEPROJECTION]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_PROJECTION_VIEW_MATRIX)){
            
            Mat4 viewproj=renderState->camera->getViewProjectionMatrix();
            shader->setUniform4m(&viewproj[0], false, shader->_engineUniformPositions[SHADER_UNIFORM_PROJECTION_VIEW_MATRIX]);
        
        }
        
        
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_CAMWORLDPOS)){
            
            Vec3 camPos=renderState->camera->transform().getTranslation();
            shader->setUniform3f(camPos.x, camPos.y, camPos.z, shader->_engineUniformPositions[SHADER_UNIFORM_CAMWORLDPOS]);
            
        }
        
        if(shader->uniformBitmap.test(SHADER_UNIFORM_GLOBAL_TIME)){
            
            shader->setUniform1f(Director::getInstance()->getTime(), shader->_engineUniformPositions[SHADER_UNIFORM_GLOBAL_TIME]);
            
        }
        
        
        checkRenderError();
        


     
     
    
    
    }
    
    
    

    


}


