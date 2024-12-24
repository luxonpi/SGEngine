

#ifndef SGENGINE_ARMATUREANIMATION_H
#define SGENGINE_ARMATUREANIMATION_H

#include "SBase.h"
#include "Transform.h"

namespace sge {

    class BoneAnimationNode{
        
    public:
        
        struct KeyFrame{
            
            float time;
            float duration;
            Vec3 valueVector;
            Quaternion valueQuaternion;
            
        };
        
        BoneAnimationNode();
        std::string name;
        bool hasAnimation;
        
        std::vector<KeyFrame> scalingKeys;
        std::vector<KeyFrame> translationKeys;
        std::vector<KeyFrame> rotationKeys;
        int t;
        
        void loadIntoTransform(Transform* transform, float time);
        static int findIndex(std::vector<KeyFrame>* array, float time);
        
    };
    
    
class Model;
class ModelLoader;

    class ArmatureAnimation{

        friend class ModelLoader;

    private:
     
        std::string _name;
        
//        uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
//        uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
//        uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
//
//        void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//        void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//        void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//        void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform, ModelArmature* skeleton);
        
     //   void getMatrix(float AnimationTime, const aiNode* pNode, const aiMatrix4x4&ParentTransform);
        
public:
        
        static ArmatureAnimation* create(const std::string& file);

        float _duration;

        std::vector<BoneAnimationNode*> _animationNodes;

        ArmatureAnimation();

        void setName(const std::string& name);
        std::string getName();
        std::string file;
        
       // void setAnimationToSkeleton(ModelArmature* skeleton, float time);


};

}

#endif
