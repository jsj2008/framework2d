#ifndef FACTORYLIST_H
#define FACTORYLIST_H

#include <vector>
#include <queue>
#include <Factory/AllFactoryDefs.h>
class Factory;
class Entity;
union StandardFactoryDef
{
    StandardFactoryDef(PlayerDef& def);
    StandardFactoryDef(CrateDef& def);
    StandardFactoryDef(ConvexGeometryDef& def);
    StandardFactoryDef(BubbleDef& def);
    StandardFactoryDef(ParticleDef& def);
    StandardFactories type;
    PlayerDef playerDef;
    CrateDef crateDef;
    ConvexGeometryDef convexGeometryDef;
    BubbleDef bubbleDef;
    ParticleDef particleDef;
};

extern class FactoryList
{
    public:
        FactoryList();
        virtual ~FactoryList();
        Entity* useFactory(StandardFactoryDef def, StandardFactories factoryType);
        //Entity* useFactory(FactoryDef* def, StandardFactories factory);
        Factory* getFactory(StandardFactories factory);
    protected:
    private:
        std::vector<Factory*> factories;
}g_FactoryList;

#endif // FACTORYLIST_H
