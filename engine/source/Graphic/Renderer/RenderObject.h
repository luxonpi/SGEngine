

#ifndef SGENGINE_RENDEROBJECT_H
#define SGENGINE_RENDEROBJECT_H

#include "SBase.h"
#include "ShaderState.h"
#include "Transform.h"
#include "RenderState.h"
#include "ShaderModule.h"
#include "Material.h"
#include "GraphicDeviceDefines.h"
#include "Mesh.h"

enum RenderType{

    RENDER_TYPE_DYNAMIC,
    RENDER_TYPE_BATCH,
    RENDER_TYPE_INSTANCED,

};

namespace sge {
    
    class Renderer;
    class Camera;
    class Node;
    class RenderLayer;
    class Batch;

    class RenderVisiter{
    
    public:
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

    };
    
    class RenderObject{

        friend Material;
        
    private:
    
    protected:
        
        SUint _renderType;
        SUint _drawMode;
        SUint _frustumCulling;

        bool _renderAble;
        bool _isVisible;

        Material* _material;
        
        RenderLayer* _renderLayer;
        Mesh* _mesh;
        Node* _node;
    

    public:
        
        float getMeshRayIntersection(Ray* ray, Vec3& normal);
        
        Batch* _batch;
        unsigned int batchPos;
        unsigned int batchIndex;

        void transformChanged();
        
        void setRenderType(SUint renderType);
        SUint getRenderType();
        
        static RenderObject* getNullObject();
        
        RenderObject(Node* node);
        virtual ~RenderObject();
        RenderObject(const RenderObject& object);

        Node* getNode();
        
        void setMesh(Mesh* mesh);
        Mesh* getMesh();
        
        std::unordered_map<Camera*, bool> hiddenForCamera;
        
        Material* getMaterial();
        void setMaterial(Material* material);

        // Experimatnal
        void setHiddenForCamera(Camera* camera , bool visibility, bool recursive);
        void multiplicateHiddenForCameraWithCamera(Camera* camera ,Camera* camera2);
        
        RenderLayer* getRenderLayer();
        void setRenderLayer(RenderLayer* layer);
        void setRenderLayerIntern(RenderLayer* layer);
        
        bool isVisible();
        virtual void setVisible(const bool& visible);
        
        void setDrawAble(bool drawAble);
        bool getDrawAble();
        
        // Getter
        const SUint& getDrawMode();
        const SUint& getFrustumCulling();

        // Setter
        void setFrustumCulling(const SUint& frustumCulling);
        void setDrawMode(const SUint& drawMode);
   
    
};
    
}
#endif
