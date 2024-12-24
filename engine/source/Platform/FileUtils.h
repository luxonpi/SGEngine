

#ifndef SGENGINE_FILEUTILS_H
#define SGENGINE_FILEUTILS_H

#include "SBase.h"

namespace sge {
    
class Director;
class FileUtils{

public:
    
    class FileWatcher{
    
    public:
        
        struct Event{
        
            FileWatcher* watcher;
            std::string changedPath;
            std::string changeType;
        
        };
        
    public:
        
        std::string targetPath;
        std::function<void(FileWatcher::Event*)> callback;
    
    };

    
    friend Director;
    
private:

    FileUtils();
    ~FileUtils();
    
    std::set<FileWatcher*> _watcher;
    
    void updateWatcher();
    
public:
    
    bool doesPathContainPath(const std::string& basePath, const std::string& path);
    
    void pathChanged(const std::string& path);
    
    void addFileWatcher(FileWatcher* filewatcher);
    void removeFileWatcher(FileWatcher* filewatcher);
    
    std::string getRessourcePath(const std::string& file);
    std::string getDocumentsPath(const std::string& file);
    std::string getLibraryPath(const std::string& file);
    
    std::string getStringFromFullPath(const std::string& path);
    
    std::string getFolderPathForPath(const std::string& path);
    std::string getFirstFolderForPath(const std::string& path);

    std::string getFileNameForPath(const std::string& path);
    
    bool doesFileExistForFullPath(const std::string& path);

    
};
    
}

#endif
