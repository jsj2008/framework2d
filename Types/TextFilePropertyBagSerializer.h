#ifndef TEXTFILEPROPERTYBAGSERIALIZER_H
#define TEXTFILEPROPERTYBAGSERIALIZER_H

#include <Types/PropertyBagSerializer.h>
#include <fstream>

class TextFilePropertyBagSerializer : public PropertyBagSerializer
{
    public:
        TextFilePropertyBagSerializer(std::ofstream* _file);
        virtual ~TextFilePropertyBagSerializer();
        void startArray(unsigned int _size);
        void outputString(const std::string& _str);
    protected:
    private:
        std::ofstream* file;
        void outputValue(SerializationHelperBase* _value);
};

#endif // TEXTFILEPROPERTYBAGSERIALIZER_H
