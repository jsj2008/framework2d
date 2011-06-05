#ifndef FACTORYDEFLIST_H
#define FACTORYDEFLIST_H

#include <Factory/FactoryList.h>

extern class FactoryDefList
{
    public:
        FactoryDefList();
        virtual ~FactoryDefList();
        Entity* singleUse(StandardFactoryDef def);
        Entity* useFactoryDef(unsigned int def);
        Entity* useFactoryDef(unsigned int def, const Vec2f& position);
        Entity* useFactoryDef(unsigned int def, const Vec2f& position, const Vec2f& direction);
    protected:
    private:
        std::vector<StandardFactoryDef> factoryDefs;
}g_FactoryDefList;

#endif // FACTORYDEFLIST_H
