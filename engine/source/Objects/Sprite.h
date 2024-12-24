

#ifndef SGENGINE_SPRITE_H
#define SGENGINE_SPRITE_H

#include <iostream>
#include <string>

#include "Color.h"
#include "Node.h"
#include "Texture.h"
#include "Quad2D.h"

namespace sge {

    class Sprite: public Node{

    protected:

        Texture* _texture;
        Quad2D* _quad;
        Vec2 _contentSize;
    
        void init();

        Sprite(std::string file);
        Sprite(int width, int height);
        Sprite(Color color,int width, int height);
        Sprite(Texture* texture);
    
        Sprite();
        
    public:
        
        virtual ~Sprite();

        void setContentSize(const Vec2& size);
        Quad2D* getQuad();
    
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);
        void setTexture(Texture* Texture);
    
        static Sprite* create(std::string file);
        static Sprite* create(int width, int height);
        static Sprite* create(Texture* texture);
        static Sprite* create(Color color, int width, int height);
    
    };
    
}

#endif
