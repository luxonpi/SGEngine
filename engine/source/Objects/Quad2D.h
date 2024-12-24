

#ifndef SGENGINE_QUAD2D_H
#define SGENGINE_QUAD2D_H

#include <iostream>
#include <vector>

#include "SMath.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"
#include "Color.h"

namespace sge {
    
    class Quad2D{

    private:
        Texture* _texture;
    
    public:
        
        void setFlipUVVertical(bool flip);
        
        std::vector<SFloat> vertex;
        std::vector<SUint> indices;
    
        Shader* shader;
    
        Mesh* mesh;
    
        Quad2D();
        virtual ~Quad2D();

        void setColor(const Color& color);
        void setUVCoords(const Vec2& leftDown, const Vec2& leftUp, const Vec2& rightUp, const Vec2& rightDown);
        void setRect(float x, float y, float width, float height);


    };
    
}

#endif
