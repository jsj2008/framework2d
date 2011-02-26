#ifndef FACTORYLIST_H
#define FACTORYLIST_H

#include <istream>
#include <vector>
class Factory;
class FactoryDef;
class Entity;

extern class FactoryList
{
    public:
        enum StandardFactories
        {
            ePlayerFactory,
            eConvexPolygonFactory,
            eCrateFactory,
            eBubbleFactory,
            eStandardFactoriesMax
        };
        FactoryList();
        virtual ~FactoryList();
        Entity* useFactory(FactoryDef* def, StandardFactories factory);
        Factory* getFactory(StandardFactories factory);
    protected:
    private:
        std::vector<Factory*> factories;
}g_FactoryList;

#endif // FACTORYLIST_H
