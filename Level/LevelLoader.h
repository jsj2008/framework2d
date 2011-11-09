#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <Level/EventListLoader.h>
#include <Level/FactoryListLoader.h>
#include <Level/EntityListLoader.h>
#include <Level/LevelData.h>
#include <string>
#include <vector>
class XmlResourceProvider;
class TiXmlElement;

class LevelLoader : public DataLoader<LevelLoader, LevelData>
{
    public:
        LevelLoader(XmlResourceProvider* _provider);
        virtual ~LevelLoader();
        void virtualLoad(const std::string& _levelName, LevelData* _data);
    protected:
    private:
        EventListLoader eventListLoader;
        FactoryListLoader factoryListLoader;
        EntityListLoader entitylistLoader;
        XmlResourceProvider* provider;
        std::vector<std::string> getChildrenOfType(const std::string& _type, TiXmlElement* _root, const std::string& _rootAddress);
        void addEventList(LevelData* _data, const std::string& _address);
        void addEntityList(LevelData* _data, const std::string& _address);
        void addFactoryList(LevelData* _data, const std::string& _address);
};

#endif // LEVELLOADER_H
