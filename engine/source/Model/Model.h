

#ifndef SGENGINE_MODEL_H
#define SGENGINE_MODEL_H

#include "SBase.h"
#include "Mesh.h"
#include "Entity.h"

namespace sge {

    class ModelLoader;
    class Model: public Entity{

    friend ModelLoader;
        
    protected:
    
        bool init;
        
        // Common init
        void initBase();
        
        // Hidden Const/ Destructor
        Model();
        ~Model();
        
    public:
        
        // Static create method
        static Model* create(const std::string& file);
        static Model* create();

       // void setShaderState(ShaderState* shader);
            
        // Render visitor
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);

    };
    
}

#endif
