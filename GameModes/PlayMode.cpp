#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Entities/Bubble.h>
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <AI/PlayerInputBrain.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactories.h>

PlayMode::PlayMode()
{
    //ctor
    type = Bubble::eSuctionBubbleType;
    mCamera = nullptr;
    playerBrain = nullptr;
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
        AbstractFactories::global().useFactory<Entity>(factory,&parameters);
    }
}
void PlayMode::setCamera(Camera* _camera)
{
    mCamera = _camera;
}
void PlayMode::setPlayerBrain(PlayerInputBrain* _playerBrain)
{
    playerBrain = _playerBrain;
}

bool PlayMode::activate(const CEGUI::EventArgs& args)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != nullptr)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    assert(playerBrain);
    playerBrain->activate();
    return true;
}

