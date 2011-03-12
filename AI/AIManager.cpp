#include "AIManager.h"
#include "AllBrains.h"
#include <Game.h>
#include <GameModes/GameMode.h>
#include <Box2D/Box2D.h>
AIManager g_AIManager;
AIManager::AIManager()
{
    //ctor
    playerSegment = NULL;
}

AIManager::~AIManager()
{
    //dtor
}

void AIManager::setPlayerSegment(b2Body* body)
{
    const Vec2f& playerPosition = body->GetPosition();
    playerSegment = pathfinding.findClosestPath(playerPosition);
}
