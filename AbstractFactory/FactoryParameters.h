#ifndef FACTORYPARAMETERS_H
#define FACTORYPARAMETERS_H

#include <unordered_map>
#include <string>
#include <Types/Vec2f.h>
#include <Types/TypeTable.h>

class FactoryParameters
{
    public:
        FactoryParameters(bool logUndefined = false);
        //FactoryParameters(std::initializer_list<std::pair<std::string,float>> list);
        FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list);
        ~FactoryParameters();

        template <typename Type>
        void add(const std::string& name, const Type& value);

        template <typename Type>
        Type get(const std::string& name, const Type& _default);
        template <typename Type>
        Type get(const std::string& name);

        std::unordered_map<TypeTable::ValueIndex,TypeTable::Value*>::iterator begin(){return table.begin();}
        std::unordered_map<TypeTable::ValueIndex,TypeTable::Value*>::iterator end(){return table.end();}

        std::vector<std::string> getUndefinedLog();

        void remove(const std::string& _name){table.removeValue(_name);}
        void clear();

        friend std::ostream& operator<< (std::ostream &out, const FactoryParameters &params);
        friend std::istream& operator>> (std::istream &in, FactoryParameters &params);

        TypeTable* getTypeTable(){return &table;}

    protected:
    private:
        //std::unordered_map<std::string, float> parameters;
        TypeTable table;
};

template <typename Type>
void FactoryParameters::add(const std::string& name, const Type& value)
{
    table.addValue(name, value);
}

template <typename Type>
Type FactoryParameters::get(const std::string& name, const Type& _default)
{
    return table.getValue(name, _default);
}

#endif // FACTORYPARAMETERS_H
