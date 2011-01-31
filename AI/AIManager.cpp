#include "AIManager.h"
#include "AllBrains.h"

AIManager::AIManager()
{
    //ctor
}

AIManager::~AIManager()
{
    //dtor
}

Brain* AIManager::brainFactory(BrainFactoryDef& def)
{
    Brain* brain;
    switch (def.brainType)
    {
        case ePlayerInputBrainType:
        {
            brain = new PlayerInputBrain;
            break;
        };
        case eBrainTypesMax:
        {
            throw "Invalid enum";
            break;
        };
    }
    return brain;
}
