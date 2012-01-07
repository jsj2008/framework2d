#ifndef PROPERTYBAGDATA_H
#define PROPERTYBAGDATA_H

#include <Level/LoadedData.h>
#include <vector>
class AbstractFactories;
class TypeTable;
class FactoryLoader;
class FactoryData;

class PropertyBagData : public LoadedData
{
    public:
        PropertyBagData();
        virtual ~PropertyBagData();
        void build(TypeTable* _params);
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        void addDynamicValue(const std::string& _type, const std::string& _name, const std::string& _value);
        void addDynamicArrayValue(const std::string& _type, const std::string& _name, int _size, const std::string* _values);
    protected:
    private:
        class PropertyData
        {
            public:
                PropertyData(const std::string& _name);
                virtual void outputProperty(TypeTable* _table)=0;
            protected:
                std::string name;
        };
        class StandardProperty: public PropertyData
        {
            public:
                StandardProperty(const std::string& _name, const std::string& _type, const std::string& _value);
                void outputProperty(TypeTable* _table);
            private:
                //TypeTable::Value* value;
                std::string type, value;
        };
        class ArrayProperty: public PropertyData
        {
            public:
                ArrayProperty(const std::string& _type, const std::string& _name, int _size, const std::string* _values);
                void outputProperty(TypeTable* _table);
            private:
                //TypeTable::Value* value;
                std::string type;
                std::vector<std::string> values;
        };
        /*class FactoryProperty: public PropertyData
        { /// FIXME. Once TypeList is finished, make this a template class decided from TypeList.
        /// Need to have two classes, FactoryProperty(template of factory) and StandardProperty(property type). FactoryProperty grabs a FactoryData
            public:
                FactoryProperty(const std::string& _name, const std::string& _factoryType, const std::string& _factory);
                void outputProperty(TypeTable* _table);
            private:
                std::string factoryType;
                FactoryData* factory;
        };*/
        std::vector<PropertyData*> properties;
};

#endif // PROPERTYBAGDATA_H
