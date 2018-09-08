/* 
 * File:   ResourcesFileParser.h
 * Author: serserar
 *
 * Created on April 21, 2014, 7:17 PM
 */

#ifndef RESOURCESFILEPARSER_H
#define	RESOURCESFILEPARSER_H
#include <string>
#include "../../util/xml/XMLParserUtil.h"
#include "../../util/xml/XMLEventHandler.h"
#include "ResourceDef.h"

class ResourcesFileParser : public XMLEventHandler {
public:
    ResourcesFileParser();
    virtual ~ResourcesFileParser();
    virtual void startElement(void * user_data, const xmlChar *name,
            const xmlChar **attrs);
    virtual void characters(void * user_data, const xmlChar * ch, int len);
    virtual void endElement(void * user_data, const xmlChar * name);
    ResourceDef* getParsedResourceFile(char* resourceFilePath);
private:
    static const std::string GAMERESOURCES;
    static const std::string VERSION_ATTR;
    static const std::string CONFIG;
    static const std::string AIPATH;
    static const std::string FONTPATH;
    static const std::string LANGUAGEPATH;
    static const std::string LEVELPATH;
    static const std::string MODELPATH;
    static const std::string MUSICPATH;
    static const std::string SOUNDPATH;
    static const std::string TEXTUREPATH;
    static const std::string UIPATH;
    static const std::string AIFILES;
    static const std::string AIFILE;
    static const std::string FONTS;
    static const std::string FONTFILE;
    static const std::string LANGUAGES;
    static const std::string LANGUAGEFILE;
    static const std::string LEVELS;
    static const std::string LEVELFILE;
    static const std::string MODELS;
    static const std::string MODELFILE;
    static const std::string MUSICS;
    static const std::string MUSICFILE;
    static const std::string SOUNDS;
    static const std::string SOUNDFILE;
    static const std::string TEXTURES;
    static const std::string TEXTUREFILE;
    static const std::string UIFILES;
    static const std::string UIFILE;
    static const std::string GAMEIDENTIFIER;
    static const std::string TYPE;
    static const std::string FORMAT;
    static const std::string NAME;
    static const std::string DESCRIPTION;
    static const std::string CACHE;
    static const std::string COMPRESSED;
    static const std::string INICIALIZATIONPATH;
    ResourceDef* resourceDef;
    bool isGameResources;
    bool isConfig;
    bool isAiPath;
    bool isFontPath;
    bool isLanguagePath;
    bool isLevelPath;
    bool isModelPath;
    bool isMusicPath;
    bool isSoundPath;
    bool isTexturePath;
    bool isUiPath;
    bool isAiFiles;
    bool isAiFile;
    bool isFonts;
    bool isFontFile;
    bool isLanguages;
    bool isLanguageFile;
    bool isLevels;
    bool isLevelFile;
    bool isModels;
    bool isModelFile;
    bool isMusics;
    bool isMusicFile;
    bool isSounds;
    bool isSoundFile;
    bool isTextures;
    bool isTextureFile;
    bool isUiFiles;
    bool isUiFile;
    bool isGameIdentifier;
    bool isType;
    bool isFormat;
    bool isName;
    bool isDescription;
    bool isCache;
    bool isCompressed;
    bool isInicializationPath;

};

#endif	/* RESOURCESFILEPARSER_H */

