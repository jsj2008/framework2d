#ifndef FACTORYPARAMETERS_H
#define FACTORYPARAMETERS_H

#include <unordered_map>
#include <string>
#include <Types/Vec2f.h>
#include <Types/DynamicTypeTable.h>

class FactoryParameters
{
    public:
        FactoryParameters();
        //FactoryParameters(std::initializer_list<std::pair<std::string,float>> list);
        FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list);
        ~FactoryParameters();

        template <typename T>
        void add(const std::string& name, const T& value);
        template <typename T>
        T get(const std::string& name, const T& _default);

        void clear();

        friend std::ostream& operator<< (std::ostream &out, const FactoryParameters &params);
        friend std::istream& operator>> (std::istream &in, FactoryParameters &params);

    protected:
    private:
        //std::unordered_map<std::string, float> parameters;
        DynamicTypeTable table;
};

template <typename T>
void FactoryParameters::add(const std::string& name, const T& value)
{
    table.addValue(name, value);
}

template <typename T>
T FactoryParameters::get(const std::string& name, const T& _default)
{
    return table.getValue(name, _default);
}

#endif // FACTORYPARAMETERS_H
