#ifndef ParticleDef_H
#define ParticleDef_H

#include <Factory/FactoryDef.h>


class ParticleDef : public FactoryDef
{
    public:
        float density;
        int lifetime;
    protected:
    private:
};

#endif // ParticleDef_H
