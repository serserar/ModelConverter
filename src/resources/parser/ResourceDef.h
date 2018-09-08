/* 
 * File:   ResourceDef.h
 * Author: serserar
 *
 * Created on April 21, 2014, 7:22 PM
 */

#ifndef RESOURCEDEF_H
#define	RESOURCEDEF_H
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

struct resource {
    std::string gameIdentifier;
    std::string type;
    std::string format;
    std::string name;
    std::string description;
    bool cache;
    bool compressed;
};

struct delete_resource_ptr {

    template <class T>
    void operator()(T* p) {
        delete p;
    }
};
;

class ResourceDef {
public:
    ResourceDef();
    virtual ~ResourceDef();
    void addAiResource(resource* aiResource);
    resource* getAiResource(unsigned int index);
    unsigned int getAiResourcesSize();
    void addFontResource(resource* fontResource);
    resource* getFontResource(unsigned int index);
    unsigned int getFontResourcesSize();
    void addLanguageResource(resource* languageResource);
    resource* getLanguageResource(unsigned int index);
    unsigned int getLanguageResourcesSize();
    void addLevelResource(resource* levelResource);
    resource* getLevelResource(unsigned int index);
    unsigned int getLevelResourcesSize();
    void addModelResource(resource* modelResource);
    resource* getModelResource(unsigned int index);
    unsigned int getModelResourcesSize();
    void addMusicResource(resource* musicResource);
    resource* getMusicResource(unsigned int index);
    unsigned int getMusicResourcesSize();
    void addSoundResource(resource* soundResource);
    resource* getSoundResource(unsigned int index);
    unsigned int getSoundResourcesSize();
    void addTextureResource(resource* textureResource);
    resource* getTextureResource(unsigned int index);
    unsigned int getTextureResourcesSize();
    void addUiResource(resource* uiResource);
    resource* getUiResource(unsigned int index);
    unsigned int getUiResourcesSize();
    void setInicializationPath(std::string inicializationPath);
    std::string getInicializationPath();
    
private:
    std::string version;
    std::string inicializationFilePath;
    std::vector<resource*> aiResources;
    std::vector<resource*> fontResources;
    std::vector<resource*> languageResources;
    std::vector<resource*> levelResources;
    std::vector<resource*> modelResources;
    std::vector<resource*> musicResources;
    std::vector<resource*> soundResources;
    std::vector<resource*> textureResources;
    std::vector<resource*> uiResources;
};

#endif	/* RESOURCEDEF_H */

