

#ifndef SGENGINE_MODELARMATURE_H
#define SGENGINE_MODELARMATURE_H

#include "SBase.h"
#include "Transform.h"
#include "MeshData.h"
#include "ArmatureAnimation.h"

namespace sge {
   
    class ModelRigged;
    class ModelLoader;
    class ArmatureAnimation;
    class ModelArmature;
    class Transform;
    class Bone;
    
    class BoneNode{
    
    public:
        
        Mat4 transform;
        BoneNode* parent;
        std::vector<BoneNode> childs;
        std::string name;
        Bone* bone;
        bool animated;
        Transform aTransform;

        BoneNode();
    
    };
    
    // Boneclass
    class Bone{
    
        friend ModelArmature;
        friend ModelLoader;
        friend ModelRigged;
        friend ArmatureAnimation;
    
    private:
    
        bool _isDirty;
        std::string _name;
    
        std::vector<Bone*> _childs;
        Bone* _parent;
        
        Bone* getCopy();
    
        int _flatArrayIndex;
        
    public:

        Bone();
    
        void addChild(Bone* bone);
        bool isDirty();
        void setDirty(bool dirty);
    
        std::string getName();
        
        Mat4 offset;
        Mat4 localTransform;

        Mat4 globalTransform;
        
        Transform transform;
        Transform customTransform;

    };
    
    struct ArmatureAnimationBridge{
    
        int boneIndex;
        BoneAnimationNode* node;
        BoneNode* bone;
    
    };
    
    struct ArmatureAnimationBridgeContainer{
    
        std::vector<ArmatureAnimationBridge> array;
        std::string name;
    
    };
    
    class ModelArmature{
    
        friend ModelLoader;
        friend ModelRigged;
        friend ArmatureAnimation;

    protected:
    
        unsigned long _lastFrame;
        
        ModelArmature();
        
        std::unordered_map<ArmatureAnimation*, ArmatureAnimationBridgeContainer> _animationMap;

        std::vector<ArmatureAnimation*> _animations;
    
        std::vector<Bone*> _rootBones;
        std::vector<Bone*> _flatBoneArray;
    
        // Maps name of bone to its index of _flatBoneArray
        std::map<std::string, uint> _boneMapping;

        uint _numBones;
    
        Bone* getBoneCopyOfBone(Bone* bone);
        
        std::vector<Mat4> _flatMatriciesArray;
        
    public:

        BoneNode bone;
        
        Mat4 inverseWorld;

        bool _dirty;
        
        void updateMatrixArray();
        void updateMatrixRecursive(Bone* bone, Mat4 ptransform);
        
        void updateMatrixRecursive(BoneNode* bone, Mat4 ptransform);

        
        
        const std::vector<Mat4>& getMatrixArray();
        
        void setPose(ArmatureAnimation* animation, float time);
    
        void printBoneNames();
        
        void updateBoneMapping();
    
        unsigned int numberOfBones();
        unsigned int getIndexOfBone(std::string name);
    
        BoneNode* getBoneNodeNamed(std::string name, BoneNode* nodeToSearch);

        Bone* getBoneNamed(std::string name);
        Bone* getBoneAtIndex(unsigned int index);
    
        ModelArmature* getCopy();
        void addAnimation(ArmatureAnimation* animation, const std::string& name);
        ArmatureAnimation* getAnimationWithName(std::string name);
    
    };
    
    
}

#endif
