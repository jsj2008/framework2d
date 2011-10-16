#ifndef TEXTFILEPROPERTYBAGSERIALIZER_H
#define TEXTFILEPROPERTYBAGSERIALIZER_H

#include <Types/PropertyBagSerializer.h>
#include <fstream>

class TextFilePropertyBagSerializer : public PropertyBagSerializer
{
    public:
        TextFilePropertyBagSerializer(std::ofstream* _file);
        virtual ~TextFilePropertyBagSerializer();
        void startFactories(unsigned int _size, const std::string& _productName);
            void startFactory(const std::string& _name);
            void setVersion(int _version);
                void setNumberOfProperties(unsigned int _size);
                    void createProperty(const std::string& _typeIndex, const std::string& _name);
                        void outputValueUntyped(SerializationHelperBase* _value);
                        void startArray(unsigned int _size);
                        void arrayValue(SerializationHelperBase* _value);
                        void endArray();
            void endFactory();
        void endFactories();
    protected:
    protected:
    private:
        std::ofstream* file;
};

#endif // TEXTFILEPROPERTYBAGSERIALIZER_H
