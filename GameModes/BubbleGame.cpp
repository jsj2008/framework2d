#include "BubbleGame.h"

BubbleGame::BubbleGame()
{
    //ctor
}

BubbleGame::~BubbleGame()
{
    //dtor
}

void BubbleGame::buttonUp(Vec2i mouse, unsigned char button)
{
    Vec2f position = startPos.ScreenToWorldSpace();
    float radius = (position-mouse.ScreenToWorldSpace()).Length();
    if (radius != 0.0f)
    {
        FactoryParameters parameters;
        parameters.add<Vec2f>("position",position);
        parameters.add<float>("radius",radius);
        parameters.add<std::string>("materialName","defaultBubble");
        std::string factory;
        switch (type)
        {
            case Bubble::eSuctionBubbleType:
            {
                factory = "suctionBubble";
                break;
            }
            case Bubble::eUpwardsGravityBubbleType:
            {
                factory = "upwardsGravityBubble";
                break;
            }
            case Bubble::eBubbleTypesMax:
            default:
            {
                throw -1;
            }
        }
        AbstractFactories::global().useFactory<Entity>(factory,&parameters);
    }
}
