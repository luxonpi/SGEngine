

#ifndef SGENGINE_SCENE_H
#define SGENGINE_SCENE_H

#include <iostream>
#include "Node.h"

namespace sge {

    class Scene: public Node{

    private:
    
    public:
        
        Node* _worldNode;
        Node* _screenNode;
    
        Scene();
        virtual ~Scene();
    
        virtual void draw();
        virtual void postDraw();
        virtual void enter();
        virtual void exit();
    
    };
    
}

#endif
