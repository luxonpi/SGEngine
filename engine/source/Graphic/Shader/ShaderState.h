

#ifndef SGENGINE_SHADERSTATE_H
#define SGENGINE_SHADERSTATE_H

#include "SBase.h"
#include "Texture.h"

namespace sge {

class Shader;
class ShaderModule;
     
#define UNIFORM_INT 0
#define UNIFORM_FLOAT 1
#define UNIFORM_VEC2 2
#define UNIFORM_VEC3 3
#define UNIFORM_MAT4 4
#define UNIFORM_VEC3V 5
#define UNIFORM_TEXTURE 6
#define UNIFORM_VEC4 7
#define UNIFORM_MAT4V 8
#define UNIFORM_MAT4ARRAY 9
#define UNIFORM_VEC3ARRAY 10

struct Uniform{

    int type;
    std::string name;
    unsigned int count;
    Vec4 value;
    float* valueP;
    Texture* texture;
    bool transpose;
    SInt location;
    
    std::vector<Mat4> array;
    std::vector<Vec3> arrayVec3;

    Uniform(){};
    
};
    
class ShaderState{
    
public:
    class Observer{
    
    public:
        virtual void shaderStateChanged(ShaderState* state)=0;
        
    };
    
friend Shader;
friend ShaderModule;
    
private:
    
    
    std::unordered_map<std::string, Uniform> uniforms;
    
    bool uniformExist(const std::string& name);
    
    void setUniform(Uniform* uniform, Shader* shader, SInt location);
    void updateUniforms(Shader* shader);
    
    std::set<Observer*> _observers;

    void hasChanged();
    Shader* _mainShader;
    
public:

    ShaderState();
    
    void setMainShader(Shader* shader);

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    
    void copy(ShaderState* shaderState);
    
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform2f(const std::string& name, const Vec2& vec);
    void setUniform3f(const std::string& name, const Vec3& vec);
    void setUniform4f(const std::string& name, const Vec4& vec);
    void setUniformMat4Array(const std::string& name, const std::vector<Mat4>& array, bool transpose);
    void setUniform4m(const std::string& name, const float* value, bool transpose);
    void setUniform4mv(const std::string& name, float* value, unsigned int count);
    void setUniformTexture(const std::string& name, Texture* texture, int position);
    void setUniformWithStrings(const std::string& name,const std::string& type, const std::string& value);
    void setUniformVec3Array(const std::string& name, const std::vector<Vec3>& array);

    void uploadToShader(Shader* shader);


};

}

#endif
