#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
class Entity;
class Vec2f;
class Factory
{
    public:
        Factory();
        virtual ~Factory();
        virtual Entity* createEntity(Vec2f* origin)=0;
    protected:
    private:
};

#endif // FACTORY_H
