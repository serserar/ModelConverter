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

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <string>
#include <map>
// #ifdef OS_WINDOWS
// #elif OS_LINUX
#include <unistd.h>
// #endif
#include "ResourceFile.h"
#include "parser/ResourcesFileParser.h"
#include "parser/ResourceDef.h"

class ResourceManager {
public:

    ResourceManager();
    ~ResourceManager();

    std::string getMediaPath();
    void setApplicationPath(std::string& mediaPath);
    bool initialize();
    bool initialize(std::string& basePath);
    std::string getAiPath();
    std::string getFontPath();
    std::string getLevelPath();
    std::string getLanguagePath();
    std::string getModelPath();
    std::string getMusicPath();
    std::string getSoundPath();
    std::string getTexturePath();
    std::string getUiPath();

    ResourceFile* getAi(std::string& aiId);
    ResourceFile* getFont(std::string& fontId);
    ResourceFile* getLevel(std::string& levelId);
    ResourceFile* getLanguage(std::string& languageId);
    ResourceFile* getModel(std::string& modelId);
    ResourceFile* getMusic(std::string& musicId);
    ResourceFile* getSound(std::string& soundId);
    ResourceFile* getTexture(std::string& textureId);
    ResourceFile* getUi(std::string& uiId);
    ResourceFile* getResourceById(int resourceType, std::string& ResourceId);
    std::string getInicializationFilePath();

    static const char* MEDIA_FOLDER;
    static const char* AI_FOLDER;
    static const char* FONT_FOLDER;
    static const char* LANGUAGE_FOLDER;
    static const char* LEVEL_FOLDER;
    static const char* MODEL_FOLDER;
    static const char* MUSIC_FOLDER;
    static const char* SOUND_FOLDER;
    static const char* TEXTURE_FOLDER;
    static const char* UI_FOLDER;
    static const char* INICIALIZATION_FOLDER;
    static const char* RESOURCES_FILE_NAME;

protected:

    void initResourcePaths(std::string& basePath);
    void loadResourceConfigurationFile(char* resourceConfigFile);
    std::string getBasePath();

private:

    std::string mediaPath;
    std::string aiPath;
    std::string fontPath;
    std::string languagePath;
    std::string levelPath;
    std::string modelPath;
    std::string musicPath;
    std::string soundPath;
    std::string texturePath;
    std::string uiPath;
    std::string inicializationFilePath;
    
    std::map<std::string, ResourceFile*> aiResources;
    std::map<std::string, ResourceFile*> fontResources;
    std::map<std::string, ResourceFile*> languageResources;
    std::map<std::string, ResourceFile*> levelResources;
    std::map<std::string, ResourceFile*> modelResources;
    std::map<std::string, ResourceFile*> musicResources;
    std::map<std::string, ResourceFile*> soundResources;
    std::map<std::string, ResourceFile*> textureResources;
    std::map<std::string, ResourceFile*> uiResources;

};

#endif // RESOURCEMANAGER_H
