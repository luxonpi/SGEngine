

#include <sstream>

#include "RenderObject.h"
#include "RenderLayer.h"
#include "Node.h"

namespace sge {
    
    void RenderVisiter::renderWithRenderer(Renderer* renderer, RenderState* renderState){}

    RenderObject* RenderObject::getNullObject(){
        
        static RenderObject* _instance=NULL;
        
        if(!_instance){
            
            _instance= new RenderObject(NULL);
        }
        
        return _instance;
    }
    
    RenderObject::RenderObject(Node* node){
        
        _node=node;
        _drawMode=DrawMode::TRIANGLES;

        _batch=NULL;
        batchPos=0;
        
        _frustumCulling=FrustumCulling::SPHERE;
        _renderAble=false;
        _mesh=NULL;
        _isVisible=true;
        _renderLayer=NULL;
        _material=NULL;
        _renderType=RENDER_TYPE_DYNAMIC;
        
        setFrustumCulling(FrustumCulling::SPHERE);
        setDrawAble(false);
        
        
    }
    
    RenderObject::RenderObject(const RenderObject& object){}
    
    float RenderObject::getMeshRayIntersection(Ray* ray, Vec3& normal){
    
        sge::Mat4 tranform= _node->getModelMatrix();
        size_t polycount = _mesh->indices.size()/3.0;
        
        float result = 1.0e6f;
        float distance = 0.0f;
        Vec3 v0, v1, v2;
        
        for(size_t i=0; i<polycount; i++){
            
            // get a single triangle from the mesh
            v0=_mesh->positions[_mesh->indices[i*3]];
            v1=_mesh->positions[_mesh->indices[i*3+1]];
            v2=_mesh->positions[_mesh->indices[i*3+2]];
            
            // transform triangle to world space
            tranform.transformPoint(&v0);
            tranform.transformPoint(&v1);
            tranform.transformPoint(&v2);
            
            // test to see if the ray intersects with this triangle
            if( ray->calcTriangleIntersection(v0, v1, v2, &distance) ) {
                
                // set our result to this if its closer than any intersection we've had so far
                if( distance < result ) {
                    result = distance;
                    // assuming this is the closest triangle, we'll set our normal
                    // while we've got all the points handy
                    normal = ( v1 - v0 ).cross( v2 - v0 ).normalized();
                }
            }
        }
        
        // did we have a hit?
        if( distance > 0 ) {
            
        
            if(normal.dot(ray->getDirection())>0) normal*=-1;
            return distance;
        
        }
        
        return 0;

    }
    
    
    void RenderObject::transformChanged(){
    
        if(_batch){
        
            _batch->dirtyIndex.insert(batchIndex);
        
        }
    
    }
    
    void RenderObject::setRenderType(SUint renderType){
    
        SUint prev=_renderType;
        _renderType=renderType;
        
        if(_renderLayer){
        
            _renderLayer->renderObjectChangedRenderType(this,prev);
            
        }
        
    
    }
    
    SUint RenderObject::getRenderType(){
    
        return _renderType;
    
    }
    
    
    RenderObject::~RenderObject(){
    
        if(_renderLayer){
         
            _renderLayer->removeRenderObject(this);
        
        }
    
    }
    
   
    Node* RenderObject::getNode(){
    
        return _node;
    }
    
    void RenderObject::setMesh(sge::Mesh *mesh){
    
        _mesh=mesh;
        if(_node) _node->setContentBox(mesh->contentBox);

    }
    
    Mesh* RenderObject::getMesh(){
    
        return _mesh;
    
    }
    
    RenderLayer* RenderObject::getRenderLayer(){
    
        return _renderLayer;
    
    }
    
    void RenderObject::setRenderLayerIntern(RenderLayer* layer){
    
        _renderLayer=layer;
    
    }
    
    void RenderObject::setRenderLayer(RenderLayer* layer){
        
        if(_renderLayer && _renderLayer!=layer) _renderLayer->removeRenderObject(this);
        
        if(layer){
        layer->insertRenderObject(this);
        _renderLayer=layer;
            
        }
    }
    

    Material* RenderObject::getMaterial(){
    
        return _material;
    
    }
    
    void RenderObject::setMaterial(Material* material){
        
        if(_material){
        
            _material->_holders.erase(this);
        
        }
    
        _material=material;
        
        _material->_holders.insert(this);
        
        for (int i=0; i<_node->_children.size(); i++) {
            
            _node->_children[i]->getRenderObject()->setMaterial(material);
            
        }
        


    
    }
    
    bool RenderObject::isVisible(){
        
        if(!_isVisible) return false;
    
        if(!_node->_parent) return true;
        else return _node->_parent->getRenderObject()->isVisible();
        
    }
    
    void RenderObject::setVisible(const bool& visible){
        
        _isVisible=visible;
        
//        for (int i=0; i<_node->_children.size(); i++) {
//            
//            _node->_children[i]->getRenderObject()->setVisible(visible);
//            
//        }

    }
    
    void RenderObject::setHiddenForCamera(Camera* camera , bool visibility, bool recursive){
        
        hiddenForCamera[camera]=visibility;
        
        if(!recursive || !_node) return;
        
        for (int i=0; i<_node->_children.size(); i++) {
            
            _node->_children[i]->getRenderObject()->setHiddenForCamera(camera, visibility, recursive);
            
        }
        
    }
    
    void RenderObject::multiplicateHiddenForCameraWithCamera(Camera* camera ,Camera* camera2){
        
        if(!_node) return;
        
            hiddenForCamera[camera]= hiddenForCamera[camera] || hiddenForCamera[camera2];
        
        for (int i=0; i<_node->_children.size(); i++) {
            
            _node->_children[i]->getRenderObject()->multiplicateHiddenForCameraWithCamera(camera, camera2);
            
        }
        
    }
    
    
   
    
    void RenderObject::setDrawAble(bool drawAble){
    
        _renderAble=drawAble;

    }
    
    bool RenderObject::getDrawAble(){
    
        return _renderAble;
    }

    const SUint &RenderObject::getFrustumCulling(){
    
        return _frustumCulling;
    
    }
    
    void RenderObject::setFrustumCulling(const SUint& frustumCulling){
    
        _frustumCulling=frustumCulling;
    
    }
    
    void RenderObject::setDrawMode(const SUint& drawMode){
        
        _drawMode=drawMode;
        
    }
    
    const SUint& RenderObject::getDrawMode(){
        
        return _drawMode;
        
    }
    
    
}
