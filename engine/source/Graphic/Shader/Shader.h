

#ifndef SGENGINE_SHADER_H
#define SGENGINE_SHADER_H

#include "SBase.h"
#include "Texture.h"
#include "ShaderState.h"

#define SHADER_UNIFORM_MVP_MATRIX 0
#define SHADER_UNIFORM_MODEL_MATRIX  1
#define SHADER_UNIFORM_PROJECTION_MATRIX  2
#define SHADER_UNIFORM_VIEW_MATRIX  3
#define SHADER_UNIFORM_NORMAL_MATRIX  4
#define SHADER_UNIFORM_DIFFUSE_TEX 5
#define SHADER_UNIFORM_MAT_TEX 6
#define SHADER_UNIFORM_NORMAL_TEX 7
#define SHADER_UNIFORM_GLOBAL_TIME 8
#define SHADER_UNIFORM_CAMWORLDPOS 9
#define SHADER_UNIFORM_MATERIAL 10
#define SHADER_UNIFORM_INVERSEPROJECTION 11
#define SHADER_UNIFORM_PROJECTION_VIEW_MATRIX  12
#define SHADER_UNIFORM_MASK_TEX 13

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define COLOR_LOCATION       3
#define TANGENT_LOCATION     4
#define BONE_ID_LOCATION     5
#define BONE_WEIGHT_LOCATION 6
#define MATERIAL_LOCATION 7

namespace sge {
    
    class GraphicDevice;
    class GraphicDeviceOpenGL;
    class ShaderModule;
    class ShaderManager;
    
    class Shader{
        
        friend ShaderModule;
        friend GraphicDevice;
        friend ShaderManager;
        friend GraphicDeviceOpenGL;

    protected:
        
        void init();
        
        std::string _vertexSource;
        std::string _fragSource;
    
        // To Do Reduce to one constructor
        Shader(){}
        Shader(const Shader& shader){}
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();
        
        void recompile(const std::string& vertexSource, const std::string& fragmentSource);

        ShaderModule* _parentModule;
        
        // Member Variables
        SInt _shaderID;
        SInt _internID;
        std::string _nameID;
        SInt _subShaderIDs[4];
        
        // Member Methods
        void checkShaderError(SUint shader, SUint flag, bool isProgram, const std::string& errorMessage, bool printSource);
        SUint createShader(const std::string& text, unsigned int type);
	
    public:
        
        std::vector<std::string> shaderDefines;
        
        std::set<ShaderState*> _dirtyShaderStates;
        ShaderState initUniforms;
        
        ShaderModule* getParentModule();
        
        std::vector<SUint> _requestedEngineUniforms;
        SInt _engineUniformPositions[20];
        
        std::bitset<16> uniformBitmap;
        std::bitset<16> attributeBitmap; 
        // ShaderStates

        static void printShaderSourceWithLineNumbers(const std::string& source);
    
        // Public Member Methods
        void bind();
        void unbind();
        const SInt& getID();
        const SInt& getInternID();
        
        void updateDirtyShaderStates();

        void printSource();
        
        // Uniform setter
        SInt getUniformLocation(const std::string& name);
   
        void setUniform1i( const int& value1 , SInt location   );
        void setUniform1f( const float& value1, SInt location   );
        void setUniform2f( const float& value1, const float& value2, SInt location   );
        void setUniform3f( const float& value1, const float& value2, const float& value3, SInt location  );
        void setUniform4f( const Vec4& value, SInt location );
        void setUniform3fv(float* value, const int& size, SInt location );
        void setUniform3m( float* value, const bool&  transpose, SInt location );
        void setUniform4m( float* value, const bool&  transpose, SInt location );
        void setUniform4mv(float* value, int count, const bool&  transpose, SInt location );
        void setTexture(Texture* texture, const  int& position, SInt location );
        void setUniform3f( const Vec3& vec, SInt location  );

    
    };

}

#endif
