#include "SerializationTypes.h"
#include <vector>
#include <Types/Vec2f.h>
class StringHelper : public SerializationHelper<std::string>
{
    public:
        void binaryRead(std::istream* _stream)
        {
            unsigned short length;
            _stream->read(reinterpret_cast<char*>(&length), sizeof(unsigned short));

            data.resize(length);
            _stream->read(&(data[0]), length);

        }
        void textRead(std::istream* _stream)
        {
            data.clear();
            while (true)
            {
                char c = '\0';
                _stream->get(c);
                if (c == '"' || c == '\0' || c == '\n' || !_stream->good())
                {
                    break;
                }
                else
                {
                    data.push_back(c);
                }
            }
        }
        void binaryWrite(std::ostream* _stream)
        {
            unsigned short length = data.length();
            _stream->write(reinterpret_cast<char*>(&length), sizeof(unsigned short));

            _stream->write(&(data[0]), length);
        }
        void textWrite(std::ostream* _stream)
        {
            *_stream << data;
        }
};
template <typename T>
class ArrayHelper : public SerializationHelper<std::vector<T>>
{
    public:
        ArrayHelper(SerializationHelper<T>* _helper){helper = _helper;}
        void binaryRead(std::istream* _stream)
        {
            unsigned short length;
            _stream->read(reinterpret_cast<char*>(&length), sizeof(unsigned short));

            this->data.resize(length);
            _stream->read(reinterpret_cast<char*>(&(this->data[0])), length * sizeof(T));

        }
        void textRead(std::istream* _stream)
        {
            int length;
            *_stream >> length;
            this->data.resize(length);
            for (int i = 0; i < length; i++)
            {
                helper->textRead(_stream);
                this->data[i] = helper->getData();
            }
        }
        void binaryWrite(std::ostream* _stream)
        {
            unsigned short length = this->data.size();
            _stream->write(reinterpret_cast<char*>(&length), sizeof(unsigned short));

            _stream->write(reinterpret_cast<char*>(&(this->data[0])), length * sizeof(T));
        }
        void textWrite(std::ostream* _stream)
        {
            *_stream << this->data.size() << ' ';

            for (unsigned int i = 0; i < this->data.size(); i++)
            {
                helper->setData(this->data[i]);
                helper->textWrite(_stream);
            }
        }
    private:
        SerializationHelper<T>* helper;
};
class Vec2fHelper : public SerializationHelper<Vec2f>
{
    public:
        void binaryRead(std::istream* _stream)
        {
            _stream->read(reinterpret_cast<char*>(&data), sizeof(Vec2f));
        }
        void textRead(std::istream* _stream)
        {
            *_stream >> data.x;
            *_stream >> data.y;
        }
        void binaryWrite(std::ostream* _stream)
        {
            _stream->write(reinterpret_cast<char*>(&data), sizeof(Vec2f));
        }
        void textWrite(std::ostream* _stream)
        {
            *_stream << data.x << ' ';
            *_stream << data.y << ' ';
        }
};

SerializationTypes::SerializationTypes()
{
    //ctor
    setHelperToDefault<float>();
    setHelper<std::string>(new StringHelper);
    setHelper<std::vector<Vec2f>>(new ArrayHelper<Vec2f>(new Vec2fHelper));
}

SerializationTypes::~SerializationTypes()
{
    //dtor
}
