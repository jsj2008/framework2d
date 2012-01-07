#ifndef BUBBLEFACTORY_H
#define BUBBLEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class Skin;
class BodyPart;

template <typename Bubble>
class BubbleFactory : public AbstractFactory<Entity, BubbleFactory<Bubble>>
{
    public:
        BubbleFactory();
        virtual ~BubbleFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return Bubble::name() + "Factory";
        }
    protected:
    private:
        AbstractFactoryBase<Skin>* skinFactory;
        AbstractFactoryBase<BodyPart>* bodyFactory;
};

#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Physics/PhysicsManager.h>
#include <Physics/BodyPart.h>
#include <Graphics/Skins/BubbleSkin.h>

template <typename Bubble>
BubbleFactory<Bubble>::BubbleFactory()
{
    //ctor
}

template <typename Bubble>
BubbleFactory<Bubble>::~BubbleFactory()
{
    //dtor
}
template <typename Bubble>
void BubbleFactory<Bubble>::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin", "BubbleSkinFactory");
    bodyFactory = loader->getFactory<BodyPart>("body", "SingleFixtureBodyFactory");
}

template <typename Bubble>
Entity* BubbleFactory<Bubble>::useFactory(FactoryParameters* _parameters)
{
    Entity* entity = new Bubble;
    entity->baseInit(skinFactory->use(_parameters, entity));

    BodyPart* physicsBody = bodyFactory->use(_parameters, entity);
    entity->setRootBody(physicsBody);

    return entity;
}

#endif // BUBBLEFACTORY_H
