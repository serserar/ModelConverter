/* 
 * File:   ResourceFile.cpp
 * Author: serserar
 * 
 * Created on April 21, 2014, 10:02 PM
 */

#include "ResourceFile.h"

ResourceFile::ResourceFile() {
}

ResourceFile::ResourceFile(const ResourceFile& orig) {
}

ResourceFile::~ResourceFile() {
}

void ResourceFile::setGameIdentifier(std::string& identifier) {
    this->gameIdentifier = identifier;
}

std::string ResourceFile::getGameIdentifier() {
    return this->gameIdentifier;
}

void ResourceFile::setType(ResourceType type) {
    this->type = type;
}

void ResourceFile::setResourceFormat(std::string& resourceFormat) {
    this->resourceFormat = resourceFormat;
}

void ResourceFile::setResourcePath(std::string& resourcePath) {
    this->resourcePath = resourcePath;
}

std::string ResourceFile::getResourcePath() {
    return this->resourcePath;
}

void ResourceFile::setResourceName(std::string& resourceName) {
    this->resourceName = resourceName;
}

void ResourceFile::setResourceDescription(std::string& resourceDescription) {
    this->resourceDescription = resourceDescription;
}

void ResourceFile::setCache(bool isCache) {
    this->cache = isCache;
}

bool ResourceFile::isCache() {
    return this->cache;
}


void ResourceFile::setCompressed(bool isCompresed) {
    this->compressed = isCompresed;
}


