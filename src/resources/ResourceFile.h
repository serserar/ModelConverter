/* 
 * File:   ResourceFile.h
 * Author: serserar
 *
 * Created on April 21, 2014, 10:02 PM
 */

#ifndef RESOURCEFILE_H
#define	RESOURCEFILE_H
#include <string>

class ResourceFile {
public:

    enum ResourceType {
        AI, FONT, LANGUAGE, LEVEL, MODEL, MUSIC, SOUND, TEXTURE, UI
    };
    ResourceFile();
    ResourceFile(const ResourceFile& orig);
    virtual ~ResourceFile();
    void setGameIdentifier(std::string& identifier);
    std::string getGameIdentifier();
    void setType(ResourceType type);
    void setResourceFormat(std::string& resourceFormat);
    void setResourcePath(std::string& resourcePath);
    std::string getResourcePath();
    void setResourceName(std::string& resourceName);
    void setResourceDescription(std::string& resourceDescription);
    void setCache(bool isCache);
    bool isCache();
    void setCompressed(bool isCompresed);
private:
    ResourceType type;
    std::string gameIdentifier;
    std::string resourceFormat;
    std::string resourcePath;
    std::string resourceName;
    std::string resourceDescription;
    bool cache;
    bool compressed;
};

#endif	/* RESOURCEFILE_H */

