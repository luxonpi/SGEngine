

#ifndef SGENGINE_MODELLOADER_H
#define SGENGINE_MODELLOADER_H

#include "SBase.h"

// Assimp imports
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"

#include "Node.h"
#include "Mesh.h"
#include "MeshData.h"

#include "Model.h"
#include "ModelRigged.h"
#include "ModelArmature.h"
#include "ArmatureAnimation.h"

namespace sge {
    
    enum{
    
        ML_FLAG_ANIMATION = 1,
        ML_FLAG_RIGGED = 2,

    };
    
    class ModelLoader{
    
        private:
        
            int _flags;
            ModelArmature* _armature;
        
            // Instance constructor
            ModelLoader();
        
            // Loader options
            const aiScene* _scene;
            Mesh* _mesh;
        
            void appendAiMeshToMesh(const aiMesh* aiMesh, const aiNode* node , Mesh* mesh, Model* model, Mat4 matrix);
            void processNodeToModel(aiNode* node, Model* model, Mesh* mesh, Mat4 matrix);
            void recursiveProcessScene(aiNode* node, Model* parentModel, Mat4 matrix);
        
            void loadAnimation(aiNode* node, aiAnimation* animation, ArmatureAnimation* armatureAnimation);
            const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string& NodeName);
        
            // Armature
            void processArmature(ModelArmature* armature);
            void getUnsortedBonesFromNode(aiNode* node, std::vector<Bone*>& bones);
            void getSkeletonRecursive(aiNode* node, BoneNode* bnode, ModelArmature* skelet, std::vector<Bone*>& bones, Bone* parentBone);
        
        const aiNode* FindNodeByName(const aiNode* node, const std::string& NodeName);
        const aiBone* FindBoneByName(const aiMesh* mesh, const std::string& NodeName);

        public:
        
            static ModelLoader* getInstance();
            void loadIntoModel(Model* model, ModelArmature* armature, std::string file, int flags);
            void loadIntoAnimation( ArmatureAnimation* armatureAnimation, std::string file, int flags);
        
        
    };
    


       
    
}


#endif
