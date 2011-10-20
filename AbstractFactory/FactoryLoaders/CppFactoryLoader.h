#ifndef CPPFACTORYLOADER_H
#define CPPFACTORYLOADER_H

#include <AbstractFactory/FactoryLoader.h>
#include <ostream>

class CppFactoryLoader : public FactoryLoader
{
    public:
        CppFactoryLoader();
        virtual ~CppFactoryLoader();
        bool isValid();
        bool next();
        template <typename Type>
        void addValue(const std::string& _name, const Type& _value);
        void output();
        void setName(const std::string& _name){name = _name;}
        void setType(const std::string& _type){type = _type;}
        void addDynamicValue(const std::string& _type, const std::string& _name, const std::string& _value);
    protected:
    private:
};

template <typename Type>
void CppFactoryLoader::addValue(const std::string& _name, const Type& _value)
{
    mvalues.addValue<Type>(_name, _value);
}
#endif // CPPFACTORYLOADER_H
