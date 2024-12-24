

#include "ArmatureAnimation.h"
#include "Model.h"
#include "ModelLoader.h"


namespace sge{
    
    ArmatureAnimation* ArmatureAnimation::create(const std::string& file){
    
        ArmatureAnimation* arm= new ArmatureAnimation();
        ModelLoader::getInstance()->loadIntoAnimation(arm, file, 0);
        return arm;
        
    }
    
    std::string ArmatureAnimation::getName(){
    
        return _name;
    
    }
    
    ArmatureAnimation::ArmatureAnimation(){}

    BoneAnimationNode::BoneAnimationNode(){
    
        hasAnimation=false;

    }
    
    void ArmatureAnimation::setName(const std::string& name){
    
        _name=name;
    
    }
    
    void BoneAnimationNode::loadIntoTransform(Transform* transform, float time){
    
        int indexTranslation= findIndex(&translationKeys, time);
        int indexRotation= findIndex(&rotationKeys, time);
        int indexScale= findIndex(&scalingKeys, time);

        if(indexTranslation>-1){
        
            float interpolationValue=(time-translationKeys[indexTranslation].time)/translationKeys[indexTranslation].duration;
            int nextIndex=(indexTranslation+1)%translationKeys.size();
            
            if(translationKeys.size()==0 || translationKeys.size()-1==indexTranslation){
            
                transform->setTranslation(translationKeys[indexTranslation].valueVector);
            
            }else{
            
                Vec3 finalPos= lerp(translationKeys[indexTranslation].valueVector, translationKeys[nextIndex].valueVector, interpolationValue);
                transform->setTranslation(finalPos);
            
            }

    
        
        }
        
        if(indexRotation>-1){
         
            float interpolationValue=(time-rotationKeys[indexRotation].time)/rotationKeys[indexRotation].duration;
            int nextIndex=(indexRotation+1)%rotationKeys.size();
            
            if(rotationKeys.size()==0 || rotationKeys.size()-1==indexRotation){
                
                transform->setRotation(rotationKeys[indexRotation].valueQuaternion);
                
            }else{
                
                Quaternion quad;
                Quaternion::slerp(rotationKeys[indexRotation].valueQuaternion, rotationKeys[nextIndex].valueQuaternion, interpolationValue, &quad);
                
                transform->setRotation(quad);
                
            }
            
            
            
        }
        
        if(indexScale>-1){
        
            float interpolationValue=(time-scalingKeys[indexScale].time)/scalingKeys[indexScale].duration;
            int nextIndex=(indexTranslation+1)%scalingKeys.size();
            
            if(scalingKeys.size()==0 || scalingKeys.size()-1==indexScale){
                
                transform->setScale(scalingKeys[indexScale].valueVector.x,scalingKeys[indexScale].valueVector.y,scalingKeys[indexScale].valueVector.z);
                
            }else{
                
                Vec3 finalPos= lerp(scalingKeys[indexScale].valueVector, scalingKeys[nextIndex].valueVector, interpolationValue);
                transform->setScale(finalPos.x,finalPos.y,finalPos.z);
                
            }

            
            
        }
        
    }

    int BoneAnimationNode::findIndex(std::vector<BoneAnimationNode::KeyFrame>* array, float time){
    
        if(array->size()==1) return 0;
        if(array->size()==0) return -1;

        for (uint i = 0; i <array->size() - 1 ; i++) {
            
            if (time < (float) array->at(i + 1).time) {
            
                return i;
                
            }
            
        }

        return -1;
    }
    
    
//    void ArmatureAnimation::setAnimationToSkeleton(ModelArmature* skeleton, float time){
//    
//        aiMatrix4x4 Identity;
//    
//        float TicksPerSecond = (float)(_animation->mTicksPerSecond != 0 ?_animation->mTicksPerSecond : 25.0f);
//        float TimeInTicks = time * TicksPerSecond;
//        float AnimationTime = fmod(TimeInTicks, (float)_animation->mDuration);
//    
//        if(_cache){
//    
//            AnimationTime= int (AnimationTime*_cacheResolution)/_cacheResolution;
//
//        }
//    
//        ReadNodeHeirarchy(AnimationTime, _scene->mRootNode, Identity, skeleton);
//    
//    }
//    

//    void ArmatureAnimation::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim){
//        
//        if (pNodeAnim->mNumPositionKeys == 1) {
//            Out = pNodeAnim->mPositionKeys[0].mValue;
//            return;
//        }
//        
//        uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
//        uint NextPositionIndex = (PositionIndex + 1);
//        assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
//        float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
//        float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
//       // assert(Factor >= 0.0f && Factor <= 1.0f);
//        const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
//        const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
//        aiVector3D Delta = End - Start;
//        Out = Start + Factor * Delta;
//    }
//    


}
