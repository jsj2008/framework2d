#ifndef AIENTITYDEF_H
#define AIENTITYDEF_H

#include <Factory/FactoryDef.h>
#include <AI/Brain.h>

class AIEntityDef : public FactoryDef
{
    public:
        AIEntityDef(const char* _materialName, float _width, float _height, BrainType _aiType, const char* _weapon);
        float width, height;
        BrainType aiType;
        char weapon[16];
    protected:
    private:
};

#endif // AIENTITYDEF_H
