

#ifndef SGENGINE_RENDERLAYER_H
#define SGENGINE_RENDERLAYER_H

#include "SBase.h"
#include "SMath.h"

#include "RenderObject.h"
#include "SCamera.h"
#include "FrameBuffer.h"

namespace sge {
    
    class Renderer;
    
    class Batch: public Node{
    
    public:
        Batch();
        void recalc();
        
        std::set<int> dirtyIndex;
        std::vector<RenderObject*> _objects;
        bool dirty;
        Material* material;
        Mesh* mesh;
    
    };
    
    class RenderLayer{
    
        friend Renderer;
        
    private:

        static unsigned int sortSteps;
        
    protected:
        
        RenderLayer();
        RenderLayer(const RenderLayer& layer);
        ~RenderLayer();
        
        std::vector<RenderObject*> _renderObjects;
        
        std::set<RenderObject*> _dynamicObjects;
        std::set<Batch*> _batchedObjects;
        
        void insertObjectToBatch(RenderObject* object, Batch* batch);
        
    public:
        
        std::unordered_map<Material*, Batch*> _batches;
        void renderObjectChangedRenderType(RenderObject* object, SUint previousType);
        
        static RenderLayer* create();

        bool depthTest;
        bool depthWritingEnabled;
        SUint depthFunc;

        void insertRenderObject(RenderObject* renderObject);
        void removeRenderObject(RenderObject* renderObject);
        void reorderRenderObject(RenderObject* renderObject);

    };
    
} // Namespace end

#endif