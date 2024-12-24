

#include "SBase.h"
#include "Director.h"
#include "ModelLoader.h"
#include "ArmatureAnimation.h"

namespace sge {
    
    inline sge::Mat4 convertToAiMat4(const aiMatrix4x4& aiMat){
        
        return sge::Mat4(aiMat[0][0],aiMat[0][1],aiMat[0][2],aiMat[0][3],
                         aiMat[1][0],aiMat[1][1],aiMat[1][2],aiMat[1][3],
                         aiMat[2][0],aiMat[2][1],aiMat[2][2],aiMat[2][3],
                         aiMat[3][0],aiMat[3][1],aiMat[3][2],aiMat[3][3]);}

    
    ModelLoader::ModelLoader(){}
    ModelLoader* ModelLoader::getInstance(){

        static ModelLoader* instance= new ModelLoader();
        return instance;

    }
    
    void ModelLoader::loadIntoAnimation( ArmatureAnimation* armatureAnimation, std::string file, int flags){
    
        std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
        
        _scene=aiImportFile(fullPath.c_str(), aiProcessPreset_TargetRealtime_Quality);
        
        // Error while loading
        if(!_scene){
            
            std::cout << "Model '"<<file<<"' wasn't successfuly opened" << aiGetErrorString() << std::endl;
            assert(_scene);
            return;
            
        }
        
        
        _flags=flags;
        
        _armature=NULL;
        
        // More than one animation -> don't know how to handle
        assert(_scene->mNumAnimations==1);
        
        for (int i=0; i<_scene->mNumAnimations; i++) {
                
            aiAnimation* animation= _scene->mAnimations[i];
            
            float TicksPerSecond = (float)(animation->mTicksPerSecond != 0 ?animation->mTicksPerSecond : 25.0f);
            float TimeInSeconds  = animation->mDuration / TicksPerSecond;
                
            armatureAnimation->_duration=TimeInSeconds;
                
            loadAnimation(_scene->mRootNode,animation,armatureAnimation);
        }
            
        
        // Delete loader and scene after done
        aiReleaseImport(_scene);
        
        return;
    
    }
    
    void ModelLoader::loadIntoModel(Model* model, ModelArmature* armature, std::string file, int flags){
    
        std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
        
        std::stringstream ss;
        ss<<file<<flags;
        
        Mesh* m= Mesh::getInstancedMesh(ss.str());
        if(m){
        
            model->getRenderObject()->setMesh(m);
            return;
            
        }

        _scene=aiImportFile(fullPath.c_str(), aiProcess_FlipUVs | aiProcess_Triangulate |aiProcessPreset_TargetRealtime_Quality | aiProcess_CalcTangentSpace);
        
        // Error while loading
        if(!_scene){
            
            std::cout << "Model '"<<file<<"' wasn't successfuly opened" << aiGetErrorString() << std::endl;
            assert(_scene);
            return;
        
        }
        

        _flags=flags;
        
        _armature=NULL;
        if(armature){
          
            _armature=armature;
            processArmature(armature);
            
        
        }
        
        if(_flags & ML_FLAG_RIGGED){
            
            _mesh=new Mesh(MESH_NORMALS | MESH_TEXCOORDS | MESH_COLORS | MESH_TANGENTS | MESH_POSONLY | MESH_BONES);
            
        }else{
            
            _mesh=new Mesh(MESH_NORMALS | MESH_TEXCOORDS | MESH_COLORS | MESH_TANGENTS | MESH_POSONLY);
            
        }
        
        _mesh->Resource::name=ss.str();
      
        model->getRenderObject()->setDrawAble(true);
        
        // Create the new model
        recursiveProcessScene(_scene->mRootNode, model, Mat4::identity());
    
        
        if(_mesh->tangents.size()==0){
            
            _mesh->removeAttribute(MESH_TANGENTS);
            
        }else if(_mesh->tangents.size()!=_mesh->positions.size()){
            
            _mesh->tangents.resize(_mesh->positions.size());
            
        }
        
        
        model->getRenderObject()->setMesh(_mesh);
        _mesh->update();
        
        Mesh::insertInstancedMesh(_mesh, ss.str());
        
        if(flags & ML_FLAG_ANIMATION){
            
            for (int i=0; i<_scene->mNumAnimations; i++) {
                
                aiAnimation* animation= _scene->mAnimations[i];
                ArmatureAnimation* armAnim= new ArmatureAnimation();
                
                float TicksPerSecond = (float)(animation->mTicksPerSecond != 0 ?animation->mTicksPerSecond : 25.0f);
                float TimeInSeconds  = animation->mDuration / TicksPerSecond;
                
                armAnim->_duration=TimeInSeconds;
                
                loadAnimation(_scene->mRootNode,animation,armAnim);
                if(armature) armature->addAnimation(armAnim, "main");
            }
            
        
        
        }
        
    
     
        // Delete loader and scene after done
        aiReleaseImport(_scene);
        
        return;
        
    }
    
    
    
    const aiNodeAnim* ModelLoader::FindNodeAnim(const aiAnimation* pAnimation, const std::string& NodeName)
    {
        for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
            
            if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }
        
        return NULL;
    }
    
    // Methods
    void ModelLoader::loadAnimation(aiNode* node, aiAnimation* animation, ArmatureAnimation* armatureAnimation){
        
        std::string aiNodeName(node->mName.data);
        float TicksPerSecond = (float)(animation->mTicksPerSecond != 0 ?animation->mTicksPerSecond : 25.0f);
        
        for (uint i = 0 ; i < animation->mNumChannels ; i++) {
            const aiNodeAnim* animNode = animation->mChannels[i];
            
            BoneAnimationNode* banChild= new BoneAnimationNode();
            armatureAnimation->_animationNodes.push_back(banChild);
            banChild->name=std::string(animNode->mNodeName.data);
            
            for (uint i = 0 ; i < animNode->mNumScalingKeys; i++) {
                
                const aiVector3D& vector= animNode->mScalingKeys[i].mValue;

                BoneAnimationNode::KeyFrame keyFrame;
                keyFrame.valueVector.set(float(vector.x),float(vector.y),float(vector.z));
                keyFrame.time=(float) animNode->mScalingKeys[i].mTime/TicksPerSecond;
                banChild->scalingKeys.push_back(keyFrame);
                
            }
            
            for (uint i = 0 ; i < animNode->mNumPositionKeys ; i++) {
                
                const aiVector3D& vector= animNode->mPositionKeys[i].mValue;
          
                BoneAnimationNode::KeyFrame keyFrame;
                keyFrame.valueVector.set( float(vector.x),float(vector.y),float(vector.z));
                keyFrame.time=(float) animNode->mPositionKeys[i].mTime/TicksPerSecond;
                banChild->translationKeys.push_back(keyFrame);
                
                banChild->hasAnimation=true;
                
            }
            
            
            for (uint i = 0 ; i < animNode->mNumRotationKeys ; i++) {
                
                const aiQuaternion& vector= animNode->mRotationKeys[i].mValue;

                
                BoneAnimationNode::KeyFrame keyFrame;
                keyFrame.valueQuaternion.set(float(vector.x),float(vector.y),float(vector.z),float(vector.w));
                keyFrame.time=(float) animNode->mRotationKeys[i].mTime/TicksPerSecond;
                banChild->rotationKeys.push_back(keyFrame);
                banChild->hasAnimation=true;
                
            }
            

            // Calc Durationsr
            for (int i=0; i<armatureAnimation->_animationNodes.size(); i++) {
                
                BoneAnimationNode* aiNode=armatureAnimation->_animationNodes[i];
                
                for (int a=0; a<aiNode->scalingKeys.size()-1; a++) {
                    
                    aiNode->scalingKeys[a].duration= aiNode->scalingKeys[a+1].time- aiNode->scalingKeys[a].time;
                    
                }
                
                for (int a=0; a<aiNode->translationKeys.size()-1; a++) {
                    
                    aiNode->translationKeys[a].duration= aiNode->translationKeys[a+1].time- aiNode->translationKeys[a].time;
                    
                }
                
                for (int a=0; a<aiNode->rotationKeys.size()-1; a++) {
                    
                    aiNode->rotationKeys[a].duration= aiNode->rotationKeys[a+1].time- aiNode->rotationKeys[a].time;
                    
                }
                
            }
            
            
            
        }
        
    
    }
    
    void ModelLoader::recursiveProcessScene(aiNode* node, Model* parentModel, Mat4 matrix){
    
        Mat4 nodeTransForm= convertToAiMat4(node->mTransformation);
        if(!nodeTransForm.isIdentity()) matrix=matrix*nodeTransForm;
    
        bool breakNode=false;
        if(node->mNumMeshes>0){
        
            parentModel->setID(node->mName.C_Str());

//            Mesh* mesh;
//            
//            if(_flags & ML_FLAG_RIGGED){
//            
//                mesh=new Mesh(MESH_NORMALS | MESH_TEXCOORDS | MESH_COLORS | MESH_TANGENTS | MESH_POSONLY | MESH_BONES);
//            
//            }else{
//            
//                mesh=new Mesh(MESH_NORMALS | MESH_TEXCOORDS | MESH_COLORS | MESH_TANGENTS | MESH_POSONLY);
//            
//            }
            
            processNodeToModel(node, parentModel, _mesh, matrix);

           // parentModel->getRenderObject()->setMesh(mesh);
           // parentModel->getRenderObject()->setDrawAble(f);

            breakNode=true;
        
        }else{
        
           // parentModel->getRenderObject()->setDrawAble(false);
      
        }
    
        //recursion
        for(int i=0;i<node->mNumChildren;i++){
            
//            if(breakNode){
//            
//                Model* model= new Model();
//                model->getRenderObject()->setDrawAble(false);
//                recursiveProcessScene(node->mChildren[i], model, matrix);
//                parentModel->addChild(model);
//            
//            }else{
            
                recursiveProcessScene(node->mChildren[i], parentModel, matrix);
            
         //   }
        
        
        }
    
    }

    void ModelLoader::processNodeToModel(aiNode* node, Model* model, Mesh* mesh, Mat4 matrix){
    
        // Initialize the meshes in the scene one by one
        for (uint i = 0 ; i < node->mNumMeshes ; i++) {
        
            const aiMesh* aimesh=_scene->mMeshes[node->mMeshes[i]];
            
            appendAiMeshToMesh(aimesh, node, mesh, model, matrix);
    
        }

    }


    void ModelLoader::appendAiMeshToMesh(const aiMesh* aiMesh, const aiNode* node , Mesh* mesh, Model* model, Mat4 matrix){
    
        unsigned int baseIndex= (unsigned int) mesh->positions.size();
    
        std::vector<Texture*> textures;
    
        aiColor4D col;
        aiMaterial* mat=_scene->mMaterials[aiMesh->mMaterialIndex];
    
        aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);
        Vec3 defaultColor(col.r,col.g,col.b);
        
        for(int i=0;i<aiMesh->mNumVertices;i++){
            
            // Positions
            Vec4 pos=Vec4(aiMesh->mVertices[i].x,aiMesh->mVertices[i].y,aiMesh->mVertices[i].z,1);
            pos=matrix*pos;
            mesh->contentBox.merge(pos.xyz());
            mesh->positions.push_back(pos.xyz());
            
           
            // Normals
            Mat4 nMatrix=matrix;
            nMatrix.inverse();
            nMatrix.transpose();
            
            if(aiMesh->mNormals){
            
                Vec3 normal=Vec3(aiMesh->mNormals[i].x,aiMesh->mNormals[i].y,aiMesh->mNormals[i].z);
                normal=nMatrix*normal;
                normal.normalize();
                
                mesh->normals.push_back(normal);

            }
            
            // Tangents
            if(aiMesh->mTangents){
                
                Vec3 tangent=Vec3(aiMesh->mTangents[i].x,aiMesh->mTangents[i].y,aiMesh->mTangents[i].z);
                tangent=nMatrix*tangent;
                tangent.normalize();
                
                mesh->tangents.push_back(tangent);

            }

            // Colors
            Vec3 color;
            if(aiMesh->mColors[0]){
                
                color=Vec3(aiMesh->mColors[0][i].r, aiMesh->mColors[0][i].g, aiMesh->mColors[0][i].b);
                
            }else{
                
                color=defaultColor;
            }
            
            mesh->colors.push_back(color);
            
            // Texcoords
            Vec2 uv;
            if(aiMesh->mTextureCoords[0]){
                
                uv.x=aiMesh->mTextureCoords[0][i].x;
                uv.y=aiMesh->mTextureCoords[0][i].y;
            
            }else{
            
                uv.x=uv.y=0.0;
            
            }
            
            mesh->texCoords.push_back(uv);
            
        }
        
    
        for(int i=0;i<aiMesh->mNumFaces;i++){
            
            aiFace face=aiMesh->mFaces[i];
            for(int j=0; j<face.mNumIndices; j++){
            
                mesh->indices.push_back (baseIndex+face.mIndices[j]);
        
            }
            
        }
    
    aiColor4D spec;
    aiGetMaterialColor(mat,AI_MATKEY_COLOR_SPECULAR,&spec);
   
   // mesh->material.specularColor =  Color(spec.r*255,spec.g*255,spec.b*255,1) ;
    
    float shininess=0.0;
    mat->Get( AI_MATKEY_SHININESS, shininess );
    
    float reflecticity=0.0;
    mat->Get( AI_MATKEY_REFLECTIVITY, reflecticity );
    
    int shadingModel=0;
    mat->Get( AI_MATKEY_SHADING_MODEL, shadingModel );
    
    if(shadingModel==aiShadingMode_Phong){
    
        reflecticity=1;
    
    }else if(shadingModel==aiShadingMode_NoShading){
        
        reflecticity=0;
        
    }
    
  //  mesh->material.roughness=(shininess+1.0)*0.125;
    
    for(int i=0;i<mat->GetTextureCount(aiTextureType_HEIGHT);i++){
        
        aiString str;
        mat->GetTexture(aiTextureType_HEIGHT,i,&str);
        
        //if(!SString::containsString(str.C_Str(), "ddn")) continue;
        
        Texture* tex= Texture::get(str.C_Str());
        if(tex){
     
          //  mesh->material.setNormalTexture(tex);
        
        }
        
    }
    
    
    
    for(int i=0;i<mat->GetTextureCount(aiTextureType_SHININESS);i++){
        
        aiString str;
        mat->GetTexture(aiTextureType_SHININESS,i,&str);
        
        //if(!SString::containsString(str.C_Str(), "ddn")) continue;
        
        Texture* tex= Texture::get(str.C_Str());
        if(tex){
            
           // mesh->material.setMaterialTexture(tex);
            
        }
        
    }

    for(int i=0;i<mat->GetTextureCount(aiTextureType_DISPLACEMENT);i++){
        
        aiString str;
        mat->GetTexture(aiTextureType_HEIGHT,i,&str);
        
        if(!SString::containsString(str.C_Str(), "ddn")) continue;
        
        Texture* tex= Texture::get(str.C_Str());
        if(tex){
            
             //   mesh->material.setNormalTexture(tex);
            
        }
        
    }


    
    for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++){
        
        aiString str;
        mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
        
//        Texture* tex= Texture::get(str.C_Str());
//        if(tex){
//      
//            mesh->material.diffuseMap=tex;
//
//        }
        
    }
        
        
        if(_flags & ML_FLAG_RIGGED){
            
            mesh->bones.resize(mesh->positions.size());
            
            for (uint i = 0 ; i < aiMesh->mNumBones ; i++) {
                
                uint BoneIndex = 0;
                std::string BoneName(aiMesh->mBones[i]->mName.data);
                
                if(_armature && _armature->getBoneNamed(BoneName)){
                    
                    BoneIndex= _armature->getIndexOfBone(BoneName);
                    
                }
                
                VertexBoneData vbd;
                
                //Load Vertex - Bones Relations into model
                for (uint j = 0 ; j < aiMesh->mBones[i]->mNumWeights ; j++) {
                    
                    uint VertexID =  aiMesh->mBones[i]->mWeights[j].mVertexId;
                    float Weight  = aiMesh->mBones[i]->mWeights[j].mWeight;
                    
                    mesh->bones[baseIndex+ VertexID].AddBoneData(BoneIndex, Weight);
                    
                }
                
            }
            
        }
    

}
    

   
//// Skeleton
void ModelLoader::processArmature(ModelArmature* armature){
    
    std::vector<Bone*> bones;
    getUnsortedBonesFromNode(_scene->mRootNode, bones);
    getSkeletonRecursive(_scene->mRootNode, &_armature->bone, armature, bones, NULL);
    
    armature->updateBoneMapping();
    
}
    
void ModelLoader::getUnsortedBonesFromNode(aiNode* node, std::vector<Bone*>& bones){
    
    aiMatrix4x4 inverseworld=_scene->mRootNode->mTransformation;
    inverseworld=inverseworld.Inverse();
    
    _armature->inverseWorld=convertToAiMat4(inverseworld);
    
    for (int i=0; i<node->mNumMeshes; i++) {
            
        aiMesh* mmesh= _scene->mMeshes[node->mMeshes[i]];
            
        for (int b=0; b<mmesh->mNumBones; b++) {
                
            // aiBone
            const aiBone* bone = mmesh->mBones[b];
            std::string BoneName(bone->mName.data);
            
            // Check if bone was already added
            bool alreadyIn=false;
            for (int ai=0; ai<bones.size(); ai++) {
                    
                if(bones[ai]->_name==BoneName){
                        
                    alreadyIn=true;
                    break;
                }
                    
            }
            
        
        
            // If not already in make new Bone
            if (!alreadyIn) {
                    
                Bone* newBone= new Bone();
                bones.push_back(newBone);
                    
                newBone->_name=BoneName;
                    
                
                const aiNode* node2 = FindNodeByName( _scene->mRootNode, bone->mName.C_Str());
                const aiNode* tempNode = node2->mParent;
                
                aiMatrix4x4 nodeTransform;

                // Add transforms of parents to bone
                while(tempNode){
                
                    const aiBone* bbone= FindBoneByName(mmesh, std::string(tempNode->mName.C_Str()));
                    if(bbone) break;
//
                    nodeTransform= tempNode->mTransformation*nodeTransform;   // check your matrix multiplication order here!!!
                    tempNode = tempNode->mParent;
                
                        
                }
                
                
                //glm::mat4 inv= glm::inverse(newBone->BoneOffset);
                Mat4 global= convertToAiMat4(nodeTransform);
                Mat4 globalInverse;
                global.inverse(&globalInverse);

                Mat4 offset= convertToAiMat4(bone->mOffsetMatrix);
                
                Mat4 nt= convertToAiMat4(node2->mTransformation);
                Vec3 pos(0,0,0);
                Vec3 scale(0,0,0);
                Quaternion quat;
                
                nt.decompose(&scale, &quat, &pos);
                
                newBone->transform.setTranslation(pos);
                newBone->transform.setScale(scale.x,scale.y,scale.z);
                newBone->transform.setRotation(quat);

            
                newBone->offset= offset;
                
                newBone->localTransform= global;


                //newBone->_transform= nodeTrans.inverse();
               // newBone->_finalTransformation=  m_GlobalInverseTransform*newBone->_boneOffset*nodeTrans;
                //newBone->position=Vec3(nodeTrans[0][3],nodeTrans[1][3], nodeTrans [2][3]);
            }
                
        }
            
    }
        
    //recursion
    for(int i=0;i<node->mNumChildren;i++){
            
        getUnsortedBonesFromNode(node->mChildren[i], bones);
            
    }
        
}
    
void ModelLoader::getSkeletonRecursive(aiNode* node, BoneNode* bnode, ModelArmature* skelet, std::vector<Bone*>& bones, Bone* parentBone){
    
    Bone* bbone=parentBone;
    // aiBone
    std::string nodeName (node->mName.data);
  
    bnode->name=nodeName;
    bnode->transform=convertToAiMat4(node->mTransformation);
        
    // Get bone from array
    for (int ai=0; ai<bones.size(); ai++) {
            
        if(bones[ai]->_name==nodeName){
            
            bnode->bone=bones[ai];
            bbone=bones[ai];
            bones.erase(bones.begin()+ai);
            break;
        }
            
    }
        
    if(bbone && parentBone!=bbone){
            
        if(parentBone) parentBone->addChild(bbone);
        else{
                
            skelet->_rootBones.push_back(bbone);
                
        }
            
    }
    
        
    //recursion
    bnode->childs.resize(node->mNumChildren);
    
    for(int i=0;i<node->mNumChildren;i++){
        
        BoneNode childNode;
        bnode->childs[i].parent=bnode;
        
        getSkeletonRecursive(node->mChildren[i], &bnode->childs[i] ,skelet, bones, bbone);
            
    }
        
}
    
//
//ModelRigged* ModelLoader::modelFromSkel(ModelArmature* modelSkel){
//        
//    ModelRigged* m= new ModelRigged();
//
//    Mesh* mesh= new Mesh();
//    
//    std::vector<Bone*> boneToVisit1= modelSkel->_rootBones;
//        
//    unsigned int bonecoount=0;
//    for (int i=0; i<boneToVisit1.size(); i=0) {
//            
//        Bone* b= boneToVisit1[i];
//        boneToVisit1.erase(boneToVisit1.begin()+i);
//        
////        Label* label= Label::create(b->name, "assets/fonts/BebasNeue.ttf", 40);
////        label->setPosition(b->position*0.01);
////        label->setScale(0.001);
////        label->setRenderLayer(3);
////        m->addChild(label);
//        
//        for (int c=0; c<b->_childs.size(); c++) {
//                
//            Bone* child= b->_childs[c];
//            boneToVisit1.push_back(child);
//        
//        }
//        
//        bonecoount++;
//    
//    }
//    
//
//    mesh->bones.resize(bonecoount);
//    
//        
//    std::vector<Bone*> boneToVisit= modelSkel->_rootBones;
//        
//    unsigned int indexCount=0;
//    for (int i=0; i<boneToVisit.size(); i=0) {
//            
//        Bone* b= boneToVisit[i];
//        boneToVisit.erase(boneToVisit.begin()+i);
//            
//        mesh->positions.push_back(Vec3(b->position.x, b->position.y, b->position.z));
//        mesh->colors.push_back(Vec3(1-indexCount/float(bonecoount),0,indexCount/float(bonecoount)));
//        mesh->normals.push_back(Vec3(0,0,0));
//        mesh->texCoords.push_back(Vec2(0, 0));
//            
//        int BoneID= modelSkel->_boneMapping[b->_name];
//        mesh->bones[indexCount].AddBoneData(BoneID, 1);
//        
//        for (int c=0; c<b->_childs.size(); c++) {
//                
//            Bone* child= b->_childs[c];
//            mesh->indices.push_back(indexCount);
//            mesh->indices.push_back((unsigned int)( indexCount+boneToVisit.size()+1));
//                
//            boneToVisit.push_back(child);
//        }
//        
//        indexCount++;
//        
//        }
//        
//        m->setArmature(modelSkel);
//        m->getRenderObject()->setDrawMode(DrawMode::LINES);
//    
//        mesh->update();
//        m->getRenderObject()->setMesh(mesh);
//    
//        return m;
//    
//    
//    }
//
    
    const aiNode* ModelLoader::FindNodeByName(const aiNode* node, const std::string& NodeName){
        
        for (int i=0; i<node->mNumChildren; i++) {
            
            aiNode* n= node->mChildren[i];
            
            if(std::string(n->mName.C_Str())==NodeName) return n;
            
            const aiNode* nf= FindNodeByName(n, NodeName);
            if(nf) return nf;
            
        }
        
        return NULL;
    }
    
    
    const aiBone* ModelLoader::FindBoneByName(const aiMesh* mesh, const std::string& NodeName){
      
        for (int b=0; b<mesh->mNumBones; b++) {
            
            // aiBone
            const aiBone* bone = mesh->mBones[b];
            if(std::string(bone->mName.C_Str())==NodeName) return bone;

        }
        
        
        return NULL;
    }
  

}
