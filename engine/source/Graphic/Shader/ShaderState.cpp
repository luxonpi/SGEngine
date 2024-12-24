

#include "ShaderState.h"
#include "Shader.h"

namespace sge {
    
    void ShaderState::setMainShader(Shader* shader){
    
        _mainShader=shader;
        
        if(_mainShader){
        
            std::unordered_map<std::string, Uniform>::iterator it;

            for ( it = uniforms.begin(); it != uniforms.end(); it++ ){
                
                it->second.location= shader->getUniformLocation(it->second.name);
                
            }
        
        }
    
    
    }

    
    void ShaderState::uploadToShader(Shader* shader){
    
        if(_mainShader==shader && shader!=NULL){
        
            std::unordered_map<std::string, Uniform>::iterator it;
            
            for ( it = uniforms.begin(); it != uniforms.end(); it++ ){
                
                setUniform(&it->second, shader,it->second.location);
                
            }
        
        }else{
        
            updateUniforms(shader);

        }
        
    
    }
    
    void ShaderState::copy(ShaderState* shaderState){
    
        uniforms=shaderState->uniforms;
    
    }
    
    ShaderState::ShaderState(){
        
        _mainShader=NULL;
    
   
    }
    
    void ShaderState::updateUniforms(Shader* shader){
    
        std::unordered_map<std::string, Uniform>::iterator it;
        
        for ( it = uniforms.begin(); it != uniforms.end(); it++ ){
      
                SInt location=shader->getUniformLocation(it->second.name);
                setUniform(&it->second, shader,location);
            
        }
    
    }
    
    void ShaderState::addObserver(ShaderState::Observer* observer){
    
        _observers.insert(observer);
    
    }
    
    void ShaderState::removeObserver(ShaderState::Observer* observer){
    
        _observers.erase(observer);
    
    }

    void ShaderState::setUniform(Uniform* uniform, Shader* shader, SInt location){
        
            switch (uniform->type) {
                case UNIFORM_MAT4:
                shader->setUniform4m(uniform->valueP, uniform->transpose, location);
                break;
                case UNIFORM_FLOAT:
                shader->setUniform1f(uniform->value.x, location);
                break;
                case UNIFORM_INT:
                shader->setUniform1i((int) uniform->value.x, location);
                break;
                case UNIFORM_TEXTURE:
                shader->setTexture(uniform->texture, (int) uniform->value.x,location);
                break;
                case UNIFORM_VEC4:
                shader->setUniform4f(uniform->value, location);
                break;
                case UNIFORM_VEC3:
                shader->setUniform3f(uniform->value.x, uniform->value.y, uniform->value.z, location);
                break;
                case UNIFORM_VEC2:
                shader->setUniform2f( uniform->value.x, uniform->value.y, location);
                break;
                case UNIFORM_MAT4V:
                shader->setUniform4mv(uniform->valueP, uniform->count, uniform->transpose, location);
                break;
                case UNIFORM_MAT4ARRAY:
                
                    shader->setUniform4mv(&uniform->array[0][0],(int) uniform->array.size(), uniform->transpose, location);
                
                break;
                
                case UNIFORM_VEC3ARRAY:
                
                    shader->setUniform3fv(&uniform->arrayVec3[0].x, (int)uniform->arrayVec3.size(), location);
                
                break;

                
                
                default:
                    
                    
                break;
            }
            
            return;
    
    }
    
    void ShaderState::hasChanged(){
    
        std::set<Observer*>::iterator it;
        
        for ( it = _observers.begin(); it != _observers.end(); it++ ){
            
            (*it)->shaderStateChanged(this);
            
        }
    
    }
    
    bool ShaderState::uniformExist(const std::string& name){
    
        return uniforms.find(name)!=uniforms.end();
    
    }

    void ShaderState::setUniformWithStrings(const std::string& name,const std::string& type, const std::string& value){
    
        std::vector<float> values;
        SString::getArrayFromString(value, values);
        
        if(type=="vec3"){
        
            setUniform3f(name, Vec3(values[0],values[1],values[2]));
        
        }else if(type=="vec2"){
        
            setUniform2f(name, Vec2(values[0],values[1]));

        
        }else if(type=="float"){
            
            setUniform1f(name, values[0]);

            
        }else if(type=="vec4"){
            
            setUniform4f(name, Vec4(values[0],values[1],values[2], value[3]));

        }else if(type=="int"){
            
            setUniform1i(name, int(values[0]));

        }
        
    }
    
    void ShaderState::setUniform1i(const std::string& name, int value){
    
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].value.x=value;
            hasChanged();
            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_INT;
        uniforms[name].value.x=value;
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();

    
    }
    
    void ShaderState::setUniform1f(const std::string& name, float value){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].value.x=value;
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_FLOAT;
        uniforms[name].value.x=value;
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();

    }
    
    void ShaderState::setUniform4f(const std::string& name, const Vec4& vec){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].value=vec;
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_VEC4;
        uniforms[name].value=vec;
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    }
    
    void ShaderState::setUniform2f(const std::string& name, const Vec2& vec){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].value=Vec4(vec.x, vec.y, 0, 0);
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_VEC2;
        uniforms[name].value=Vec4(vec.x, vec.y, 0, 0);
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    }
    
    void ShaderState::setUniform3f(const std::string& name, const Vec3& vec){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].value=Vec4(vec.x, vec.y, vec.z, 0);
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_VEC3;
        uniforms[name].value=Vec4(vec.x, vec.y, vec.z, 0);
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    
    }
    
    void ShaderState::setUniformTexture(const std::string& name, Texture* texture, int position){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].texture=texture;
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_TEXTURE;
        uniforms[name].texture=texture;
        uniforms[name].value.x=position;
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    }
    
    void ShaderState::setUniform4m(const std::string& name ,const float* value, bool transpose){
    
        bool exists=uniformExist(name);
        if(exists){
        
            memcpy(uniforms[name].valueP, value, 16* sizeof(float));
            uniforms[name].transpose=transpose;
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_MAT4;
        uniforms[name].valueP= new float[16];
        uniforms[name].transpose=transpose;
        memcpy(uniforms[name].valueP, value, 16* sizeof(float));
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    }
    
    void ShaderState::setUniformMat4Array(const std::string& name , const std::vector<Mat4>& array, bool transpose){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].array=array;
            hasChanged();
            
            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_MAT4ARRAY;
        uniforms[name].array=array;
        uniforms[name].transpose=transpose;

        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();

    
    }
    
    void ShaderState::setUniformVec3Array(const std::string& name, const std::vector<Vec3>& array){
    
        bool exists=uniformExist(name);
        if(exists){
            
            uniforms[name].arrayVec3=array;
            hasChanged();
            
            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_VEC3ARRAY;
        uniforms[name].arrayVec3=array;
        
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();

    
    }

    
    void ShaderState::setUniform4mv(const std::string& name, float* value, unsigned int count){
    
        bool exists=uniformExist(name);
        if(exists){
            
            memcpy(uniforms[name].valueP, value, 16* sizeof(float));
            hasChanged();

            return;
        }
        
        uniforms.insert(std::make_pair(name, Uniform()));
        uniforms[name].name=name;
        uniforms[name].type=UNIFORM_MAT4V;
        uniforms[name].valueP= value;
        uniforms[name].count=count;
        if(_mainShader) uniforms[name].location=_mainShader->getUniformLocation(name);
        hasChanged();


    }
    
}


