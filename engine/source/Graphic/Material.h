

#ifndef SGENGINE_MATERIAL_H
#define SGENGINE_MATERIAL_H

#include <stdio.h>
#include <map>
#include <set>

#include "SBase.h"
#include "Color.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureCubeMap.h"

namespace sge {

    class RenderObject;
    class Material: public ShaderState::Observer{
        
        friend RenderObject;
        
    private:
        
        static Texture* getTextureForStringValue(const std::string& value, const std::string& folder);

    protected:
        
        static std::unordered_map<std::string, Material*> _chache;
        
        std::vector<Texture*>   _textures;
        std::set<std::string>   _defines;
        std::set<RenderObject*> _holders;

        ShaderModule* _shaderModule;
        ShaderState* _shaderState;
        Shader* _activeShader;

        SUint _cullFaceSide;
        BlendFunc _blendFunc;
        SUint _depthFunction;
        bool _hasAlpha;

        void hasChanged();
        void shaderStateChanged(ShaderState* state);

    public:
        
        bool _isDirty;
        
        Material();
        virtual ~Material();
        Material* getCopy();
        static Material* get(const std::string& file);

        void addDefine(const std::string& define);
        void removeDefine(const std::string& define);
        void replaceDefine(const std::string& defineToBeReplaced, const std::string& define);
        std::vector<std::string> getDefines();
        
        virtual void setAlpha(bool hasAlpha);
        bool hasAlpha();
        
        BlendFunc& getBlendFunc();
        void setBlendFunc(const BlendFunc& blendFunc);
        
        void setCullFaceSide(const SUint& cullFaceSide);
        const SUint& getCullFaceSide();
        
        void setDepthFunction(const SUint& depthFunction);
        const SUint& getDepthFunction();
        
        void setShaderModule(ShaderModule* shaderModule);
        ShaderModule* getShaderModule();
        ShaderState* getShaderState();
        Shader* getActiveShader();
        Shader* getActiveShader(const std::string& define);
        
    };
    
}

#endif
