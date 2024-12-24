

#include "Shader.h"
#include "ShaderModule.h"
#include "Director.h"
#include "GraphicDeviceDefines.h"
#include "ShaderManager.h"

#include "glInclude.h"

using namespace std;

namespace sge {
    
    void Shader::init(){
    
        _shaderID=-1;
       
        for (int i=0; i<4; i++) {
            _subShaderIDs[i]=-1;
        }
        
        uniformBitmap=0;

    }
    
    const SInt& Shader::getInternID(){
    
        return _internID;
    
    }
    
    ShaderModule* Shader::getParentModule(){
    
        return _parentModule;
    
    }
    
    void Shader::recompile(const std::string& vertexSource, const std::string& fragmentSource){
    
        uniformBitmap=0;
        
        
        _vertexSource=vertexSource;
        _fragSource=fragmentSource;
        
        for (int i=0; i<20; i++) {
            _engineUniformPositions[i]=-1;
        }
        
        if(_fragSource.find("u_sge_mainTex") != std::string::npos){     uniformBitmap.set(SHADER_UNIFORM_DIFFUSE_TEX); }
        if(_fragSource.find("u_sge_normalTex") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_NORMAL_TEX); }
        if(_fragSource.find("u_sge_matTex") != std::string::npos ){     uniformBitmap.set(SHADER_UNIFORM_MAT_TEX); }
        if(_fragSource.find("u_sge_maskTex") != std::string::npos ){    uniformBitmap.set(SHADER_UNIFORM_MASK_TEX); }
        
        
        if(_vertexSource.find("u_sge_mvpMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_MVP_MATRIX); }
        if(_vertexSource.find("u_sge_normalMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_NORMAL_MATRIX); }
        if(_vertexSource.find("u_sge_modelMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_MODEL_MATRIX); }
        if(_vertexSource.find("u_sge_viewMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_VIEW_MATRIX); }
        if(_vertexSource.find("u_sge_projectionMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_PROJECTION_MATRIX); }
        if(_vertexSource.find("u_sge_inverseProjectionMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_INVERSEPROJECTION); }
        if(_vertexSource.find("u_sge_projectionViewMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_PROJECTION_VIEW_MATRIX); }
        
        if(_fragSource.find("u_sge_mvpMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_MVP_MATRIX); }
        if(_fragSource.find("u_sge_normalMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_NORMAL_MATRIX); }
        if(_fragSource.find("u_sge_modelMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_MODEL_MATRIX); }
        if(_fragSource.find("u_sge_viewMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_VIEW_MATRIX); }
        if(_fragSource.find("u_sge_projectionMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_PROJECTION_MATRIX); }
        if(_fragSource.find("u_sge_inverseProjectionMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_INVERSEPROJECTION); }
        if(_fragSource.find("u_sge_projectionViewMatrix") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_PROJECTION_VIEW_MATRIX); }
        
        
        if(_vertexSource.find("u_sge_camWorldPos") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_CAMWORLDPOS); }
        if(_vertexSource.find("u_sge_time") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_GLOBAL_TIME); }
        
        if(_fragSource.find("u_sge_camWorldPos") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_CAMWORLDPOS); }
        if(_fragSource.find("u_sge_time") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_GLOBAL_TIME); }
        if(_fragSource.find("u_sge_material") != std::string::npos ){  uniformBitmap.set(SHADER_UNIFORM_MATERIAL); }
        
        if(_vertexSource.find("a_position") != std::string::npos ){  attributeBitmap.set(POSITION_LOCATION); }
        if(_vertexSource.find("a_uv") != std::string::npos ){  attributeBitmap.set(TEX_COORD_LOCATION); }
        if(_vertexSource.find("a_normal") != std::string::npos ){  attributeBitmap.set(NORMAL_LOCATION); }
        if(_vertexSource.find("a_color") != std::string::npos ){  attributeBitmap.set(COLOR_LOCATION); }
        if(_vertexSource.find("a_tangent") != std::string::npos ){  attributeBitmap.set(TANGENT_LOCATION); }
        if(_vertexSource.find("a_boneID") != std::string::npos ){  attributeBitmap.set(BONE_ID_LOCATION); }
        if(_vertexSource.find("a_boneWeights") != std::string::npos ){  attributeBitmap.set(BONE_WEIGHT_LOCATION); }
        
        
        GraphicDevice* graphicDevice= Director::getInstance()->getGraphicDevice();
        
        if(_shaderID!=-1) graphicDevice->releaseShader(this);
        
        graphicDevice->generateShader(this);
        graphicDevice->attachSource(this, vertexSource, ShaderType::VERTEX);
        graphicDevice->attachSource(this, fragmentSource, ShaderType::FRAGMENT);
        
        graphicDevice->bindAttribLocation(this, POSITION_LOCATION, "a_position");
        graphicDevice->bindAttribLocation(this, TEX_COORD_LOCATION, "a_uv");
        graphicDevice->bindAttribLocation(this, NORMAL_LOCATION, "a_normal");
        graphicDevice->bindAttribLocation(this, COLOR_LOCATION, "a_color");
        graphicDevice->bindAttribLocation(this, TANGENT_LOCATION, "a_tangent");
        graphicDevice->bindAttribLocation(this, BONE_ID_LOCATION, "a_boneIDs");
        graphicDevice->bindAttribLocation(this, BONE_WEIGHT_LOCATION, "a_boneWeights");
        graphicDevice->bindAttribLocation(this, MATERIAL_LOCATION, "a_material");
        
        graphicDevice->linkShader(this);
        
        _engineUniformPositions[SHADER_UNIFORM_MVP_MATRIX ]= getUniformLocation("u_sge_mvpMatrix");
        _engineUniformPositions[SHADER_UNIFORM_NORMAL_MATRIX]= getUniformLocation("u_sge_normalMatrix");
        _engineUniformPositions[SHADER_UNIFORM_MODEL_MATRIX ]= getUniformLocation("u_sge_modelMatrix");
        _engineUniformPositions[SHADER_UNIFORM_VIEW_MATRIX ]= getUniformLocation("u_sge_viewMatrix");
        _engineUniformPositions[SHADER_UNIFORM_PROJECTION_MATRIX ]= getUniformLocation("u_sge_projectionMatrix");
        _engineUniformPositions[SHADER_UNIFORM_DIFFUSE_TEX]= getUniformLocation("u_sge_mainTex");
        _engineUniformPositions[SHADER_UNIFORM_NORMAL_TEX]= getUniformLocation("u_sge_normalTex");
        _engineUniformPositions[SHADER_UNIFORM_MASK_TEX]= getUniformLocation("u_sge_maskTex");
        
        _engineUniformPositions[SHADER_UNIFORM_MAT_TEX]= getUniformLocation("u_sge_matTex");
        _engineUniformPositions[SHADER_UNIFORM_CAMWORLDPOS]= getUniformLocation("u_sge_camWorldPos");
        _engineUniformPositions[SHADER_UNIFORM_GLOBAL_TIME]= getUniformLocation("u_sge_time");
        _engineUniformPositions[SHADER_UNIFORM_MATERIAL]= getUniformLocation("u_sge_material");
        _engineUniformPositions[SHADER_UNIFORM_INVERSEPROJECTION]= getUniformLocation("u_sge_inverseProjectionMatrix");
        _engineUniformPositions[SHADER_UNIFORM_PROJECTION_VIEW_MATRIX ]= getUniformLocation("u_sge_projectionViewMatrix");

    
    
    }
    
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource){
        
        init();
        recompile(vertexSource, fragmentSource);
        
        checkRenderError();

    }
 
    Shader::~Shader(){
        
        GraphicDevice* graphicDevice= Director::getInstance()->getGraphicDevice();
        graphicDevice->releaseShader(this);
        
    }
    
    void Shader::updateDirtyShaderStates(){
    
        std::set<ShaderState*>::iterator it;
        
        for (it= _dirtyShaderStates.begin(); it!=_dirtyShaderStates.end(); ++it) {
            
            (*it)->uploadToShader(this);
            
        }
        
        _dirtyShaderStates.clear();
        
    }

    void Shader::bind(){
        
        ShaderManager::getInstance()->bindShader(this);
        
    }

    void Shader::setUniform1i(const int& value1, SInt location ){
  
        bind();
        glUniform1i(location, value1);
        checkRenderError();

    }

    void Shader::setUniform1f(const float& value1, SInt location ){

        bind();
        glUniform1f(location, value1);
        checkRenderError();

    }

    void Shader::setUniform2f(const float& value1, const float& value2, SInt location ){

        bind();
        glUniform2f(location, value1, value2);
        checkRenderError();

    }

    void Shader::setUniform3f(const float& value1, const float& value2, const float& value3, SInt location ){

        bind();
        glUniform3f(location, value1,value2,value3);
        checkRenderError();

    }
    
    void Shader::setUniform3f( const Vec3& vec, SInt location  ){
    
        bind();
        glUniform3f(location, vec.x,vec.y,vec.z);
        checkRenderError();

    }

    
    void Shader::setUniform4f(const Vec4& value, SInt location ){
    
        bind();
        glUniform4f(location, value.x,value.y,value.z,value.w);
        checkRenderError();

    }

    void Shader::setUniform4m(float* value, const bool& transpose, SInt location ){

        bind();

#ifdef MOBILE_TARGET
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
#else
        glUniformMatrix4fv(location, 1, transpose, value);
#endif

        checkRenderError();

    }

    void Shader::setUniform3m(float* value, const bool& transpose, SInt location ){
        
        bind();
        
#ifdef MOBILE_TARGET
        glUniformMatrix3fv(location, 1, GL_FALSE, value);
#else
        glUniformMatrix3fv(location, 1, transpose, value);
#endif
        
        checkRenderError();

    }
    
    void Shader::setUniform3fv(float* value,const int& size, SInt location ){

        bind();
        glUniform3fv(location, size, value);
        checkRenderError();

    }
    
    void Shader::setUniform4mv( float* value, int count, const bool&  transpose, SInt location ){

        bind();
        
#ifdef MOBILE_TARGET
        glUniformMatrix4fv(location, count, GL_FALSE, value);
#else
        glUniformMatrix4fv(location, count, transpose, value);
#endif
        
        checkRenderError();

    }

    void Shader::setTexture(Texture* texture, const int& position, SInt location ){
    
        bind();
        Director::getInstance()->getRenderer()->uploadTexture(texture, position);
        glUniform1i(location, (GLint)position);
        checkRenderError();

    }
    
    SInt Shader::getUniformLocation(const std::string& name){
        
        return Director::getInstance()->getGraphicDevice()->getUniformLocation(this, name);
    
    }
    
    const SInt& Shader::getID(){
    
        return _shaderID;
    
    }
    
    void Shader::printSource(){
    
        std::cout<< "------------------------------"<< std::endl;
        std::cout<< _nameID << std::endl;
        std::cout << std::endl;
        Shader::printShaderSourceWithLineNumbers(_vertexSource);
        std::cout << std::endl;
        Shader::printShaderSourceWithLineNumbers(_fragSource);
        std::cout << std::endl;
    
    }
    
    void Shader::printShaderSourceWithLineNumbers(const std::string& source){
    
        std::istringstream f(source);
        std::string line;
        int lineNumber=1;
        
        while (std::getline(f, line)) {
        
            std::cout << lineNumber<< ": " << line << std::endl;
            lineNumber++;
        
        }
        
    }

}
