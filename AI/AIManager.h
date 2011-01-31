#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <AI/Brain.h>
struct BrainFactoryDef
{
    BrainType brainType;
    union BrainTypeDef
    {
        struct PlayerInputBrainDef
        {
        };
        PlayerInputBrainDef playerInputBrainDef;
    };
};
class AIManager
{
    public:
        AIManager();
        virtual ~AIManager();
        Brain* brainFactory(BrainFactoryDef& def);
    protected:
    private:
};

#endif // AIMANAGER_H
