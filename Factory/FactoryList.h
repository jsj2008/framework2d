#ifndef FACTORYLIST_H
#define FACTORYLIST_H

#include <vector>
#include <queue>
#include <Factory/AllFactoryDefs.h>
class Factory;
class Entity;
union StandardFactoryDef
{
    StandardFactoryDef();
    StandardFactoryDef(CrateDef& def);
    StandardFactoryDef(ConvexGeometryDef& def);
    StandardFactoryDef(BubbleDef& def);
    StandardFactoryDef(ParticleDef& def);
    StandardFactoryDef(AIEntityDef& def);
    StandardFactoryDef(ProjectileDef& def);
    StandardFactories type;
    FactoryDef baseDef;
    CrateDef crateDef;
    ConvexGeometryDef convexGeometryDef;
    BubbleDef bubbleDef;
    ParticleDef particleDef;
    AIEntityDef aiEntityDef;
    ProjectileDef projectileDef;
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
