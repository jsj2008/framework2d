#ifndef AIENTITYDEF_H
#define AIENTITYDEF_H

#include <Factory/FactoryDef.h>


class AIEntityDef : public FactoryDef
{
    public:
        enum AIType : unsigned short
        {
            eZombie, /// Walks towards enemy trying to attack with no self preservation
            eAITypesSize
        };
        void set(const char* _materialName, float _width, float _height, AIType _aiType);
        float width, height;
        AIType aiType;
    protected:
    private:
};

#endif // AIENTITYDEF_H
