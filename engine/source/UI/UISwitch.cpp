

#include "UISwitch.h"
#include "Director.h"

namespace sge {

    UISwitch::UISwitch(){
    
        getRenderObject()->setDrawAble(false);
        _isOn=false;
        _changeCallback=0;
        
        Texture* ui= Texture::get("assets/sprites/baseUI.png");
        
        _bg= View::create(53, 27, "assets/sprites/baseUI.png");
        _bg->setTextureRect(Rectangle(0,1,1,27./ui->getSize().y));
        this->addSubview(_bg);
        
        _bg2= View::create(43, 17, "assets/sprites/baseUI.png");
        _bg2->setTextureRect(Rectangle(0,28/ui->getSize().y,43./ui->getSize().x,17./ui->getSize().y));
        _bg2->setPosition(53/2.0, 27/2.0);
        _bg2->transform().setScale(0.99);
        _bg2->getRenderObject()->setVisible(false);
        _bg2->setTintColor(Color(26, 85, 36, 1));
        this->addSubview(_bg2);

        
        _button= View::create(17, 17, "assets/sprites/baseUI.png");
        _button->setTextureRect(Rectangle(0,46/ui->getSize().y,17./ui->getSize().x,17./ui->getSize().y));
        _button->setPosition(13.5, 27/2.0);
        this->addSubview(_button);
        
        _button->setTintColor(Color(26, 85, 36, 1));
        _bg->setTintColor(Color(26, 85, 36, 1));

        
        setContentSize(Vec2(53, 27));
        
        TouchReceiver* newTouch= new TouchReceiver(0);
        newTouch->touchBeganCallback=CALLBACK_SELECTOR(UISwitch::touchBegan, this);
        newTouch->touchEndedCallback=CALLBACK_SELECTOR(UISwitch::touchEnded, this);
        newTouch->touchMovedCallback=CALLBACK_SELECTOR(UISwitch::touchMoved, this);
       
        Director::getInstance()->getTouchDispenser()->addReceiver(newTouch);
    
    }
    
    UISwitch::~UISwitch(){
    
    
    }
    
    void UISwitch::touchBegan(sge::TouchEvent* event){
        
        Vec2 winS= Director::getInstance()->getWindowSize();
  
        
    }
    
    void UISwitch::touchMoved(sge::TouchEvent* event){
        
        
    }
    
    void UISwitch::touchEnded(sge::TouchEvent* event){
        
        if(Director::getInstance()->isMouseTrapped()) return;
        
        Vec2 p=event->getCurrentLocation();
        BoundingBox b= getBoundingBox();
        
        if(b.contains2DPoint(p)){
            
            setOn(!_isOn);
        
            if(_changeCallback) _changeCallback(this);
            
        }
       
        
    }

    void UISwitch::setCallback(std::function<void(UISwitch*)> callback){
    
        _changeCallback=callback;
    
    }

    bool UISwitch::isOn(){
    
        return _isOn;
    
    }
    
    void UISwitch::setOn(bool on){
    
        _isOn=on;
        _button->setPosition(14+ (53-28)*_isOn, 27/2.0);
        _bg2->getRenderObject()->setVisible(_isOn);

        if(_isOn){
        
            _button->setTintColor(Color(122, 255, 63, 1));
            _bg->setTintColor(Color(122, 255, 63, 1));
        
        }else{
        
            _button->setTintColor(Color(26, 85, 36, 1));
            _bg->setTintColor(Color(26, 85, 36, 1));
        
        }

    
    }
    
    UISwitch* UISwitch::create(){
    
        UISwitch* newswitch= new UISwitch();
        return newswitch;
        
    }

}