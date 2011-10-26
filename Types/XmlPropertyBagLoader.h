#ifndef XMLPROPERTYBAGLOADER_H
#define XMLPROPERTYBAGLOADER_H

#include <Types/PropertyBagLoader.h>
#include <tinyxml.h>
class FactoryParameters;

class XmlPropertyBagLoader : public PropertyBagLoader
{
    public:
        XmlPropertyBagLoader(const char* _filename);
        XmlPropertyBagLoader(TiXmlElement* _propertyBag);
        virtual ~XmlPropertyBagLoader();
        int getVersion();
        bool startFactories();
            bool next();
            const char* getFactoryName();
            void readParameters(FactoryParameters* _params);
        void endFactories();
    protected:
    private:
        TiXmlDocument doc;
        TiXmlHandle handle;
        TiXmlElement* element;
};

#endif // XMLPROPERTYBAGLOADER_H
