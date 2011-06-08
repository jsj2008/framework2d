#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Entities/Bubble.h>
#include <Factory/FactoryList.h>
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <AI/PlayerInputBrain.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactoryList.h>

PlayMode::PlayMode()
{
    //ctor
    type = Bubble::eSuctionBubbleType;
    mCamera = NULL;
}

PlayMode::~PlayMode()
{
    //dtor
}

void PlayMode::start(unsigned char button)
{

}
void PlayMode::mouseMove(Vec2i mouse)
{

}
void PlayMode::buttonUp(Vec2i mouse, unsigned char button)
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
        g_AbstractFactoryList.useFactory(factory,&parameters);
    }
}
void PlayMode::setBody(b2Body* body, PlayerInputBrain* _playerBrain)
{
    mCamera = new PhysicsCamera(body);
    playerBrain = _playerBrain;
}

bool PlayMode::activate(const CEGUI::EventArgs& args)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != NULL)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    assert(playerBrain);
    playerBrain->activate();
    return true;
}

