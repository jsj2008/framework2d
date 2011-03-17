#include "AIManager.h"
#include "AllBrains.h"
#include <Game.h>
#include <GameModes/GameMode.h>
#include <Box2D/Box2D.h>
#include <AI/Paths/Paths.h>
AIManager g_AIManager;
AIManager::AIManager()
{
    //ctor
    playerNode = Node(NULL,0);
    pathfinding = new Pathfinding;
}

AIManager::~AIManager()
{
    //dtor
}

void AIManager::path(Node start, Node end, std::stack<PathInstruction>& instructions)
{
    return paths->path(start,end, instructions);
}

void AIManager::setPlayerNode(b2Body* body)
{
    const Vec2f& playerPosition = body->GetPosition();
    playerNode = paths->findClosestNode(playerPosition);
}

Node AIManager::findClosestNode(const Vec2f& position)
{
    return paths->findClosestNode(position);
}
