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
        virtual void startFactories(unsigned int _size, const std::string& _productName)=0;
            virtual void startFactory(const std::string& _name)=0;
            virtual void setVersion(int _version)=0;
                virtual void setNumberOfProperties(unsigned int _size)=0;
                    virtual void createProperty(const std::string& _typeIndex, const std::string& _name)=0;
                        template <typename T>
                        void outputArray(const T* _value, unsigned int _size);
                        template <typename T>
                        void outputValue(const T& _value);
            virtual void endFactory()=0;
        virtual void endFactories()=0;


    protected:
    private:
        virtual void startArray(unsigned int _size)=0;
        virtual void arrayValue(SerializationHelperBase* _value)=0;
        virtual void endArray()=0;
        virtual void outputValueUntyped(SerializationHelperBase* _value)=0;
        SerializationTypes* types;
};

#include <Types/SerializationTypes.h>
template <typename T>
void PropertyBagSerializer::outputValue(const T& _value)
{
    SerializationHelperBase* helper = types->getHelper<T>(_value);
    outputValueUntyped(helper);
}
template <typename T>
void PropertyBagSerializer::outputArray(const T* _values, unsigned int _size)
{
    startArray(_size);
    SerializationHelper<T>* helper = types->getHelper<T>(_values[0]);
    for (unsigned int i = 0; i < _size; i++)
    {
        helper->setData(_values[i]);
        arrayValue(helper);
    }
    endArray();
}
#endif // PROPERTYBAGSERIALIZER_H
