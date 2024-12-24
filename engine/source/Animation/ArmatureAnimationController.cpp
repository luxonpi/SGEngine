

#include "ArmatureAnimationController.h"
#include "Director.h"

namespace sge {

ArmatureAnimationController::ArmatureAnimationController(){
    
    runningAnimation=NULL;
    _lastFrame=Director::getInstance()->getPassedTime();


}
    
void ArmatureAnimationController::update(){
    

    float deltaTime=Director::getInstance()->getPassedTime()-_lastFrame;
    _lastFrame= Director::getInstance()->getPassedTime();
    
    typedef std::map<unsigned int, ControlledAnimation*>::iterator it_type;
    
      for(it_type iterator = _channels.begin(); iterator != _channels.end(); iterator++) {
     
        ControlledAnimation* channelAnimation= iterator->second;
        channelAnimation->time+=channelAnimation->speed*(deltaTime*0.1);
    
    }

}
    
bool ArmatureAnimationController::isRunningAnimation(){
 
    return runningAnimation;
    
}
    
void ArmatureAnimationController::setToArmature(ModelArmature* armature){
    
    typedef std::map<unsigned int, ControlledAnimation*>::iterator it_type;
    
    for(it_type iterator = _channels.begin(); iterator != _channels.end(); iterator++) {
        
        ControlledAnimation* channelAnimation= iterator->second;
        

        float AnimationTime = fmod(channelAnimation->time, (float)channelAnimation->animation->_duration);
        armature->setPose(channelAnimation->animation,  AnimationTime);
        
        //channelAnimation->animation->setAnimationToSkeleton(armature, channelAnimation->time);
        
    }
    
}
    
void ArmatureAnimationController::stopAnimationOnChannel(unsigned int channel){
    
    if(_channels.find(channel)!=_channels.end()){
    
        _channels.erase(channel);
    
    }

}
    
void ArmatureAnimationController::setSpeed(float speed){
    

}
    
void ArmatureAnimationController::playAnimation(ArmatureAnimation* animation,unsigned int channel, float speed, bool loop){
    
    _lastFrame=Director::getInstance()->getPassedTime();
    
    if(_channels.find(channel)==_channels.end()){
    
        _channels.insert(std::make_pair(channel, new ControlledAnimation()));
        
    }
    
    ControlledAnimation* channelanimation= _channels[channel];
    
    channelanimation->animation=animation;
    channelanimation->speed=speed;
    channelanimation->loop= loop;
    channelanimation->time=0;

}
    
}