

#include "PlayerMovementComponent.h"

using namespace sge;

PlayerMovementComponent::PlayerMovementComponent(){
        
        setTypeName();

        _forward=false;
        _backward=false;
        _left=false;
        _right=false;
        _velocity=0.1;
        _run=false;
        _up=false;
        _space=false;
        _down=false;
        _mode=PERSON_FIRST;
    _moveCamera=NULL;
    
        _updateReceiver= new UpdateReceiver(CALLBACK_SELECTOR(PlayerMovementComponent::update, this), 1/60. , 0);
        _keyBoardReceiver= new KeyboardReceiver(0);
        _keyBoardReceiver->releaseCallback=CALLBACK_SELECTOR(PlayerMovementComponent::didReleaseKey, this);
        _keyBoardReceiver->pressCallback=CALLBACK_SELECTOR(PlayerMovementComponent::didPressKey, this);
        _touchReceiver= new TouchReceiver(0);
        _touchReceiver->touchBeganCallback=CALLBACK_SELECTOR(PlayerMovementComponent::touchBegan, this);
        _touchReceiver->touchEndedCallback=CALLBACK_SELECTOR(PlayerMovementComponent::touchEnded, this);
        _touchReceiver->touchMovedCallback=CALLBACK_SELECTOR(PlayerMovementComponent::touchMoved, this);
        
        Director::getInstance()->getKeyboardDispenser()->addReceiver(_keyBoardReceiver);
        Director::getInstance()->getUpdateDispenser()->addReceiver(_updateReceiver);
        Director::getInstance()->getTouchDispenser()->addReceiver(_touchReceiver);
    
        _physicsComponent=NULL;
    
        setEnabled(false);
        
    }

    void PlayerMovementComponent::setMoveCamera(sge::Camera* camera){

        _moveCamera=camera;

    }

    void PlayerMovementComponent::setMoveDir(const sge::Vec3& moveDir){

        _moveDirForward=moveDir;
        _moveDirForward.normalize();
        
        _moveDirRight=_moveDirForward;
        
        sge::Mat4 rotMatrix;
        sge::Mat4::createRotation(Vec3(0, 1, 0), -M_PI_2, &rotMatrix);
        rotMatrix.transformVector( &_moveDirRight);
    
    }

    void PlayerMovementComponent::addedToEntity(Entity* entity){

        _physicsComponent=(sge::PhysicsComponent* ) entity->getComponentByName("PhysicsComponent");
   
    }


    void PlayerMovementComponent::setTypeName(){
        
        _componentKey="PlayerMovementComponent";
        
    }
    
    void PlayerMovementComponent::setEnabled(bool enabled){
        
        Component::setEnabled(enabled);
        // ToDo deactivate all key state
        if(!enabled){
            
            _updateReceiver->setEnabled(false);
            _keyBoardReceiver->setEnabled(false);
            _touchReceiver->setEnabled(false);
            
        }else{
            
            _updateReceiver->setEnabled(true);
            _keyBoardReceiver->setEnabled(true);
            _touchReceiver->setEnabled(true);
            
        }
        
    }
    
    void PlayerMovementComponent::setVelocity(float velocity){
        
        _velocity=velocity;
        
    }
    
    void PlayerMovementComponent::update(float delta){
        
        _moveVec=_moveVec-_moveVec*delta*0.9;

        if(_forward){
            
            _moveVec+=_moveDirForward*delta;
            
        }
        
        if(_backward){
            
            _moveVec-=_moveDirForward*delta;
            
        }
        if(_left){
            
            _moveVec-=_moveDirRight*delta;
        }
        
        if(_right){
            
            _moveVec+=_moveDirRight*delta;
            
        }
        
        float velo=_velocity;
        if(_run) velo=_velocity*5;
        
        if(_moveCamera){
        
            setMoveDir(Vec3(_moveCamera->getDirection().x, 0, _moveCamera->getDirection().z));
            float angle= -Vec2(_moveDirForward.x, _moveDirForward.z).angleDegree()+90;

            _entity->transform().setRotation(Vec3(0, 1, 0),angle);
            
        }
        
        if(_physicsComponent){
            
            _physicsComponent->_velocity=_physicsComponent->_velocity*Vec3(0.8, 1, 0.8);
            _physicsComponent->_velocity+=_moveVec*delta*velo;
    
        }else{
        
            _entity->transform().setTranslation(_entity->transform().getTranslation()+_moveVec*delta*velo);
        
        }
        
        
    }

    
    void PlayerMovementComponent::didReleaseKey(KeyEvent* event){
        
        if(event->KeyCode==KeyEvent::W) _forward=false;
        if(event->KeyCode==KeyEvent::S) _backward=false;
        if(event->KeyCode==KeyEvent::A) _left=false;
        if(event->KeyCode==KeyEvent::D) _right=false;
        if(event->KeyCode==KeyEvent::SPACE) _space=false;
        if(event->KeyCode==KeyEvent::Q) _run=false;
        if(event->KeyCode==KeyEvent::ENTER) _down=false;
        
    }
    
    void PlayerMovementComponent::didPressKey(KeyEvent* event){
        
        
        if(event->KeyCode==KeyEvent::W) _forward=true;
        if(event->KeyCode==KeyEvent::S) _backward=true;
        if(event->KeyCode==KeyEvent::A) _left=true;
        if(event->KeyCode==KeyEvent::D) _right=true;
        
        if(event->KeyCode==KeyEvent::SPACE && _physicsComponent){
            
            _physicsComponent->_velocity+=Vec3(0,1,0);
            _space=true;
            
        }
        
        if(event->KeyCode==KeyEvent::Q) _run=true;
        if(event->KeyCode==KeyEvent::ENTER) _down=true;
        
    }
    
    void PlayerMovementComponent::touchBegan(TouchEvent* event){
        
        
        
    }
    
    void PlayerMovementComponent::touchMoved(TouchEvent* event){
        
       
        
    }
    
    void PlayerMovementComponent::touchEnded(TouchEvent* event){
        
        
    }
    
    
    
    void PlayerMovementComponent::setMode(int mode){
        
        _mode=mode;
        
    }
    
    bool PlayerMovementComponent::isRunning(){
        
        return _run;
        
    }
    
    PlayerMovementComponent::~PlayerMovementComponent(){
        
        
    }
    

