#include "TextFileFactoryLoader.h"

TextFileFactoryLoader::TextFileFactoryLoader(const char* filename, bool logUndefined)
:FactoryLoader(logUndefined),
file(filename)
{
    //ctor
}

TextFileFactoryLoader::~TextFileFactoryLoader()
{
    //dtor
}

bool TextFileFactoryLoader::isValid()
{
    return file.good();
}
bool TextFileFactoryLoader::next()
{
    file >> type;
    file >> name;
    std::string token;
    file >> token;
    if (token[0] != '{')
    {
        if (!file.good()) return false;
        syntaxError("Syntax error, '{' expected, " + token + " read instead");
    }
    while (file.good())
    {
        file >> token;
        if (token[0] == '}')
        {
            return true;
        }
        else
        {
            std::string variableName;
            file >> variableName;
            /*if (types.find(token) == types.end())
            {
                syntaxError("Type " + token + " not defined");
            }
            if (values.find(variableName) != values.end())
            {
                warning("Variable " + variableName + " already defined, redefining");
            }
            values[variableName] = types[token]->instance(&file);*/
            mvalues.addDynamicValue(token,variableName,&file);
        }
    }
    return false;
}
