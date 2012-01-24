#ifndef FACTORYGROUPDATA_H
#define FACTORYGROUPDATA_H

#include <Level/LoadedData.h>
#include <vector>
class AbstractFactories;

class FactoryGroupData : public LoadedData
{
    public:
        class Child
        {
            public:
                Child(const char* _name, const char* _type);
                ~Child();
                void addChild(Child* _child);
            private:
                std::string name, type;
                std::vector<Child*> children;
        };
        FactoryGroupData(const char* _name);
        virtual ~FactoryGroupData();

        GameObjectBase* build(AbstractFactories* _factories);
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        Child* getRoot(){return &root;}
    protected:
    private:
        std::string name;
        Child root;
};

#endif // FACTORYGROUPDATA_H
