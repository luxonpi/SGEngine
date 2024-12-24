

#include "Material.h"
#include "ShaderModule.h"
#include "RenderObject.h"
#include "IniParser.h"
#include "Director.h"

namespace sge {

    std::unordered_map<std::string, Material*> Material::_chache;

    
    Material::~Material(){}
    Material::Material(){

        _depthFunction=DepthFunc::LESS;
        _cullFaceSide=CullFace::BACK;
        _blendFunc= BlendFunc::NORMAL;
        
        _shaderState= new ShaderState();
        _shaderState->addObserver(this);
        _isDirty=false;
        
        _activeShader=NULL;

    }
    
    void Material::shaderStateChanged(ShaderState* state){

        _isDirty=true;
        
    }

    Material* Material::getCopy(){
        
        Material* mat= new Material();
        
        mat->_defines=_defines;
        mat->_shaderModule=_shaderModule;
        mat->_cullFaceSide=_cullFaceSide;
        mat->_depthFunction=_depthFunction;
        mat->_hasAlpha=_hasAlpha;
        mat->_shaderState->copy(_shaderState);
        mat->hasChanged();
        
        return mat;
        
    }
    
    Material* Material::get(const std::string& file){
        
        if(_chache.find(file)!=_chache.end()){
        
            return _chache[file];
        
        }
        
        Material* material= new Material();
        
        IniReader iniParser;
        std::string fullPath=Director::getInstance()->getFileUtils()->getRessourcePath(file);
        iniParser.parseFile(fullPath);
        
        IniReader::Section* matSection= iniParser.getSection("material");
        IniReader::Section* textSection= iniParser.getSection("textures");
        IniReader::Section* parameterSection= iniParser.getSection("parameter");

        std::string defines= matSection->getValue("defines");
        std::string shader= matSection->getValue("shader");
        
        material->setShaderModule(ShaderModule::get(shader));
    
        // DEFINES ///
        std::vector<std::string> array= SString::getStringArrayFromCommaSeperatedString(defines);
    
        for (int i=0; i<array.size(); i++) {
            
            SString::replaceAll(array[i], " ", "");
            material->addDefine(array[i]);
            
        }
        
        std::string folder= Director::getInstance()->getFileUtils()->getFolderPathForPath(file);
        
        // Textures Parameter ////
        int textureCount=0;
        if(textSection){
            
            std::unordered_map<std::string, std::string>::iterator it;
            
            for ( it = textSection->entries.begin(); it != textSection->entries.end(); it++){
                
                Texture* texture=getTextureForStringValue(it->second, folder);
                
                if(texture){
                
                    material->getShaderState()->setUniformTexture(it->first, texture, textureCount);
                    textureCount++;
                }

            
            }
        
            
        }
       
        // parameter
        if(parameterSection){
            
            std::unordered_map<std::string, std::string>::iterator it;
            
            for ( it = parameterSection->entries.begin(); it != parameterSection->entries.end(); it++){
                
                if(SString::containsString(it->second, "f")){
        
                    material->getShaderState()->setUniform1f(it->first, parameterSection->getValueAsFloat(it->first));
                
                }else if(SString::containsString(it->second, "vec3")){
                    
                    material->getShaderState()->setUniform3f(it->first, parameterSection->getValueAsVec3(it->first));
                    
                }else if(SString::containsString(it->second, "vec4")){
                    
                    material->getShaderState()->setUniform4f(it->first, parameterSection->getValueAsVec4(it->first));
                    
                }else if(SString::containsString(it->second, "vec2")){
                    
                    material->getShaderState()->setUniform2f(it->first, parameterSection->getValueAsVec2(it->first));
                    
                }else if(SString::containsString(it->second, "i")){
                    
                    material->getShaderState()->setUniform1i(it->first, parameterSection->getValueAsInt(it->first));
                    
                }
                
                
            }
            
            
        }

        
        
        material->hasChanged();
        _chache.insert(std::make_pair(file, material));
        
        return material;
        
    }

    
    
    ShaderState* Material::getShaderState(){
        
        return _shaderState;
        
    }
    
    Texture* Material::getTextureForStringValue(const std::string& value, const std::string& folder){
    
        std::string text=value;
        std::string params;
        
        int bracketPos= (int) text.find("(");
        if(bracketPos!=std::string::npos){
            
            params= text.substr(bracketPos, text.length());
            text.erase(bracketPos,text.length());
            
        }
        
        SString::replaceAll(text, " ", "");
        
        if(text.length()==0) return NULL;
        
        Texture* texture= Texture::get(folder+text);
        if(texture){
            
            if(SString::containsString(params, "MIPMAP")){
                
                texture->generateMipMap();
                
            }
            
            return texture;
            
        }

        return NULL;
    }
    
    void Material::hasChanged(){
    
        _isDirty=true;
//        for (std::set<RenderObject*>::iterator i = _holders.begin(); i != _holders.end(); i++) {
//            
//            RenderObject* object=*i;
//            object->updateShader();
//            
//        }

        
        if(_shaderModule){
            
            Shader* newShader=_shaderModule->getShaderForDefines(getDefines());
            
            if(newShader!=_activeShader){
               
                _activeShader=newShader;
                _shaderState->setMainShader(newShader);

            }
        
        }
        
    }
    
    Shader* Material::getActiveShader(){
    
        return _activeShader;
    
    }
    
    Shader* Material::getActiveShader(const std::string& define){
        
        std::vector<std::string> defines;
        defines.insert(defines.end(), _defines.begin(), _defines.end());
        defines.push_back(define);
            
        return getShaderModule()->getShaderForDefines(defines);
        
    }
    
    std::vector<std::string> Material::getDefines(){
    
        
        std::vector<std::string> array;
        
        for (std::set<std::string>::iterator i = _defines.begin(); i != _defines.end(); i++) {
            
            array.push_back(*i);
            
        }
        
        return array;
    
    }
    

    void Material::setShaderModule(ShaderModule* shaderModule){
    
        _shaderModule= shaderModule;
        
        hasChanged();

    
    }
    
    ShaderModule* Material::getShaderModule(){
    
        return _shaderModule;
    
    }
    


    void Material::setBlendFunc(const BlendFunc& blendFunc){
        
        _blendFunc=blendFunc;
        
    }
    
    BlendFunc& Material::getBlendFunc(){
        
        return _blendFunc;
        
    }
    
    bool Material::hasAlpha(){
        
        return _hasAlpha;
    }
    
    void Material::setAlpha(bool hasAlpha){
        
        _hasAlpha=hasAlpha;
        
    }
    
    void Material::setCullFaceSide(const SUint& cullFaceSide){
        
        _cullFaceSide=cullFaceSide;
        
    }
    
    void Material::setDepthFunction(const SUint& depthFunction){
        
        _depthFunction=depthFunction;
        
    }
    
    const SUint& Material::getCullFaceSide(){
        
        return _cullFaceSide;
        
    }
    
    const SUint& Material::getDepthFunction(){
        
        return _depthFunction;
        
    }
    
    
    void Material::addDefine(const std::string& define){
        
        _defines.insert(define);
        hasChanged();
        
    }
    
    void Material::removeDefine(const std::string& define){
        
        _defines.erase(define);
        hasChanged();
        
    }
    
    void Material::replaceDefine(const std::string& defineToBeReplaced, const std::string& define){
        
        _defines.erase(defineToBeReplaced);
        _defines.insert(define);
        hasChanged();
        
    }

   
    
}