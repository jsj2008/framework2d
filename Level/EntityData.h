#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <Level/LoadedData.h>
class PropertyBagData;
class AbstractFactories;
class Level;

class EntityData : public LoadedData
{
    public:
        EntityData(const char* _type, PropertyBagData* _propertyBag);
        virtual ~EntityData();

        GameObjectBase* get();
        void build(AbstractFactories* _factories, Level* _level);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        PropertyBagData* propertyBag;
        std::string type;
};

#endif // ENTITYDATA_H
