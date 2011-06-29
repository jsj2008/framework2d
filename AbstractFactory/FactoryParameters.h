#ifndef FACTORYPARAMETERS_H
#define FACTORYPARAMETERS_H

#include <unordered_map>
#include <string>
#include <Types/Vec2f.h>
#include <Types/TypeTable.h>

class FactoryParameters
{
    public:
        FactoryParameters();
        //FactoryParameters(std::initializer_list<std::pair<std::string,float>> list);
        FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list);
        ~FactoryParameters();

        template <typename Type>
        void add(const std::string& name, const Type& value);
        template <typename Type>
        Type get(const std::string& name, const Type& _default);

        void clear();

        friend std::ostream& operator<< (std::ostream &out, const FactoryParameters &params);
        friend std::istream& operator>> (std::istream &in, FactoryParameters &params);

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
