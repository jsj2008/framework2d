#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include "Factory.h"


class CrateFactory : public Factory
{
    public:
        CrateFactory(int _width, int _height);
        virtual ~CrateFactory();
        Entity* createEntity(Vec2f* origin);
    protected:
    private:
        int width, height;
};

#endif // CRATEFACTORY_H
