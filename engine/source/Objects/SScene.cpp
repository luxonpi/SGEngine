

#include "SScene.h"

namespace sge {

    Scene::Scene(){
    
        _worldNode= Node::create();
        _screenNode= Node::create();
    
    }
    Scene::~Scene(){}

    void Scene::enter(){}
    void Scene::exit(){}
    void Scene::draw(){}
    void Scene::postDraw(){}
    
}