/* 
 * File:   ResourcesFileParser.cpp
 * Author: serserar
 * 
 * Created on April 21, 2014, 7:17 PM
 */

#include "ResourcesFileParser.h"
const std::string ResourcesFileParser::GAMERESOURCES = "GameResources";
const std::string ResourcesFileParser::VERSION_ATTR = "version";
const std::string ResourcesFileParser::CONFIG = "Config";
const std::string ResourcesFileParser::AIPATH = "AiPath";
const std::string ResourcesFileParser::FONTPATH = "FontPath";
const std::string ResourcesFileParser::LANGUAGEPATH = "LanguagesPath";
const std::string ResourcesFileParser::LEVELPATH = "LevelPath";
const std::string ResourcesFileParser::MODELPATH = "ModelPath";
const std::string ResourcesFileParser::MUSICPATH = "MusicPath";
const std::string ResourcesFileParser::SOUNDPATH = "SoundPath";
const std::string ResourcesFileParser::TEXTUREPATH = "TexturePath";
const std::string ResourcesFileParser::UIPATH = "UiPath";
const std::string ResourcesFileParser::AIFILES = "AiFiles";
const std::string ResourcesFileParser::AIFILE = "AiFile";
const std::string ResourcesFileParser::FONTS = "Fonts";
const std::string ResourcesFileParser::FONTFILE = "FontFile";
const std::string ResourcesFileParser::LANGUAGES = "Languages";
const std::string ResourcesFileParser::LANGUAGEFILE = "LanguageFile";
const std::string ResourcesFileParser::LEVELS = "Levels";
const std::string ResourcesFileParser::LEVELFILE = "LevelFile";
const std::string ResourcesFileParser::MODELS = "Models";
const std::string ResourcesFileParser::MODELFILE = "ModelFile";
const std::string ResourcesFileParser::MUSICS = "Models";
const std::string ResourcesFileParser::MUSICFILE = "ModelFile";
const std::string ResourcesFileParser::SOUNDS = "Sounds";
const std::string ResourcesFileParser::SOUNDFILE = "SoundFile";
const std::string ResourcesFileParser::TEXTURES = "Textures";
const std::string ResourcesFileParser::TEXTUREFILE = "TextureFile";
const std::string ResourcesFileParser::UIFILES = "UiFiles";
const std::string ResourcesFileParser::UIFILE = "UiFile";
const std::string ResourcesFileParser::GAMEIDENTIFIER = "GameIdentifier";
const std::string ResourcesFileParser::TYPE = "Type";
const std::string ResourcesFileParser::FORMAT = "Format";
const std::string ResourcesFileParser::NAME = "Name";
const std::string ResourcesFileParser::DESCRIPTION = "Description";
const std::string ResourcesFileParser::CACHE = "Cache";
const std::string ResourcesFileParser::COMPRESSED = "Compressed";
const std::string ResourcesFileParser::INICIALIZATIONPATH = "InicializationFilePath";

ResourcesFileParser::ResourcesFileParser() {
    this->isGameResources = false;
    this->isConfig = false;
    this->isAiPath = false;
    this->isFontPath = false;
    this->isLanguagePath = false;
    this->isLevelPath = false;
    this->isModelPath = false;
    this->isMusicPath = false;
    this->isSoundPath = false;
    this->isTexturePath = false;
    this->isUiPath = false;
    this->isAiFiles = false;
    this->isAiFile = false;
    this->isFonts = false;
    this->isFontFile = false;
    this->isLanguages = false;
    this->isLanguageFile = false;
    this->isLevels = false;
    this->isLevelFile = false;
    this->isModels = false;
    this->isModelFile = false;
    this->isMusics = false;
    this->isMusicFile = false;
    this->isSounds = false;
    this->isSoundFile = false;
    this->isTextures = false;
    this->isTextureFile = false;
    this->isUiFiles = false;
    this->isUiFile = false;
    this->isGameIdentifier = false;
    this->isType = false;
    this->isFormat = false;
    this->isName = false;
    this->isDescription = false;
    this->isCache = false;
    this->isCompressed = false;
    this->isInicializationPath = false;
}

void ResourcesFileParser::startElement(void* user_data, const xmlChar* name,
        const xmlChar** attrs) {
    std::string nodeName = (char*) name;
    if (nodeName.compare(ResourcesFileParser::GAMERESOURCES) == 0) {
        isGameResources = true;
        resourceDef = new ResourceDef();
    } else if (nodeName.compare(ResourcesFileParser::CONFIG) == 0) {
        isConfig = true;
    } else if (nodeName.compare(ResourcesFileParser::AIPATH) == 0) {
        isAiPath = true;
    } else if (nodeName.compare(ResourcesFileParser::FONTPATH) == 0) {
        isFontPath = true;
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGEPATH) == 0) {
        isLanguagePath = true;
    } else if (nodeName.compare(ResourcesFileParser::LEVELPATH) == 0) {
        isLevelPath = true;
    } else if (nodeName.compare(ResourcesFileParser::MODELPATH) == 0) {
        isModelPath = true;
    } else if (nodeName.compare(ResourcesFileParser::MUSICPATH) == 0) {
        isMusicPath = true;
    } else if (nodeName.compare(ResourcesFileParser::SOUNDPATH) == 0) {
        isSoundPath = true;
    } else if (nodeName.compare(ResourcesFileParser::TEXTUREPATH) == 0) {
        isTexturePath = true;
    } else if (nodeName.compare(ResourcesFileParser::UIPATH) == 0) {
        isUiPath = true;
    } else if (nodeName.compare(ResourcesFileParser::AIFILES) == 0) {
        isAiFiles = true;
    } else if (nodeName.compare(ResourcesFileParser::AIFILE) == 0) {
        isAiFile = true;
        resource* aiResource = new resource;
        this->resourceDef->addAiResource(aiResource);
    } else if (nodeName.compare(ResourcesFileParser::FONTS) == 0) {
        isFonts = true;
    } else if (nodeName.compare(ResourcesFileParser::FONTFILE) == 0) {
        isFontFile = true;
        resource* fontResource = new resource;
        this->resourceDef->addFontResource(fontResource);
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGES) == 0) {
        isLanguages = true;
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGEFILE) == 0) {
        isLanguageFile = true;
        resource* langResource = new resource;
        this->resourceDef->addLanguageResource(langResource);
    } else if (nodeName.compare(ResourcesFileParser::LEVELS) == 0) {
        isLevels = true;
    } else if (nodeName.compare(ResourcesFileParser::LEVELFILE) == 0) {
        isLevelFile = true;
        resource* levelResource = new resource;
        this->resourceDef->addLevelResource(levelResource);
    } else if (nodeName.compare(ResourcesFileParser::MODELS) == 0) {
        isModels = true;
    } else if (nodeName.compare(ResourcesFileParser::MODELFILE) == 0) {
        isModelFile = true;
        resource* modelResource = new resource;
        this->resourceDef->addModelResource(modelResource);
    } else if (nodeName.compare(ResourcesFileParser::MUSICS) == 0) {
        isMusics = true;
    } else if (nodeName.compare(ResourcesFileParser::MUSICFILE) == 0) {
        isMusicFile = true;
        resource* musicResource = new resource;
        this->resourceDef->addMusicResource(musicResource);
    } else if (nodeName.compare(ResourcesFileParser::SOUNDS) == 0) {
        isSounds = true;
    } else if (nodeName.compare(ResourcesFileParser::SOUNDFILE) == 0) {
        isSoundFile = true;
        resource* soundResource = new resource;
        this->resourceDef->addSoundResource(soundResource);
    } else if (nodeName.compare(ResourcesFileParser::TEXTURES) == 0) {
        isTextures = true;
    } else if (nodeName.compare(ResourcesFileParser::TEXTUREFILE) == 0) {
        isTextureFile = true;
        resource* textureResource = new resource;
        this->resourceDef->addTextureResource(textureResource);
    } else if (nodeName.compare(ResourcesFileParser::UIFILES) == 0) {
        isUiFiles = true;
    } else if (nodeName.compare(ResourcesFileParser::UIFILE) == 0) {
        isUiFile = true;
        resource* uiResource = new resource;
        this->resourceDef->addUiResource(uiResource);
    } else if (nodeName.compare(ResourcesFileParser::GAMEIDENTIFIER) == 0) {
        isGameIdentifier = true;
    } else if (nodeName.compare(ResourcesFileParser::TYPE) == 0) {
        isType = true;
    } else if (nodeName.compare(ResourcesFileParser::FORMAT) == 0) {
        isFormat = true;
    } else if (nodeName.compare(ResourcesFileParser::NAME) == 0) {
        isName = true;
    } else if (nodeName.compare(ResourcesFileParser::DESCRIPTION) == 0) {
        isDescription = true;
    } else if (nodeName.compare(ResourcesFileParser::CACHE) == 0) {
        isCache = true;
    } else if (nodeName.compare(ResourcesFileParser::COMPRESSED) == 0) {
        isCompressed = true;
    } else if (nodeName.compare(ResourcesFileParser::INICIALIZATIONPATH) == 0) {
        isInicializationPath = true;
    }
}

void ResourcesFileParser::characters(void* user_data, const xmlChar* ch, int len) {
    std::string nodeChars;
    nodeChars.append((char*) ch, len);
    if (isAiFiles) {
        if (isAiFile) {
            if (isGameIdentifier) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getAiResource(
                        this->resourceDef->getAiResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isFonts) {
        if (isFontFile) {
            if (isGameIdentifier) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getFontResource(
                        this->resourceDef->getFontResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isLanguages) {
        if (isLanguageFile) {
            if (isGameIdentifier) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getLanguageResource(
                        this->resourceDef->getLanguageResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isLevels) {
        if (isLevelFile) {
            if (isGameIdentifier) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getLevelResource(
                        this->resourceDef->getLevelResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isModels) {
        if (isModelFile) {
            if (isGameIdentifier) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getModelResource(
                        this->resourceDef->getModelResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isMusics) {
        if (isMusicFile) {
            if (isGameIdentifier) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getMusicResource(
                        this->resourceDef->getMusicResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isSounds) {
        if (isSoundFile) {
            if (isGameIdentifier) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getSoundResource(
                        this->resourceDef->getSoundResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isTextures) {
        if (isTextureFile) {
            if (isGameIdentifier) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getTextureResource(
                        this->resourceDef->getTextureResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isUiFiles) {
        if (isUiFile) {
            if (isGameIdentifier) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->gameIdentifier = nodeChars;
            } else if (isType) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->type = nodeChars;
            } else if (isFormat) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->format = nodeChars;
            } else if (isName) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->name = nodeChars;
            } else if (isDescription) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->description = nodeChars;
            } else if (isCache) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->cache = atoi(nodeChars.c_str());
            } else if (isCompressed) {
                this->resourceDef->getUiResource(
                        this->resourceDef->getUiResourcesSize() - 1)->compressed = atoi(nodeChars.c_str());
            }
        }
    } else if (isInicializationPath) {
        this->resourceDef->setInicializationPath(nodeChars);
    }
}

void ResourcesFileParser::endElement(void* user_data, const xmlChar* name) {
    std::string nodeName = (char*) name;
    if (nodeName.compare(ResourcesFileParser::GAMERESOURCES) == 0) {
        isGameResources = false;
    } else if (nodeName.compare(ResourcesFileParser::CONFIG) == 0) {
        isConfig = false;
    } else if (nodeName.compare(ResourcesFileParser::AIPATH) == 0) {
        isAiPath = false;
    } else if (nodeName.compare(ResourcesFileParser::FONTPATH) == 0) {
        isFontPath = false;
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGEPATH) == 0) {
        isLanguagePath = false;
    } else if (nodeName.compare(ResourcesFileParser::LEVELPATH) == 0) {
        isLevelPath = false;
    } else if (nodeName.compare(ResourcesFileParser::MODELPATH) == 0) {
        isModelPath = false;
    } else if (nodeName.compare(ResourcesFileParser::MUSICPATH) == 0) {
        isMusicPath = false;
    } else if (nodeName.compare(ResourcesFileParser::SOUNDPATH) == 0) {
        isSoundPath = false;
    } else if (nodeName.compare(ResourcesFileParser::TEXTUREPATH) == 0) {
        isTexturePath = false;
    } else if (nodeName.compare(ResourcesFileParser::UIPATH) == 0) {
        isUiPath = false;
    } else if (nodeName.compare(ResourcesFileParser::AIFILES) == 0) {
        isAiFiles = false;
    } else if (nodeName.compare(ResourcesFileParser::AIFILE) == 0) {
        isAiFile = false;
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGES) == 0) {
        isLanguages = false;
    } else if (nodeName.compare(ResourcesFileParser::LANGUAGEFILE) == 0) {
        isLanguageFile = false;
    } else if (nodeName.compare(ResourcesFileParser::LEVELS) == 0) {
        isLevels = false;
    } else if (nodeName.compare(ResourcesFileParser::LEVELFILE) == 0) {
        isLevelFile = false;
    } else if (nodeName.compare(ResourcesFileParser::MODELS) == 0) {
        isModels = false;
    } else if (nodeName.compare(ResourcesFileParser::MODELFILE) == 0) {
        isModelFile = false;
    } else if (nodeName.compare(ResourcesFileParser::MUSICS) == 0) {
        isMusics = false;
    } else if (nodeName.compare(ResourcesFileParser::MUSICFILE) == 0) {
        isMusicFile = false;
    } else if (nodeName.compare(ResourcesFileParser::SOUNDS) == 0) {
        isSounds = false;
    } else if (nodeName.compare(ResourcesFileParser::SOUNDFILE) == 0) {
        isSoundFile = false;
    } else if (nodeName.compare(ResourcesFileParser::TEXTURES) == 0) {
        isTextures = false;
    } else if (nodeName.compare(ResourcesFileParser::TEXTUREFILE) == 0) {
        isTextureFile = false;
    } else if (nodeName.compare(ResourcesFileParser::UIFILES) == 0) {
        isUiFiles = false;
    } else if (nodeName.compare(ResourcesFileParser::UIFILE) == 0) {
        isUiFile = false;
    } else if (nodeName.compare(ResourcesFileParser::GAMEIDENTIFIER) == 0) {
        isGameIdentifier = false;
    } else if (nodeName.compare(ResourcesFileParser::TYPE) == 0) {
        isType = false;
    } else if (nodeName.compare(ResourcesFileParser::FORMAT) == 0) {
        isFormat = false;
    } else if (nodeName.compare(ResourcesFileParser::NAME) == 0) {
        isName = false;
    } else if (nodeName.compare(ResourcesFileParser::DESCRIPTION) == 0) {
        isDescription = false;
    } else if (nodeName.compare(ResourcesFileParser::CACHE) == 0) {
        isCache = false;
    } else if (nodeName.compare(ResourcesFileParser::COMPRESSED) == 0) {
        isCompressed = false;
    } else if (nodeName.compare(ResourcesFileParser::INICIALIZATIONPATH) == 0) {
        isInicializationPath = false;
    }
}

ResourcesFileParser::~ResourcesFileParser() {
}

ResourceDef* ResourcesFileParser::getParsedResourceFile(char* resourceFilePath) {
    XmlParserUtil parser;
    parser.parseXML(resourceFilePath, *this);
    return this->resourceDef;
}

