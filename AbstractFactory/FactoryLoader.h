#ifndef FACTORYLOADER_H
#define FACTORYLOADER_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <Types/Vec2f.h>

class FactoryLoader
{
    public:
        FactoryLoader(const char* filename);
        virtual ~FactoryLoader();
        const std::pair<std::string,std::string> next();
        void end();
        /// Default is a keyword, so I called them "normal" :(
        float getFloat(const std::string& name, float normal = 0.0f);
        const Vec2f getVec2f(const std::string& name, const Vec2f& normal = Vec2f(0,0));
        const std::string getString(const std::string& name, const std::string& normal = "");
    protected:
    private:
        std::ifstream file;
        std::unordered_map<std::string,float> floatValues;
        std::unordered_map<std::string,std::string> stringValues;
        void addFloat(const std::string& name, float value);
        void addVec2f(const std::string& name, const Vec2f& value);
        void addString(const std::string& name, const std::string& value);
        void syntaxError(const std::string& type, const std::string& name, const std::string& message);
};

#endif // FACTORYLOADER_H
