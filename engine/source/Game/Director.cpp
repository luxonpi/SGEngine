

#include "Director.h"
#include "GraphicDeviceOpenGL.h"
#include "Benchmark.h"
#include <chrono>

namespace sge {

Camera* Director::Camera2d= Camera::create2D(100, 100);
    
Director*  Director::_instance=NULL;
Director* Director::getInstance(){
    
    if(!_instance) _instance= new Director();
    return _instance;
}


Director::Director(){

    _renderer= new Renderer();

    _fpsLimit=60.;
    _pause=false;
    _currentScene=NULL;
    _lastReorder=60;
    
    _fpsTimer=0;
    _frames=0;
    _currentFps=0;
    _time=0;
    _frameCount=0;
    _didInit=false;
    _isMouseTrapped=false;
    _loopedTime=0;
    _graphicDevice= new GraphicDeviceOpenGL();
    
}
    
void Director::init(){
    
    if(_didInit) return;

    _didInit=true;
    
    _graphicDevice->startUp();
    
    modelDefaultMaterial= new Material();
    modelDefaultMaterial->setShaderModule(ShaderModule::get("sge/shader/Standard.glsl"));
    modelDefaultMaterial->setAlpha(false);
    modelDefaultMaterial->getShaderState()->setUniform3f("u_sge_material.color", Vec3(1, 1, 1));
    modelDefaultMaterial->getShaderState()->setUniform1f("u_sge_material.roughness", 0.5);
    modelDefaultMaterial->getShaderState()->setUniform1f("u_sge_material.metalness", 0);
    modelDefaultMaterial->getShaderState()->setUniform1f("u_sge_material.fresnelFactor", 1);
    modelDefaultMaterial->addDefine("FORWARD_RENDERING");
    modelDefaultMaterial->addDefine("SGE_RECEIVE_SHADOW");
    modelDefaultMaterial->addDefine("SGE_LIGTHING_ENVIRONMENT");
    
    viewDefaultMaterial= new Material();
    viewDefaultMaterial->setShaderModule(ShaderModule::get("sge/shader/View.glsl"));
    viewDefaultMaterial->setAlpha(true);
    viewDefaultMaterial->setDepthFunction(DepthFunc::ALWAYS);
    
    fontDefaultMaterial= new Material();
    fontDefaultMaterial->setShaderModule(ShaderModule::get("sge/shader/Font.glsl"));
    fontDefaultMaterial->setAlpha(true);

    Texture::init();
    
    _screenBuffer= FrameBuffer::getDefaultBuffer();
    _screenBuffer->setClearColor(Color(255,195,0,1));
    _screenBuffer->setSize(_realWindowsSize.x, _realWindowsSize.y);
    _screenBuffer->clear(1, 1, 1);
    
    _compositor= new Compositor();
    _fileUtils= new FileUtils();

    checkRenderError();

}
    
    
FileUtils* Director::getFileUtils(){
    
    return _fileUtils;
    
}

    
Compositor* Director::getCompositor(){
    
    return _compositor;

}
    
GraphicDevice* Director::getGraphicDevice(){
    
    return _graphicDevice;

}

Director::~Director(){}
    
FrameBuffer* Director::getScreenBuffer(){
    
    return _screenBuffer;
}
    
void Director::setFpsLimit(float fps){
    
    _fpsLimit=fps;
    
}
    
float Director::getFpsLimit(){
    
    return _fpsLimit;
    
}
    
bool Director::isMouseTrapped(){
    
    return _isMouseTrapped;
    
}
    
Vec2 Director::getWindowSize(){
    
    return _realWindowsSize;
}
    
void Director::setWindowSize(Vec2 size){

    Camera2d->setWindowsSize(size.x, size.y);
    _realWindowsSize=size;
    
    if(_didInit) _screenBuffer->setSize(size.x, size.y);

}
    
    
Camera* Director::getCamera(){
    
    return _currentCamera;
}
    
void Director::setCamera(Camera* camera){
    
    _currentCamera=camera;
    
}
    
UpdateDispenser* Director::getUpdateDispenser(){
    
    return &_updateDispenser;
    
}
    
KeyboardDispenser* Director::getKeyboardDispenser(){
    
    return &_keyboardDispenser;
    
}
    
TouchDispenser* Director::getTouchDispenser(){

    return &_touchDispenser;
    
}
   
void Director::replaceScene(Scene* Scene){
    
    if(_currentScene){
    
        _currentScene->exit();
        delete _currentScene;
    }
    
    _currentScene=Scene;
    _currentScene->enter();
    
}
    
void Director::draw(){
    
    Benchmark::getInstance()->resetCounter();
    
    if(_currentScene) _currentScene->draw();
    if(_currentScene) _currentScene->postDraw();
        
    _frames++;
    _frameCount++;

    if(_fpsTimer>10){
        
        float factor= 10./_fpsTimer;
        _currentFps=_frames*factor;
        _fpsTimer=0;
        _frames=0;
        
    }
    
    
}
    
Renderer* Director::getRenderer(){
    
    return _renderer;
    
}
    
float Director::getTime(){
    
    return _loopedTime;

}

void Director::update(float delta){

    _loopedTime+=delta;
    _time+=delta;
    _fpsTimer+=delta;
   
    _updateDispenser.update(delta);

}
    
unsigned int Director::getCurrentFps(){

    return _currentFps;

}
    
double Director::getPassedTime(){
    
    return _time;
}
    
unsigned int Director::getFrameCount(){
    
    return _frameCount;
}

void Director::mouseUp(Vec2 location, bool isMouse){

    _touchDispenser.touchEnded(location,isMouse);
}
    
void Director::mouseScrolled(Vec2 offset){
    
    _touchDispenser.mouseWheel(offset,true);

}

void Director::mouseDown(Vec2 location, bool isMouse){

    _touchDispenser.touchBegan(location,isMouse);
 
}

void Director::mouseMoved(Vec2 location, bool isMouse){
    
    _touchDispenser.touchMoved(location,isMouse);
    
}
    
void Director::mouseMovedRelative(Vec2 offset, bool isMouse){
    
    _touchDispenser.mouseMovedRelative(offset, true);
    
}
    

void Director::keyUp(const KeyEvent& key){

    KeyEvent keyEvent= KeyEvent(key);
    _keyboardDispenser.keyReleased(&keyEvent);

}


void Director::keyDown(const KeyEvent& key){

    KeyEvent keyEvent= KeyEvent(key);
    _keyboardDispenser.keyPressed(&keyEvent);

}



} // Namespace en
