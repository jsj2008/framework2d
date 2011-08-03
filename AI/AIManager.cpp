#include "AIManager.h"
#include "AllBrains.h"
#include <Game.h>
#include <GameModes/GameMode.h>
#include <Box2D/Box2D.h>
#include <AI/Pathfinding/Paths.h>
AIManager g_AIManager;
AIManager::AIManager()
{
    //ctor
}

AIManager::~AIManager()
{
    //dtor
}

void AIManager::init(PhysicsManager* _physicsManager)
{
    playerNode = Node(0,0);
    pathfinding = new Pathfinding(_physicsManager);
}

void AIManager::path(Node start, Node end, std::stack<PathInstruction>& instructions)
{
    return paths->path(start,end, instructions);
}

void AIManager::setPlayerNode(const Vec2f& _playerPosition)
{
    playerNode = paths->findClosestNode(_playerPosition);
}

Node AIManager::findClosestNode(const Vec2f& position)
{
    return paths->findClosestNode(position);
}
