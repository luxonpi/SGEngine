

#ifndef SGENGINE_DIRECTOR_H
#define SGENGINE_DIRECTOR_H

#include "SBase.h"

#include "SScene.h"
#include "Vec2.h"
#include "KeyboardDispenser.h"
#include "TouchDispenser.h"
#include "Renderer.h"
#include "SCamera.h"
#include "UpdateDispenser.h"
#include "GraphicDevice.h"
#include "IniParser.h"
#include "FileUtils.h"


namespace sge {

class Director{
    
private:

    Director();
    ~Director();
    
    static Director* _instance;
    
    Vec2 _realWindowsSize;
    Vec2 _userSetWindowsSize;

    Renderer* _renderer;
    UpdateDispenser _updateDispenser;
    KeyboardDispenser _keyboardDispenser;
    TouchDispenser _touchDispenser;
    
    Scene* _currentScene;
    Camera* _currentCamera;
    
    FrameBuffer* _screenBuffer;
    
    bool _pause;
    float _fpsLimit;
    float _lastReorder;
    float _renderTime;
    float _loopedTime;
    
    float _fpsTimer;
    unsigned int _frames;
    float _currentFps;
    
    
    bool _didInit;
    
    bool _isMouseTrapped;
    IniReader* _iniParser;
    
    GraphicDevice* _graphicDevice;
    Compositor* _compositor;
    FileUtils* _fileUtils;
    
public:
    
    ShaderState globalShaderState;
    
    Compositor* getCompositor();
    FileUtils* getFileUtils();
    
    Material* modelDefaultMaterial;
    Material* viewDefaultMaterial;
    Material* fontDefaultMaterial;
    
    std::unordered_map<std::string, std::string> resourceLocations;

    Timer timer;

    GraphicDevice* getGraphicDevice();
    
    void init();
    
    float getTime();
    
    double _time;
    double  _timeCount;
    unsigned int _frameCount;

    FrameBuffer* getScreenBuffer();
    void setMouseTrapped(bool trapped);
        
    unsigned int getCurrentFps();
    unsigned int getFrameCount();
    double getPassedTime();
    
    static Director* getInstance();
    static Camera* Camera2d;

    Vec2 getWindowSize();
    void setWindowSize(Vec2 size);
    
    void setFpsLimit(float fps);
    float getFpsLimit();
    
    void draw();
    void update(float delta);
    
    void mouseUp(Vec2 location, bool isMouse);
    void mouseDown(Vec2 location, bool isMouse);
    void mouseMoved(Vec2 location, bool isMouse);
    void mouseScrolled(Vec2 offset);
    void mouseMovedRelative(Vec2 offset, bool isMouse);

    void keyUp(const KeyEvent& key);
    void keyDown(const KeyEvent& key);
    
    void replaceScene(Scene* Scene);
    bool isMouseTrapped();
    
    
    UpdateDispenser* getUpdateDispenser();
    KeyboardDispenser* getKeyboardDispenser();
    TouchDispenser* getTouchDispenser();

    Camera* getCamera();
    Renderer* getRenderer();
    void setCamera(Camera* camera);
   
};
    
} // Namespace end

#endif
