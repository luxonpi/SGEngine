

#include "ModelArmature.h"
#include "ArmatureAnimation.h"

namespace sge {
    
// Armature /////////
BoneNode::BoneNode(){
    
    parent=NULL;
    bone=NULL;
    animated=false;

}

    
BoneNode* ModelArmature::getBoneNodeNamed(std::string name, BoneNode* nodeToSearch){

    if(nodeToSearch->childs.size()==0) return NULL;
    
    for (int i=0; i<nodeToSearch->childs.size(); i++) {
        
        if(nodeToSearch->childs[i].name==name) return &nodeToSearch->childs[i];
    
        BoneNode* snode= getBoneNodeNamed(name, &nodeToSearch->childs[i]);
        if(snode) return snode;
        
    }
    

    return NULL;
}
    
ModelArmature* ModelArmature::getCopy(){

    ModelArmature* copy= new ModelArmature();
    
    copy->_animations=_animations;
    copy->_numBones=_numBones;

    for (int i=0; i<_rootBones.size(); i++) {
        
        copy->_rootBones.push_back(getBoneCopyOfBone(_rootBones[i]));
        
    }
    
    copy->updateBoneMapping();
    
    return copy;

}
    
void ModelArmature::setPose(ArmatureAnimation* animation, float time){

    if(_animationMap.find(animation)!=_animationMap.end()){
    
        _dirty=true;
        
        ArmatureAnimationBridgeContainer* aabc=&_animationMap[animation];

        for (int i=0; i<aabc->array.size(); i++) {
            
            ArmatureAnimationBridge* aab=&aabc->array.at(i);
            BoneAnimationNode* anode=aab->node;
            
            if(anode->hasAnimation){
               
                anode->loadIntoTransform(&aab->bone->aTransform, time);
                aab->bone->animated=true;

               // aab->bone->setDirty(true);
            }
            

        }

    }


}
    
Bone* ModelArmature::getBoneCopyOfBone(Bone* bone){
    
    Bone* n= bone->getCopy();
    
    for (int i=0; i<bone->_childs.size(); i++) {
        
        n->addChild(getBoneCopyOfBone(bone->_childs[i]));

    }

    return n;
}

void ModelArmature::addAnimation(ArmatureAnimation* animation, const std::string& name){

    // Only add if not in yet
    if(_animationMap.find(animation)==_animationMap.end()){
    
        _animationMap.insert(std::make_pair(animation, ArmatureAnimationBridgeContainer()));
        ArmatureAnimationBridgeContainer* aabc=&_animationMap[animation];
        aabc->name=name;
        
        for (int i=0; i<animation->_animationNodes.size(); i++) {
        
            BoneAnimationNode* anode=animation->_animationNodes[i];
            
            //Bone* bone= getBoneNamed(anode->name);
            BoneNode* boneNode= getBoneNodeNamed(anode->name, &bone);
            
            // && bone Mask applied
            if(boneNode){
            
                ArmatureAnimationBridge aab;
                //aab.boneIndex=bone->_flatArrayIndex;
                aab.bone=boneNode;
                aab.node=anode;
                aabc->array.push_back(aab);

            }
            
            
        }
        
    
    }
    
    

}

void ModelArmature::updateMatrixArray(){
    
//    for (int i=0; i<_rootBones.size(); i++) {
//        
//        updateMatrixRecursive(_rootBones[i], Mat4::identity());
//        
//    }

    
    updateMatrixRecursive(&bone, Mat4::identity());
    
}
    
void ModelArmature::updateMatrixRecursive(BoneNode* bone, Mat4 ptransform){
    
    Mat4 localTransform;
    
    if(bone->animated){
    
        localTransform=bone->aTransform.getMatrix();
 

    }else{
    
        localTransform=bone->transform;
    
    }
    
    
    Mat4 globalTransForm=ptransform*localTransform;
    
    if(bone->bone){
        bone->bone->globalTransform=globalTransForm*bone->bone->offset;

        int index= getIndexOfBone(bone->name);
        _flatMatriciesArray[index]= globalTransForm*bone->bone->offset*inverseWorld;
    }
    
    for (int i=0; i<bone->childs.size(); i++) {
        
        updateMatrixRecursive(&bone->childs[i], globalTransForm);
        
    }

    

}

   
void ModelArmature::updateMatrixRecursive(Bone* bone, Mat4 ptransform){
    
    Mat4 newTransForm=ptransform*bone->localTransform*bone->transform.getMatrix();
    _flatMatriciesArray[bone->_flatArrayIndex]= newTransForm * bone->offset *inverseWorld;

    for (int i=0; i<bone->_childs.size(); i++) {
        
        updateMatrixRecursive(bone->_childs[i], newTransForm);
        
    }
    
 
}
    
    
ArmatureAnimation* ModelArmature::getAnimationWithName(std::string name){
    
    std::unordered_map<ArmatureAnimation*, ArmatureAnimationBridgeContainer>::iterator it;
    
    for (it=_animationMap.begin(); it!=_animationMap.end(); ++it) {
        
        if(it->second.name==name) return it->first;
        
    }
    
    
    return NULL;
}
    
ModelArmature::ModelArmature(){
    
    _numBones=0;
    _lastFrame=0;
    _dirty=false;
    
}
    
void ModelArmature::updateBoneMapping(){
    
    _boneMapping.clear();
    _flatBoneArray.clear();
        
    std::vector<Bone*> boneToVisit= _rootBones;
        
    unsigned int indexCount=0;
    for (int i=0; i<boneToVisit.size(); i=0) {
            
        Bone* b= boneToVisit[i];
        boneToVisit.erase(boneToVisit.begin()+i);
        
        b->_flatArrayIndex=(int)_flatBoneArray.size();
        _flatBoneArray.push_back(b);
        _boneMapping.insert(std::make_pair(b->_name, indexCount));
            
        for (int c=0; c<b->_childs.size(); c++) {
                
            Bone* child= b->_childs[c];
            boneToVisit.push_back(child);
            
        }
        
        indexCount++;
            
    }
    
    _flatMatriciesArray.resize(_flatBoneArray.size());

}

void ModelArmature::printBoneNames(){
    
    for (int i=0; i< _flatBoneArray.size(); i++) {
        
        std::cout << _flatBoneArray[i]->_name << std::endl;
        
    }

}
    
Bone* ModelArmature::getBoneNamed(std::string name){
    
    if(_boneMapping.find(name)!=_boneMapping.end()){
        
        return _flatBoneArray[_boneMapping[name]];
        
    }
    
    return NULL;
}
    
unsigned int ModelArmature::getIndexOfBone(std::string name){
    
    if(_boneMapping.find(name)!=_boneMapping.end()){
            
        return _boneMapping[name];
            
    }
        
    return 0;

}
    
unsigned int ModelArmature::numberOfBones(){
    
    return (unsigned int)_flatBoneArray.size();
    
}
    
Bone* ModelArmature::getBoneAtIndex(unsigned int index){
    
    return _flatBoneArray[index];
    
}
    
// Bone ///////////////////
    
Bone::Bone(){
        
    _isDirty=true;
    _parent=NULL;
        
}
    
Bone* Bone::getCopy(){
    
    Bone* copy= new Bone();
    
    copy->_name= _name;
    copy->transform=transform;
    copy->offset=offset;
    copy->customTransform=customTransform;
    copy->_isDirty=_isDirty;
    
    return copy;

}
    
bool Bone::isDirty(){
        
    return _isDirty;
        
}
    
void Bone::setDirty(bool dirty){
    
    _isDirty=dirty;

}
    
std::string Bone::getName(){
        
    return _name;
        
}
    
void Bone::addChild(Bone* bone){
        
    bone->_parent=this;
    _childs.push_back(bone);
        
}
    
const std::vector<Mat4>& ModelArmature::getMatrixArray(){
    
    return _flatMatriciesArray;

}

   
    
} // Namespace end
