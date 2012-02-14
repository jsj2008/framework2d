#ifndef WATERVOLUMEFACTORY_H
#define WATERVOLUMEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Entities/Entity.h>
#include <Graphics/Skins/Skin.h>
#include <Physics/BodyParts/BodyPart.h>
class WaterPhysicsSystem;

class WaterVolumeFactory : public AbstractFactory<Entity, WaterVolumeFactory>
{
    public:
        WaterVolumeFactory();
        virtual ~WaterVolumeFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "WaterVolumeFactory";
        }
    protected:
    private:
        AbstractFactoryBase<Skin>* skinFactory;
        AbstractFactoryBase<BodyPart>* bodyFactory;
        WaterPhysicsSystem* system;
};

#endif // WATERVOLUMEFACTORY_H
