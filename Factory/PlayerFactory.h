#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <Factory/Factory.h>
#include <AI/AIManager.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>


class PlayerFactory : public Factory
{
    public:
        PlayerFactory();
        virtual ~PlayerFactory();
        Entity* createEntity(FactoryDef* def);
    protected:
    private:
        PhysicsFactoryDef physicsDef;
};

#endif // PLAYERFACTORY_H
