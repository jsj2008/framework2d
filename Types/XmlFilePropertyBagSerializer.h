#ifndef XMLFILEPROPERTYBAGSERIALIZER_H
#define XMLFILEPROPERTYBAGSERIALIZER_H

#include <Types/PropertyBagSerializer.h>
#include <fstream>
#include <stack>
#include <tinyxml.h>

class XmlFilePropertyBagSerializer : public PropertyBagSerializer
{
    public:
        XmlFilePropertyBagSerializer(const char* _filename, bool _append);
        virtual ~XmlFilePropertyBagSerializer();
        void setVersion(int _version);
        void startFactories(unsigned int _size, const std::string& _productName);
            void startFactory(const std::string& _name);
                void setNumberOfProperties(unsigned int _size);
                    void createProperty(const std::string& _typeIndex, const std::string& _name);
                        void outputValueUntyped(SerializationHelperBase* _value);
                        void startArray(unsigned int _size);
                        void arrayValue(SerializationHelperBase* _value);
                        void endArray();
            void endFactory();
        void endFactories();

        void startFactoryDefinitions();
        void startFactoryDefinition(const std::string& _type, const std::string& _name);
        void endFactoryDefinition();
        void endFactoryDefinitions();
    protected:
    private:
        TiXmlDocument output;
        std::stack<TiXmlElement*> elements;
        const char* filename;
};

#endif // XMLFILEPROPERTYBAGSERIALIZER_H
