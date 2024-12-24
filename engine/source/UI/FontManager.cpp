

#include "FontManager.h"
#include "Director.h"

namespace sge {
    
    FontManager* FontManager::_instance=NULL;

    FontManager* FontManager::getInstance(){

        if (!_instance) _instance= new FontManager();
        return _instance;

    }
    
    FontManager::FontManager(){
    
        int error = FT_Init_FreeType( &library );
        if ( error ){
            
            std::cout<< "Could not init FreeType" << std::endl;
            
        }


    }
    
    FontManager::~FontManager(){
    
    
    }
    
    FontAtlas* FontManager::getFontAtlasForFontAndSize(Font* font, float size){

        FontAtlas* fontAtlas=NULL;
        std::stringstream key; key<<font->file<<(int) size;
        
        if(_fontMap.find(key.str())!=_fontMap.end()){
            
            return _fontAtlasMap[key.str()];
            
        }else{
            
            fontAtlas= createNewFontAtlasFromFileAndSize(font, size);
            if(fontAtlas) _fontAtlasMap.insert(std::make_pair(key.str(), fontAtlas));
            
        }
        
        return fontAtlas;
    
    }
    
    Font* FontManager::getFont(const std::string& file){
    
        Font* font=NULL;
        
        if(_fontMap.find(file)!=_fontMap.end()){
        
            return _fontMap[file];
        
        }else{
        
            font= createNewFontFromFile(file);
            if(font) _fontMap.insert(std::make_pair(file, font));
        
        }
        
        return font;
    
    }
    
    FontAtlas* FontManager::createNewFontAtlasFromFileAndSize(Font* font, float size){
    
        FontAtlas* fontAtlas=FontAtlas::createFromFontAndSize(font, size);
        return fontAtlas;
    
    }
    
    Font* FontManager::createNewFontFromFile(const std::string& file){
        
        Font* font= new Font();
        font->file=file;
        font->name=Director::getInstance()->getFileUtils()->getFileNameForPath(file);
        
    
        int error = FT_New_Face( library, file.c_str() , 0 , &font->face );
        
        if ( error == FT_Err_Unknown_File_Format ){
           
            std::cout<< "Font Format is unsupported" << std::endl;
            delete font;
            font=NULL;
        
        }else if ( error ){
        
            std::cout<< "Could not open / read font" << std::endl;
            delete font;
            font=NULL;
        }
    
        return font;
    }

    
}