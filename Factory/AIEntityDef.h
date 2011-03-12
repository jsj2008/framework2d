#ifndef AIENTITYDEF_H
#define AIENTITYDEF_H

#include <Factory/FactoryDef.h>
#include <AI/Brain.h>

class AIEntityDef : public FactoryDef
{
    public:
        void set(const char* _materialName, float _width, float _height, BrainType _aiType);
        float width, height;
        BrainType aiType;
    protected:
    private:
};

#endif // AIENTITYDEF_H
