

#include "RenderLayer.h"
#include "Director.h"

using namespace std;

namespace sge {
    
    Batch::Batch(){
    
        dirty=false;
    
    }
    
    
    void Batch::recalc(){
    
        std::set<int>::iterator it;
        
        for (it= dirtyIndex.begin(); it!=dirtyIndex.end(); ++it) {
            
            RenderObject* object= _objects[*it];
            Mesh* m=object->getMesh();
            
            int baseIndex= object->batchPos;
        
            for (int i=0; i<m->positions.size(); i++) {
                
                Vec4 p(m->positions[i].x,m->positions[i].y,m->positions[i].z,1);
                p=object->getNode()->getModelMatrix()*p;
                mesh->positions[baseIndex+i].set(p.x, p.y, p.z);
                
                Vec3 n(m->normals[i].x,m->normals[i].y,m->normals[i].z);
                n=object->getNode()->getNormalMatrix()*n;
                mesh->normals[baseIndex+i].set(n.x, n.y, n.z);
                
                Vec3 t(m->tangents[i].x,m->tangents[i].y,m->tangents[i].z);
                t=object->getNode()->getNormalMatrix()*t;
                mesh->tangents[baseIndex+i].set(t.x, t.y, t.z);
                
            }
            
        }
        
        mesh->update();
        
        dirtyIndex.clear();

    }

    RenderLayer::~RenderLayer(){}
    RenderLayer::RenderLayer(const RenderLayer& layer){}
    
    unsigned int RenderLayer::sortSteps=4;

    RenderLayer* RenderLayer::create(){
        
        return new RenderLayer();
    
    }
    
    RenderLayer::RenderLayer(){

        depthTest=true;
        depthFunc= DepthFunc::LESS;
        depthWritingEnabled=true;
      
    }

    void RenderLayer::insertRenderObject(RenderObject* renderObject){

        if(!renderObject) return;
        if(!renderObject->getDrawAble()) return;

        renderObject->setRenderLayerIntern(this);
        _renderObjects.push_back(renderObject);
        
        if (renderObject->getRenderType()==RENDER_TYPE_DYNAMIC) {
        
            _dynamicObjects.insert(renderObject);
        
        }else if(renderObject->getRenderType()==RENDER_TYPE_BATCH){
        
            Batch* batch=NULL;
            if(_batches.find(renderObject->getMaterial())!=_batches.end()){
                
                batch=_batches[renderObject->getMaterial()];
                
            }
            
            if(!batch){
                
                batch= new Batch();
                batch->mesh= new Mesh(MESH_NORMALS | MESH_COLORS | MESH_TEXCOORDS | MESH_TANGENTS);
                batch->material= renderObject->getMaterial()->getCopy();
                batch->material->addDefine("SGE_PRECOMPUTED");
                _batches.insert(std::make_pair(renderObject->getMaterial(), batch));
                
            }
            
            insertObjectToBatch(renderObject,batch);
        }
        
        
    }
    
    void RenderLayer::renderObjectChangedRenderType(RenderObject* object, SUint previousType){
    
        if(previousType==RENDER_TYPE_DYNAMIC){
        
            _dynamicObjects.erase(object);
        
        }
        
        
        if (object->getRenderType()==RENDER_TYPE_DYNAMIC) {
            
            _dynamicObjects.insert(object);
            
        }else if(object->getRenderType()==RENDER_TYPE_BATCH && object->getDrawAble()){
            
            Batch* batch=NULL;
            if(_batches.find(object->getMaterial())!=_batches.end()){
            
                batch=_batches[object->getMaterial()];
            
            }
            
            if(!batch){
            
                batch= new Batch();
                batch->mesh= new Mesh(MESH_NORMALS | MESH_COLORS | MESH_TEXCOORDS | MESH_TANGENTS);
                batch->material= object->getMaterial()->getCopy();
                batch->material->addDefine("SGE_PRECOMPUTED");
                _batches.insert(std::make_pair(object->getMaterial(), batch));

            }
            
            insertObjectToBatch(object,batch);
            
        }
    
    }
    
    void RenderLayer::insertObjectToBatch(RenderObject* object, Batch* batch){
        
        object->batchIndex=(int) batch->_objects.size();
        batch->_objects.push_back(object);
    
        Mesh* m= object->getMesh();
        Mesh* bm= batch->mesh;
        bm->Resource::name=m->name +" | batch";
        
        int baseIndex=(int) bm->positions.size();
        
        object->batchPos=baseIndex;
        object->_batch=batch;

        bm->positions.insert(bm->positions.end(), m->positions.begin(), m->positions.end());
        bm->texCoords.insert(bm->texCoords.end(), m->texCoords.begin(), m->texCoords.end());
        bm->colors.insert(bm->colors.end(), m->colors.begin(), m->colors.end());
        bm->normals.insert(bm->normals.end(), m->normals.begin(), m->normals.end());
        bm->tangents.insert(bm->tangents.end(), m->tangents.begin(), m->tangents.end());

      //  int indexOffset= (int) bm->indices.size();
        
        for (int i=0; i<m->indices.size(); i++) {
            
            bm->indices.push_back(baseIndex+m->indices[i]);
            
        }

        for (int i=baseIndex; i<bm->positions.size(); i++) {
            
            Vec4 p(bm->positions[i].x,bm->positions[i].y,bm->positions[i].z,1);
            p=object->getNode()->getModelMatrix()*p;
            bm->positions[i].set(p.x, p.y, p.z);
            
            Vec3 n(bm->normals[i].x,bm->normals[i].y,bm->normals[i].z);
            n=object->getNode()->getNormalMatrix()*n;
            bm->normals[i].set(n.x, n.y, n.z);
            
            Vec3 t(bm->tangents[i].x,bm->tangents[i].y,bm->tangents[i].z);
            t=object->getNode()->getNormalMatrix()*t;
            bm->tangents[i].set(t.x, t.y, t.z);
            
        }
    
        bm->update();
        
        
    }
    
    void RenderLayer::removeRenderObject(RenderObject* renderObject){
        
        for (int i=0; i<_renderObjects.size(); i++) {
            
            if(renderObject==_renderObjects[i]){
            
                _renderObjects.erase(_renderObjects.begin()+i);
                break;
            
            }
            
        }
        
        
        std::set<RenderObject*>::iterator it;
        
        for (it=_dynamicObjects.begin(); it!=_dynamicObjects.end(); ++it) {
            
            if(renderObject==*it){
                
                _dynamicObjects.erase(it);
                break;
                
            }
            
        }
        
        
        
    }


  
    
} // Namespace end
