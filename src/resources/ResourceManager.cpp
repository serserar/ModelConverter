/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#include "ResourceManager.h"

const char* ResourceManager::MEDIA_FOLDER = "media";
const char* ResourceManager::AI_FOLDER = "ai";
const char* ResourceManager::FONT_FOLDER = "fonts";
const char* ResourceManager::LEVEL_FOLDER = "level";
const char* ResourceManager::LANGUAGE_FOLDER = "languages";
const char* ResourceManager::MODEL_FOLDER = "model";
const char* ResourceManager::MUSIC_FOLDER = "music";
const char* ResourceManager::SOUND_FOLDER = "sound";
const char* ResourceManager::TEXTURE_FOLDER = "texture";
const char* ResourceManager::UI_FOLDER = "ui";
const char* ResourceManager::INICIALIZATION_FOLDER = "inicialization";
const char* ResourceManager::RESOURCES_FILE_NAME = "resources.xml";

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {

}

bool ResourceManager::initialize() {
    std::string base = getBasePath();
    initResourcePaths(base);
    std::string resourceConfigFile = mediaPath + RESOURCES_FILE_NAME;
    loadResourceConfigurationFile((char*) resourceConfigFile.c_str());
}

    bool ResourceManager::initialize(std::string& basePath) {
    initResourcePaths(basePath);
    std::string resourceConfigFile = mediaPath + RESOURCES_FILE_NAME;
    loadResourceConfigurationFile((char*) resourceConfigFile.c_str());
}

std::string ResourceManager::getBasePath() {

    char buff[1024];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof (buff) - 1);
    if (len != -1) {
        buff[len] = '\0';
        return std::string(buff);
    } else {
        /* handle error condition */
    }

}

std::string ResourceManager::getMediaPath() {
    return this->mediaPath;
}

void ResourceManager::setApplicationPath(std::string& appPath) {
    initResourcePaths(appPath);
}

std::string ResourceManager::getAiPath() {
    return this->aiPath;
}

std::string ResourceManager::getFontPath() {
    return this->fontPath;
}

std::string ResourceManager::getLanguagePath() {
    return this->languagePath;
}

std::string ResourceManager::getLevelPath() {
    return this->levelPath;
}

std::string ResourceManager::getModelPath() {
    return this->modelPath;
}

std::string ResourceManager::getMusicPath() {
    return this->musicPath;
}

std::string ResourceManager::getSoundPath() {
    return this->soundPath;
}

std::string ResourceManager::getTexturePath() {
    return this->texturePath;
}

std::string ResourceManager::getUiPath() {
    return this->uiPath;
}

void ResourceManager::initResourcePaths(std::string& basePath) {
    mediaPath = basePath.append("/").append(MEDIA_FOLDER).append("/");
    aiPath = mediaPath + AI_FOLDER + "/";
    fontPath = mediaPath + FONT_FOLDER + "/";
    languagePath = mediaPath + LANGUAGE_FOLDER + "/";
    levelPath = mediaPath + LEVEL_FOLDER + "/";
    modelPath = mediaPath + MODEL_FOLDER + "/";
    musicPath = mediaPath + MUSIC_FOLDER + "/";
    soundPath = mediaPath + SOUND_FOLDER + "/";
    texturePath = mediaPath + TEXTURE_FOLDER + "/";
    uiPath = mediaPath + UI_FOLDER + "/";
    inicializationFilePath = mediaPath + INICIALIZATION_FOLDER + "/";
}

ResourceFile* ResourceManager::getAi(std::string& aiId) {
    return aiResources.at(aiId);
}

ResourceFile* ResourceManager::getFont(std::string& fontId) {
    return fontResources.at(fontId);
}

ResourceFile* ResourceManager::getLanguage(std::string& languageId) {
    return languageResources.at(languageId);
}

ResourceFile* ResourceManager::getLevel(std::string& levelId) {
    return levelResources.at(levelId);
}

ResourceFile* ResourceManager::getModel(std::string& modelId) {
    return modelResources.at(modelId);
}

ResourceFile* ResourceManager::getMusic(std::string& musicId) {
    return musicResources.at(musicId);
}

ResourceFile* ResourceManager::getSound(std::string& soundId) {
    return soundResources.at(soundId);
}

ResourceFile* ResourceManager::getTexture(std::string& textureId) {
    return textureResources.at(textureId);
}

ResourceFile* ResourceManager::getUi(std::string& uiId) {
    return uiResources.at(uiId);
}

ResourceFile* ResourceManager::getResourceById(int resourceType, std::string& ResourceId) {
    ResourceFile* resourceFile = NULL;
    switch (resourceType) {
        case ResourceFile::AI:
            resourceFile = this->aiResources.at(ResourceId);
            break;
        case ResourceFile::FONT:
            resourceFile = this->fontResources.at(ResourceId);
            break;
        case ResourceFile::LANGUAGE:
            resourceFile = this->languageResources.at(ResourceId);
            break;
        case ResourceFile::LEVEL:
            resourceFile = this->levelResources.at(ResourceId);
            break;
        case ResourceFile::MODEL:
            resourceFile = this->modelResources.at(ResourceId);
            break;
        case ResourceFile::MUSIC:
            resourceFile = this->musicResources.at(ResourceId);
            break;
        case ResourceFile::SOUND:
            resourceFile = this->soundResources.at(ResourceId);
            break;
        case ResourceFile::TEXTURE:
            resourceFile = this->textureResources.at(ResourceId);
            break;
        case ResourceFile::UI:
            resourceFile = this->uiResources.at(ResourceId);
            break;
    };
    return resourceFile;
}

void ResourceManager::loadResourceConfigurationFile(char* resourceConfigFile) {
    if (resourceConfigFile) {
        ResourcesFileParser resParser;
        ResourceDef* resDef = resParser.getParsedResourceFile(resourceConfigFile);
        if (resDef) {
            ResourceFile* resourceFile = NULL;
            //recover ai files
            for (int i = 0; i < resDef->getAiResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getAiResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::AI);
                resourceFile->setResourceFormat(resDef->getAiResource(i)->format);
                resourceFile->setResourceName(resDef->getAiResource(i)->name);
                resourceFile->setResourceDescription(resDef->getAiResource(i)->description);
                resourceFile->setCache(resDef->getAiResource(i)->cache);
                resourceFile->setCompressed(resDef->getAiResource(i)->compressed);
                std::string ai = aiPath + resDef->getAiResource(i)->name;
                resourceFile->setResourcePath(ai);
                this->aiResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover font resources
            for (int i = 0; i < resDef->getFontResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getFontResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::FONT);
                resourceFile->setResourceFormat(resDef->getFontResource(i)->format);
                resourceFile->setResourceName(resDef->getFontResource(i)->name);
                resourceFile->setResourceDescription(resDef->getFontResource(i)->description);
                resourceFile->setCache(resDef->getFontResource(i)->cache);
                resourceFile->setCompressed(resDef->getFontResource(i)->compressed);
                std::string font = fontPath + resDef->getFontResource(i)->name;
                resourceFile->setResourcePath(font);
                this->fontResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover language resources
            for (int i = 0; i < resDef->getLanguageResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getLanguageResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::LANGUAGE);
                resourceFile->setResourceFormat(resDef->getLanguageResource(i)->format);
                resourceFile->setResourceName(resDef->getLanguageResource(i)->name);
                resourceFile->setResourceDescription(resDef->getLanguageResource(i)->description);
                resourceFile->setCache(resDef->getLanguageResource(i)->cache);
                resourceFile->setCompressed(resDef->getLanguageResource(i)->compressed);
                std::string language = languagePath + resDef->getLanguageResource(i)->name;
                resourceFile->setResourcePath(language);
                this->languageResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover levels
            for (int i = 0; i < resDef->getLevelResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getLevelResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::LEVEL);
                resourceFile->setResourceFormat(resDef->getLevelResource(i)->format);
                resourceFile->setResourceName(resDef->getLevelResource(i)->name);
                resourceFile->setResourceDescription(resDef->getLevelResource(i)->description);
                resourceFile->setCache(resDef->getLevelResource(i)->cache);
                resourceFile->setCompressed(resDef->getLevelResource(i)->compressed);
                std::string level = levelPath + resDef->getLevelResource(i)->name;
                resourceFile->setResourcePath(level);
                this->levelResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover levels
            for (int i = 0; i < resDef->getLevelResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getLevelResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::LEVEL);
                resourceFile->setResourceFormat(resDef->getLevelResource(i)->format);
                resourceFile->setResourceName(resDef->getLevelResource(i)->name);
                resourceFile->setResourceDescription(resDef->getLevelResource(i)->description);
                resourceFile->setCache(resDef->getLevelResource(i)->cache);
                resourceFile->setCompressed(resDef->getLevelResource(i)->compressed);
                std::string level = levelPath + resDef->getLevelResource(i)->name;
                resourceFile->setResourcePath(level);
                this->levelResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover model resources
            for (int i = 0; i < resDef->getModelResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getModelResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::MODEL);
                resourceFile->setResourceFormat(resDef->getModelResource(i)->format);
                resourceFile->setResourceName(resDef->getModelResource(i)->name);
                resourceFile->setResourceDescription(resDef->getModelResource(i)->description);
                resourceFile->setCache(resDef->getModelResource(i)->cache);
                resourceFile->setCompressed(resDef->getModelResource(i)->compressed);
                std::string model = modelPath + resDef->getModelResource(i)->name;
                resourceFile->setResourcePath(model);
                this->modelResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover music resources
            for (int i = 0; i < resDef->getMusicResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getMusicResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::MUSIC);
                resourceFile->setResourceFormat(resDef->getMusicResource(i)->format);
                resourceFile->setResourceName(resDef->getMusicResource(i)->name);
                resourceFile->setResourceDescription(resDef->getMusicResource(i)->description);
                resourceFile->setCache(resDef->getMusicResource(i)->cache);
                resourceFile->setCompressed(resDef->getMusicResource(i)->compressed);
                std::string music = musicPath + resDef->getMusicResource(i)->name;
                resourceFile->setResourcePath(music);
                this->musicResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover sound resources
            for (int i = 0; i < resDef->getSoundResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getSoundResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::SOUND);
                resourceFile->setResourceFormat(resDef->getSoundResource(i)->format);
                resourceFile->setResourceName(resDef->getSoundResource(i)->name);
                resourceFile->setResourceDescription(resDef->getSoundResource(i)->description);
                resourceFile->setCache(resDef->getSoundResource(i)->cache);
                resourceFile->setCompressed(resDef->getSoundResource(i)->compressed);
                std::string sound = soundPath + resDef->getSoundResource(i)->name;
                resourceFile->setResourcePath(sound);
                this->soundResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover textures resources
            for (int i = 0; i < resDef->getTextureResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getTextureResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::TEXTURE);
                resourceFile->setResourceFormat(resDef->getTextureResource(i)->format);
                resourceFile->setResourceName(resDef->getTextureResource(i)->name);
                resourceFile->setResourceDescription(resDef->getTextureResource(i)->description);
                resourceFile->setCache(resDef->getTextureResource(i)->cache);
                resourceFile->setCompressed(resDef->getTextureResource(i)->compressed);
                std::string texture = texturePath + resDef->getTextureResource(i)->name;
                resourceFile->setResourcePath(texture);
                this->textureResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover ui resources
            for (int i = 0; i < resDef->getUiResourcesSize(); i++) {
                resourceFile = new ResourceFile();
                resourceFile->setGameIdentifier(resDef->getUiResource(i)->gameIdentifier);
                resourceFile->setType(ResourceFile::UI);
                resourceFile->setResourceFormat(resDef->getUiResource(i)->format);
                resourceFile->setResourceName(resDef->getUiResource(i)->name);
                resourceFile->setResourceDescription(resDef->getUiResource(i)->description);
                resourceFile->setCache(resDef->getUiResource(i)->cache);
                resourceFile->setCompressed(resDef->getUiResource(i)->compressed);
                std::string ui = uiPath + resDef->getUiResource(i)->name;
                resourceFile->setResourcePath(ui);
                this->uiResources.insert(std::make_pair(resourceFile->getGameIdentifier(),
                        resourceFile));
            }
            //recover inicializationPath
            this->inicializationFilePath = inicializationFilePath + resDef->getInicializationPath();
            delete resDef;
        }
    }
}

std::string ResourceManager::getInicializationFilePath() {
    return this->inicializationFilePath;
}
