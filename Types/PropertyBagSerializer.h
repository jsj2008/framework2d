#ifndef PROPERTYBAGSERIALIZER_H
#define PROPERTYBAGSERIALIZER_H

#include <string>
class SerializationTypes;
class SerializationHelperBase;

class PropertyBagSerializer
{
    public:
        PropertyBagSerializer(SerializationTypes* _types);
        virtual ~PropertyBagSerializer();
        virtual void startArray(unsigned int _size)=0;
        virtual void outputString(const std::string& _str)=0;

        template <typename T>
        void outputArray(const std::string& _typeIndex, const std::string& _name, const T* _value, unsigned int _size);
        template <typename T>
        void outputValue(const T& _value);

    protected:
    private:
        virtual void outputValue(SerializationHelperBase* _value)=0;
        SerializationTypes* types;
};

#include <Types/SerializationTypes.h>
template <typename T>
void PropertyBagSerializer::outputValue(const T& _value)
{
    SerializationHelperBase* helper = types->getHelper<T>(_value);
    outputValue(helper);
}
#endif // PROPERTYBAGSERIALIZER_H
