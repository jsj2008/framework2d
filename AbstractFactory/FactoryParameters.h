#ifndef FACTORYPARAMETERS_H
#define FACTORYPARAMETERS_H

#include <unordered_map>
#include <string>
#include <Types/Vec2f.h>

class FactoryParameters
{
    public:
        FactoryParameters();
        //FactoryParameters(std::initializer_list<std::pair<std::string,float>> list);
        FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list);
        ~FactoryParameters();
        void add(const std::string&, float value);
        //float getFloat(const std::string& name);

        void add(const std::string&, const Vec2f& value);
        const Vec2f getVec2f(const std::string& name);
    protected:
    private:
        std::unordered_map<std::string, float> parameters;
};

#endif // FACTORYPARAMETERS_H
