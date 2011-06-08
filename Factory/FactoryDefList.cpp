#include "FactoryDefList.h"
FactoryDefList g_FactoryDefList;

FactoryDefList::FactoryDefList()
{
    //ctor
    AIEntityDef def("player",2,2,ePlayerInputBrainType,"pistol");
    def.position = Vec2f(-20,0);
    factoryDefs.push_back(def);
}

FactoryDefList::~FactoryDefList()
{
    //dtor
}

Entity* FactoryDefList::singleUse(StandardFactoryDef def)
{
    return g_FactoryList.useFactory(def,eStandardFactoriesMax);
}
Entity* FactoryDefList::useFactoryDef(unsigned int def)
{
    return g_FactoryList.useFactory(factoryDefs[def],eStandardFactoriesMax);
}
Entity* FactoryDefList::useFactoryDef(unsigned int def, const Vec2f& position)
{
    factoryDefs[def].baseDef.position = position;
    return useFactoryDef(def);
}
/*Entity* FactoryDefList::useFactoryDef(unsigned int def, const Vec2f& position, const Vec2f& direction)
{

}
*/
