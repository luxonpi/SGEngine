

#ifndef SGENGINE_MESHDATA_H
#define SGENGINE_MESHDATA_H

#include "GraphicDeviceDefines.h"
#include "Vec3.h"
#include "Matrix.h"

namespace sge {

#define NUM_BONES_PER_VERTEX 4
    
struct VertexData{
    Vec3 position;
	Vec3 normal;
	Vec3 tangent;
	Vec3 color;
	float U,V;
};

    
struct VertexBoneData{
    
    SShort IDs[NUM_BONES_PER_VERTEX];
    SFloat Weights[NUM_BONES_PER_VERTEX];
        
    VertexBoneData(){
        
        Reset();
    };
        
    void Reset(){
        
        for(int i=0; i<NUM_BONES_PER_VERTEX; i++){
        
            IDs[i]=0;
            Weights[i]=0;
            
        }
    }
        
    void AddBoneData(SShort BoneID, float Weight){
    
        
        for (SShort i = 0 ; i < NUM_BONES_PER_VERTEX ; i++) {
            if (Weights[i] == 0.0) {
                IDs[i]     = BoneID;
                Weights[i] = Weight;
                return;
            }
        }
            
            // should never get here - more bones than we have space for
        //assert(0);
    }
    
};
    
}

#endif
