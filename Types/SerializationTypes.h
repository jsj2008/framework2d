#ifndef SERIALIZATIONTYPES_H
#define SERIALIZATIONTYPES_H

#include <Log/Log.h>
#include <iostream>

class SerializationHelperBase
{
    public:
        SerializationHelperBase(){}
        virtual ~SerializationHelperBase(){}
        virtual void binaryRead(std::istream* _stream)=0;
        virtual void textRead(std::istream* _stream)=0;
        virtual void binaryWrite(std::ostream* _stream)=0;
        virtual void textWrite(std::ostream* _stream)=0;
};
template <typename T>
class SerializationHelper : public SerializationHelperBase
{
    public:
        SerializationHelper(){}
        virtual ~SerializationHelper(){}
        void setData(const T& _data){data = _data;}
        const T& getData(){return data;}
        virtual void binaryRead(std::istream* _stream)=0;
        virtual void textRead(std::istream* _stream)=0;
        virtual void binaryWrite(std::ostream* _stream)=0;
        virtual void textWrite(std::ostream* _stream)=0;
    protected:
        T data;
};
class SerializationTypes
{
    public:
        SerializationTypes();
        ~SerializationTypes();

        template <typename T>
        SerializationHelper<T>* getHelper(const T& _value);
        template <typename T>
        void setHelper(SerializationHelper<T>* _helper)
        {
            *helper<T>() = _helper;
        }
        template <typename T>
        void setHelperToDefault();
    protected:
    private:
        template <typename T>
        static SerializationHelper<T>** helper()
        {
            static SerializationHelper<T>* value;
            return &value;
        }
};

#include <AbstractFactory/EvaluateTypeName.h>
template <typename T>
SerializationHelper<T>* SerializationTypes::getHelper(const T& _value)
{
    SerializationHelper<T>* ret = *helper<T>();
    if (ret == nullptr)
    {
        g_Log.error("No serialisation helper defined for " + EvaluateTypeName<T>());
    }
    ret->setData(_value);
    return ret;
}
template <typename T>
class DefaultHelper : public SerializationHelper<T>
{
    public:
        void binaryRead(std::istream* _stream)
        {
            _stream->read(reinterpret_cast<char*>(&(this->data)), sizeof(T));
        }
        void textRead(std::istream* _stream)
        {
            *_stream >> SerializationHelper<T>::data;
        }
        void binaryWrite(std::ostream* _stream)
        {
            _stream->write(reinterpret_cast<const char*>(&(this->data)), sizeof(T));
        }
        void textWrite(std::ostream* _stream)
        {
            *_stream << SerializationHelper<T>::data;
        }
};
template <typename T>
void SerializationTypes::setHelperToDefault()
{
    *helper<T>() = new DefaultHelper<T>;
}

#endif // SERIALIZATIONTYPES_H
