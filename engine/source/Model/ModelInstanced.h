

#ifndef SGENGINE_MODELINSTANCED_H
#define SGENGINE_MODELINSTANCED_H

#include <stdio.h>

#include "SBase.h"
#include "Model.h"

namespace sge {
    
class ModelInstanced: public Model{
    
public:
    
    // Instance - Child
    class Instance: public Entity{
        
        friend ModelInstanced;
        
    private:
        

        unsigned int index;
        ModelInstanced* _parent;
        
        Instance();
        ~Instance();
        
        void transformChanged();
        
    };
    
    // Instanced Model - Parent
    friend Instance;
    
    private:
    
        ModelInstanced();
        ~ModelInstanced();
    
    
        std::vector<Mat4> _modelMatrix;
        std::vector<Mat4> _normalMatrix;
    
        void updateMatrices();
        void updateVBO(int count, bool model, bool normal);
        void instanceChanged(Instance* instance, unsigned int index);
    
    bool buffered;

    ShaderModule* modeule;

    public:
    std::vector<Instance*> instancesToRender;

    std::vector<Instance*> _instances;

        VertexArrayObject* _vaoInstanced;
        unsigned int getCount();
    
        VertexBuffer* _bufferModel;
        VertexBuffer* _bufferNormal;
    
        AttributePointer* _attributePointerModel;
        AttributePointer* _attributePointerNormal;
    
        void setShaderModules(std::vector<ShaderModule*> modules);
        void addShaderModuleExtension(ShaderModule* module, const std::string& configId);
    
        static ModelInstanced* create(std::string file);
    
        Instance* createChild();
        
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

};
    
}

#endif