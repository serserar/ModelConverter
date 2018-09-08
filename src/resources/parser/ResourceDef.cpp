/* 
 * File:   ResourceDef.cpp
 * Author: serserar
 * 
 * Created on April 21, 2014, 7:22 PM
 */

#include "ResourceDef.h"

ResourceDef::ResourceDef() {
}

ResourceDef::~ResourceDef() {
    std::for_each(aiResources.begin(), aiResources.end(), delete_resource_ptr());
    std::for_each(fontResources.begin(), fontResources.end(), delete_resource_ptr());
    std::for_each(languageResources.begin(), languageResources.end(), delete_resource_ptr());
    std::for_each(levelResources.begin(), levelResources.end(), delete_resource_ptr());
    std::for_each(modelResources.begin(), modelResources.end(), delete_resource_ptr());
    std::for_each(musicResources.begin(), musicResources.end(), delete_resource_ptr());
    std::for_each(soundResources.begin(), soundResources.end(), delete_resource_ptr());
    std::for_each(textureResources.begin(), textureResources.end(), delete_resource_ptr());
    std::for_each(uiResources.begin(), uiResources.end(), delete_resource_ptr());
}

void ResourceDef::addAiResource(resource* aiResource) {
    this->aiResources.push_back(aiResource);
}

resource* ResourceDef::getAiResource(unsigned int index) {
    resource* aiResource = NULL;
    if (index < this->aiResources.size()) {
        aiResource = this->aiResources.at(index);
    }
    return aiResource;
}

unsigned int ResourceDef::getAiResourcesSize() {
    return this->aiResources.size();
}

void ResourceDef::addFontResource(resource* fontResource) {
    this->fontResources.push_back(fontResource);
}

resource* ResourceDef::getFontResource(unsigned int index) {
    resource* fontResource = NULL;
    if (index < this->fontResources.size()) {
        fontResource = this->fontResources.at(index);
    }
    return fontResource;
}

unsigned int ResourceDef::getFontResourcesSize() {
    return this->fontResources.size();
}

void ResourceDef::addLanguageResource(resource* languageResource) {
    this->languageResources.push_back(languageResource);
}

resource* ResourceDef::getLanguageResource(unsigned int index) {
    resource* languageResource = NULL;
    if (index < this->languageResources.size()) {
        languageResource = this->languageResources.at(index);
    }
    return languageResource;
}

unsigned int ResourceDef::getLanguageResourcesSize() {
    return this->languageResources.size();
}

void ResourceDef::addLevelResource(resource* levelResource) {
    this->levelResources.push_back(levelResource);
}

resource* ResourceDef::getLevelResource(unsigned int index) {
    resource* levelResource = NULL;
    if (index < this->levelResources.size()) {
        levelResource = this->levelResources.at(index);
    }
    return levelResource;
}

unsigned int ResourceDef::getLevelResourcesSize() {
    return this->levelResources.size();
}

void ResourceDef::addModelResource(resource* modelResource) {
    this->modelResources.push_back(modelResource);
}

resource* ResourceDef::getModelResource(unsigned int index) {
    resource* modelResource = NULL;
    if (index < this->modelResources.size()) {
        modelResource = this->modelResources.at(index);
    }
    return modelResource;
}

unsigned int ResourceDef::getModelResourcesSize() {
    return this->modelResources.size();
}

void ResourceDef::addMusicResource(resource* musicResource) {
    this->musicResources.push_back(musicResource);
}

resource* ResourceDef::getMusicResource(unsigned int index) {
    resource* musicResource = NULL;
    if (index < this->musicResources.size()) {
        musicResource = this->musicResources.at(index);
    }
    return musicResource;
}

unsigned int ResourceDef::getMusicResourcesSize() {
    return this->musicResources.size();
}

void ResourceDef::addSoundResource(resource* soundResource) {
    this->soundResources.push_back(soundResource);
}

resource* ResourceDef::getSoundResource(unsigned int index) {
    resource* soundResource = NULL;
    if (index < this->soundResources.size()) {
        soundResource = this->soundResources.at(index);
    }
    return soundResource;
}

unsigned int ResourceDef::getSoundResourcesSize() {
    return this->soundResources.size();
}

void ResourceDef::addTextureResource(resource* textureResource) {
    this->textureResources.push_back(textureResource);
}

resource* ResourceDef::getTextureResource(unsigned int index) {
    resource* textureResource = NULL;
    if (index < this->textureResources.size()) {
        textureResource = this->textureResources.at(index);
    }
    return textureResource;
}

unsigned int ResourceDef::getTextureResourcesSize() {
    return this->textureResources.size();
}

void ResourceDef::addUiResource(resource* uiResource) {
    this->uiResources.push_back(uiResource);
}

resource* ResourceDef::getUiResource(unsigned int index) {
    resource* uiResource = NULL;
    if (index < this->uiResources.size()) {
        uiResource = this->uiResources.at(index);
    }
    return uiResource;
}

unsigned int ResourceDef::getUiResourcesSize() {
    return this->uiResources.size();
}

void ResourceDef::setInicializationPath(std::string inicializationPath) {
    this->inicializationFilePath = inicializationPath;
}

std::string ResourceDef::getInicializationPath() {
    return this->inicializationFilePath;
}
