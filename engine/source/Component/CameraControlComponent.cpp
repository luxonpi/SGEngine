

#include "CameraControlComponent.h"
#include "Director.h"
#include "Entity.h"
#include "PhysicComponent.h"

namespace sge {
    
    CameraControlComponent::CameraControlComponent(){
        
        _forward=false;
        _backward=false;
        _left=false;
        _right=false;
        _velocity=0.1;
        _run=false;
        _up=false;
        _space=false;
        _angleHorizontal=0;
        _angleVertikal=0;
        _down=false;
        _mode=PERSON_FIRST;
        _anglesLocked=false;
        _cameraDistance=3;
        _cameraOffset.set(0, 0);
        setTypeName();
        
        _followEntity=NULL;

        _moveVec=Vec2(0,0);
        _mouseMomentum.set(0,0);
   
        
        _updateReceiver= new UpdateReceiver(CALLBACK_SELECTOR(CameraControlComponent::update, this), 1/60. , 0);
        
        _keyBoardReceiver= new KeyboardReceiver(0);
        _keyBoardReceiver->releaseCallback=CALLBACK_SELECTOR(CameraControlComponent::didReleaseKey, this);
        _keyBoardReceiver->pressCallback=CALLBACK_SELECTOR(CameraControlComponent::didPressKey, this);
        
        _touchReceiver= new TouchReceiver(0);
        _touchReceiver->touchBeganCallback=CALLBACK_SELECTOR(CameraControlComponent::touchBegan, this);
        _touchReceiver->touchEndedCallback=CALLBACK_SELECTOR(CameraControlComponent::touchEnded, this);
        _touchReceiver->touchMovedCallback=CALLBACK_SELECTOR(CameraControlComponent::touchMoved, this);
        
        Director::getInstance()->getKeyboardDispenser()->addReceiver(_keyBoardReceiver);
        Director::getInstance()->getUpdateDispenser()->addReceiver(_updateReceiver);
        Director::getInstance()->getTouchDispenser()->addReceiver(_touchReceiver);
        
        setEnabled(false);
        
    }
    
    void CameraControlComponent::setCameraDistance(float distance){
    
        _cameraDistance=distance;
    
    }
    
    void CameraControlComponent::setFollowEntity(Entity* followEntity){
    
        _followEntity=followEntity;
    
    }
  
    void CameraControlComponent::setTypeName(){
        
        _componentKey="FlyoverCameraComponent";
        
    }
    
    void CameraControlComponent::setEnabled(bool enabled){
        
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
    
    void CameraControlComponent::setVelocity(float velocity){
        
        _velocity=velocity;
        
    }
    
    void CameraControlComponent::update(float delta){
        
        Vec2 moveDir= Vec2::fromAngle(_angleHorizontal);
        Vec2 moveDirSide= Vec2::fromAngle(_angleHorizontal-90);
        
        Vec2 lookDir= Vec2(_angleVertikal/360.+1.5,0);
        
        Vec2 move= moveDir*_moveVec.y;
         move+= moveDirSide*_moveVec.x;
        
        _moveVec=_moveVec*0.9;
        
        float b=-1;
        if(_mouseMomentum.x>0) b=1;
        _angleHorizontal-= powf(fabs(_mouseMomentum.x)*50,1.3)*b;
        _mouseMomentum.x*=0.9;
        
        float by=-1;
        if(_mouseMomentum.y>0) by=1;
        _angleVertikal-= powf(fabs(_mouseMomentum.y)*50,1.3)*by;
        _mouseMomentum.y*=0.9;
        
        
        if(_forward){
            
            //move=Vec2(move.x+moveDir.x, move.y+moveDir.y);
            _moveVec+=Vec2(0, 3)*delta;
            
        }
        
        if(_backward){
            
           //move=Vec2(move.x-moveDir.x, move.y-moveDir.y);
            _moveVec-=Vec2(0, 3)*delta;
            
        }
        if(_left){
            
            _moveVec-=Vec2(moveDirSide.x, moveDirSide.y)*delta;
        }
        
        if(_right){
            
            //move=Vec2(move.x+moveDirSide.x, move.y+moveDirSide.y);
            _moveVec+=Vec2(moveDirSide.x, moveDirSide.y)*delta;

        }
        
        float velo=_velocity;
        if(_run) velo*=13;
        
//        if(_space) _entity->setPositionY(_entity->getPosition().y+1*delta*velo);
//        if(_down) _entity->setPositionY(_entity->getPosition().y-1*delta*velo);
//        
//        
//        float y=_entity->getPosition().y;
//        
   
        Camera* cam= dynamic_cast<Camera*>(_entity);
        
        if(cam){
        
            cam->setDirection(Vec3(moveDir.x, -lookDir.x, moveDir.y).normalized());

        }
        
        if(_followEntity){
        
            cam->setPosition(_followEntity->transform().getTranslation()-
                             cam->getDirection()*_cameraDistance+
                             Vec3(0,_cameraOffset.y,0)+Vec3(moveDirSide.x, 0, moveDirSide.y)*_cameraOffset.x);
        
        
        }else{
        
            _entity->transform().setTranslation(_entity->transform().getTranslation().x+move.x*delta*velo,
                                2,
                                _entity->transform().getTranslation().z+move.y*delta*velo);
            
            
        }

    
        
    }
    
    void CameraControlComponent::setCameraOffset(sge::Vec2 offset){
    
        _cameraOffset=offset;
    
    }
    
    void CameraControlComponent::setLockAngles(bool lock){
    
        _anglesLocked=lock;
        _mouseMomentum.set(0, 0);
    
    }

    
    void CameraControlComponent::didReleaseKey(KeyEvent* event){
        
        if(event->KeyCode==KeyEvent::W) _forward=false;
        if(event->KeyCode==KeyEvent::S) _backward=false;
        if(event->KeyCode==KeyEvent::A) _left=false;
        if(event->KeyCode==KeyEvent::D) _right=false;
        if(event->KeyCode==KeyEvent::SPACE) _space=false;
        if(event->KeyCode==KeyEvent::Q) _run=false;
        if(event->KeyCode==KeyEvent::ENTER) _down=false;
        
    }
    
    void CameraControlComponent::didPressKey(KeyEvent* event){
        
        
        if(event->KeyCode==KeyEvent::W) _forward=true;
        if(event->KeyCode==KeyEvent::S) _backward=true;
        if(event->KeyCode==KeyEvent::A) _left=true;
        if(event->KeyCode==KeyEvent::D) _right=true;
        
        if(event->KeyCode==KeyEvent::SPACE){
            
            _space=true;
            
        }
        
        if(event->KeyCode==KeyEvent::Q) _run=true;
        if(event->KeyCode==KeyEvent::ENTER) _down=true;
        
    }
    
    void CameraControlComponent::touchBegan(TouchEvent* event){
        
        
        
    }
    
    void CameraControlComponent::touchMoved(TouchEvent* event){
        
        Vec2 winS= Director::getInstance()->getWindowSize();
        
        if(_anglesLocked) return;
        
#ifdef MOBILE_TARGET
        float dif_x=event->getCurrentLocation().x-event->getPreviousLocation().x;
        float dif_y=event->getCurrentLocation().y-event->getPreviousLocation().y;
        
        if(event->getStartLocation().x<winS.y/2.0){
        
            _moveVec+=Vec2(dif_x, dif_y)*0.1;
            
            return;
        
        }
#else
        float dif_x,dif_y;
        
        if(Director::getInstance()->isMouseTrapped()){
            
            dif_x= event->getRelativeMovement().x;
            dif_y= event->getRelativeMovement().y;
        
        }else{
        
            dif_x= event->getCurrentLocation().x-event->getPreviousLocation().x;
            dif_y= event->getCurrentLocation().y-event->getPreviousLocation().y;

        }
     
      
#endif
        
        _mouseMomentum.x+=dif_x/winS.x;
        if(_mouseMomentum.x>1) _mouseMomentum.x=1;
        if(_mouseMomentum.x<-1) _mouseMomentum.x=-1;

        _mouseMomentum.y+=dif_y/winS.y;
        if(_mouseMomentum.y>1) _mouseMomentum.y=1;
        if(_mouseMomentum.y<-1) _mouseMomentum.y=-1;
        
    }
    
    void CameraControlComponent::touchEnded(TouchEvent* event){
        
        
    }
    

    
    void CameraControlComponent::setMode(int mode){
        
        _mode=mode;
        
    }
    
    bool CameraControlComponent::isRunning(){
        
        return _run;
        
    }
    
    CameraControlComponent::~CameraControlComponent(){
        
        
    }
    
}

