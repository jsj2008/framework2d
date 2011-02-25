#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include "Factory.h"


class CrateFactory : public Factory
{
    public:
        CrateFactory();
        virtual ~CrateFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
};

#endif // CRATEFACTORY_H
