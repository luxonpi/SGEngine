

#include "UISlider.h"
#include "Director.h"

namespace sge {
    
    UISlider::UISlider(){
        
        getRenderObject()->setDrawAble(false);
        _changeCallback=0;
        
        Texture* ui= Texture::get("assets/sprites/baseUI.png");
        
        _bg= View::create(200, 3, Color::grey);
        _bg->setPosition(0, 20/2.0);
        this->addSubview(_bg);
        
        _bg2= View::create(100, 3, Color::green);
        _bg2->setPosition(0, 20/2.0);
        this->addSubview(_bg2);
        
        
        _button= View::create(42, 12, "assets/sprites/baseUI.png");
        _button->setTextureRect(Rectangle(0,64/ui->getSize().y,42./ui->getSize().x,12./ui->getSize().y));
        _button->setPosition(200/2.0, 20/2.0);
        this->addSubview(_button);
        
        _button->setTintColor(Color(122, 255, 63, 1));
        _bg2->setTintColor(Color(26, 85, 36, 1));
        _bg->setTintColor(Color(80, 80, 80, 1));

        
        _minX=21;
        _maxX=200-21;

        setContentSize(Vec2(200, 20));
        
        TouchReceiver* newTouch= new TouchReceiver(0);
        newTouch->touchBeganCallback=CALLBACK_SELECTOR(UISlider::touchBegan, this);
        newTouch->touchEndedCallback=CALLBACK_SELECTOR(UISlider::touchEnded, this);
        newTouch->touchMovedCallback=CALLBACK_SELECTOR(UISlider::touchMoved, this);
        
        Director::getInstance()->getTouchDispenser()->addReceiver(newTouch);
        
        _isDragging=false;
        
    }
    
    float UISlider::getValue(){
    
        return (_button->transform().getTranslation().x-_minX)/(200-_minX*2);
    
    
    }
    
    
    UISlider::~UISlider(){
        
        
    }
    
    void UISlider::touchBegan(sge::TouchEvent* event){
        
        Vec2 winS= Director::getInstance()->getWindowSize();
        
        if(Director::getInstance()->isMouseTrapped()) return;
        
        Vec2 p=event->getCurrentLocation();
        BoundingBox b= _button->getBoundingBox();
        
        if(b.contains2DPoint(p)){
            
            _isDragging=true;
            _button->transform().setScale(0.95);
            
        }
        
        
    }
    
    void UISlider::touchMoved(sge::TouchEvent* event){
        
        Vec2 p=event->getCurrentLocation();
        Vec2 dif=event->getPreviousLocation()-p;
        
        if(_isDragging){

            assert(0);
            //
//            _button->setPosition(_button->getPosition().x-dif.x, 20/2.0);
//            
//            if(_button->getPosition().x<_minX) _button->setPositionX(_minX);
//            if(_button->getPosition().x>_maxX) _button->setPositionX(_maxX);
//            
//            _bg2->setContentSize(Vec2(_button->getPosition().x, 3));
//            if(_changeCallback) _changeCallback(this);

        
        }
        
    }
    
    void UISlider::touchEnded(sge::TouchEvent* event){
        
        if(Director::getInstance()->isMouseTrapped()) return;
        
        Vec2 p=event->getCurrentLocation();
        BoundingBox b= getBoundingBox();
        
        assert(0);

       // _button->setScale(1);

        _isDragging=false;
        
        
    }
    
    void UISlider::setCallback(std::function<void(UISlider*)> callback){
        
        _changeCallback=callback;
        
    }
    
    
    
    UISlider* UISlider::create(){
        
        UISlider* newswitch= new UISlider();
        return newswitch;
        
    }
    
}