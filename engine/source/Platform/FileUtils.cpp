

#include "FileUtils.h"
#include "SPath.h"

namespace sge {

FileUtils::FileUtils(){


}

FileUtils::~FileUtils(){}
    
void FileUtils::updateWatcher(){

    std::vector<std::string> pathToWatch;
    
    std::set<FileWatcher*>::iterator it;
    for (it=_watcher.begin(); it!=_watcher.end(); ++it) {
        
        pathToWatch.push_back((*it)->targetPath);
        
    }
    
    SPath::setPathsToWatch(pathToWatch);
    
}

void FileUtils::addFileWatcher(FileUtils::FileWatcher* filewatcher){
    
    if (_watcher.find(filewatcher)==_watcher.end()) {
        
        _watcher.insert(filewatcher);
        updateWatcher();
        
    }
    
}

void FileUtils::removeFileWatcher(FileUtils::FileWatcher* filewatcher){

    _watcher.erase(filewatcher);
    updateWatcher();

}
    
void FileUtils::pathChanged(const std::string& path){
    
    std::set<FileWatcher*>::iterator it;
    for (it=_watcher.begin(); it!=_watcher.end(); ++it) {
        
        if (doesPathContainPath((*it)->targetPath, path)) {
            
            FileUtils::FileWatcher::Event event;
            event.watcher=(*it);
            event.changedPath=path;
            
            (*it)->callback(&event);
            
            
        }
        
    }
    
}
    
bool FileUtils::doesPathContainPath(const std::string& basePath, const std::string& path){
    
    if(basePath.length()>path.length()) return false;
    
    std::string subString= path.substr(0, basePath.length());
    if(subString==basePath) return true;

    return false;

}
    
std::string FileUtils::getFirstFolderForPath(const std::string& path){
    
    std::string text=path;
    
    int posP= (int)text.find_first_of("/");
    if(posP!=std::string::npos && posP<text.length()-1){
        
        text.erase(posP+1, text.length());
        
    }
    
    return text;
    
}
    
std::string FileUtils::getFolderPathForPath(const std::string& path){

    std::string text=path;
    
    int posP= (int)text.find_last_of("/");
    if(posP!=std::string::npos && posP<text.length()-1){
    
        text.erase(posP+1, text.length());
    
    }

    return text;

}

std::string FileUtils::getFileNameForPath(const std::string& path){
    
    std::string text=path;
    
    int posP= (int)text.find_last_of("/");
    if(posP!=std::string::npos && posP<text.length()-1){
        
        return text.substr(posP+1, text.length());
    
    }
    
    return "";
    
}


std::string FileUtils::getRessourcePath(const std::string& path){

    return SPath::getRessourcePath().append("/").append(path);

}

std::string FileUtils::getDocumentsPath(const std::string& path){

    return SPath::getDocumentsPath().append("/").append(path);

}

std::string FileUtils::getLibraryPath(const std::string& path){

    return SPath::getLibraryPath().append("/").append(path);

}

bool FileUtils::doesFileExistForFullPath(const std::string& path){

    std::ifstream file;
    file.open((path).c_str());
    
    std::string output;
    std::string line;
    
    if(file.is_open()){
        return true;
    
    }
    
    return false;
}

std::string FileUtils::getStringFromFullPath(const std::string& path){

    std::ifstream file;
    file.open((path).c_str());
    
    std::string output;
    std::string line;
    
    if(file.is_open()){
        
        while(file.good()){
            
            getline(file, line);
            output.append(line + "\n");
        }
    
    }else{
        
        std::cerr << "Unable to load string from file: " << path << std::endl;
    }
    
    return output;

}
    
}

