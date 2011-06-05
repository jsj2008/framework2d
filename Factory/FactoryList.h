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
    StandardFactoryDef(ConvexGeometryDef& def);
    StandardFactoryDef(BubbleDef& def);
    StandardFactoryDef(AIEntityDef& def);
    StandardFactories type;
    FactoryDef baseDef;
    ConvexGeometryDef convexGeometryDef;
    BubbleDef bubbleDef;
    AIEntityDef aiEntityDef;
};

extern class FactoryList
{
    public:
        FactoryList();
        virtual ~FactoryList();
    protected:
    private:
        friend class FactoryDefList;
        Entity* useFactory(StandardFactoryDef def, StandardFactories factoryType); /// FIXME i removed this unused parameter in another branch
        Factory* getFactory(StandardFactories factory);
        std::vector<Factory*> factories;
}g_FactoryList;

#endif // FACTORYLIST_H
