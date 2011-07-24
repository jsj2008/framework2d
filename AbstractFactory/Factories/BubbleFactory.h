#ifndef BUBBLEFACTORY_H
#define BUBBLEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;

template <typename Bubble>
class BubbleFactory : public AbstractFactory<Entity, BubbleFactory<Bubble>>
{
    public:
        BubbleFactory();
        virtual ~BubbleFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return Bubble::name() + "Factory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
};

#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/BubbleSkin.h>

template <typename Bubble>
BubbleFactory<Bubble>::BubbleFactory()
{
    //ctor
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
}

template <typename Bubble>
BubbleFactory<Bubble>::~BubbleFactory()
{
    //dtor
}
template <typename Bubble>
void BubbleFactory<Bubble>::init(FactoryLoader* loader, AbstractFactories* factories)
{
}

template <typename Bubble>
Entity* BubbleFactory<Bubble>::useFactory(FactoryParameters* parameters)
{
    Skin* skin = new BubbleSkin(shapeDef.m_radius);
    Entity* entity = new Bubble(skin);

    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));
    shapeDef.m_radius = parameters->get<float>("radius",1.0f);
    bodyDef.userData = (void*)entity;
    b2Body* body = g_PhysicsManager.createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);

    setMaterial(skin,parameters->get<std::string>("materialName",""));
    return entity;
}

#endif // BUBBLEFACTORY_H
