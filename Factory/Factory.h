#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
class Entity;
class b2Vec2;
class Factory
{
    public:
        Factory();
        virtual ~Factory();
        virtual Entity* createEntity(b2Vec2* origin)=0;
    protected:
    private:
};

#endif // FACTORY_H
