#include "Level.h"
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>
#include <Graphics/Contexts/TextureContext.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Level/ParallaxLayer.h>
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
Level::Level(const char* _name)
{
    //ctor
    name = _name;
    world = new PhysicsManager();
}

Level::~Level()
{
    //dtor
    saveLevel();
}
Entity* Level::addBody(const std::string& factory, FactoryParameters* parameters)
{
    Entity* entity = AbstractFactories::global().useFactory<Entity>(factory, parameters);
    table[entity] = {factory,*parameters};
    return entity;
}
void Level::addJoint(b2JointDef* def)
{
    b2JointDef* copy;
    switch (def->type)
    {
        case e_distanceJoint:
        {
            copy = new b2DistanceJointDef(*(b2DistanceJointDef*)def);
            break;
        }
        case e_revoluteJoint:
        {
            copy = new b2RevoluteJointDef(*(b2RevoluteJointDef*)def);
            break;
        }
        case e_prismaticJoint:
        {
            copy = new b2PrismaticJointDef(*(b2PrismaticJointDef*)def);
            break;
        }
        case e_pulleyJoint:
        {
            copy = new b2PulleyJointDef(*(b2PulleyJointDef*)def);
            break;
        }
        case e_gearJoint:
        {
            copy = new b2GearJointDef(*(b2GearJointDef*)def);
            break;
        }
        case e_lineJoint:
        {
            copy = new b2LineJointDef(*(b2LineJointDef*)def);
            break;
        }
        case e_weldJoint:
        {
            copy = new b2WeldJointDef(*(b2WeldJointDef*)def);
            break;
        }
        case e_frictionJoint:
        {
            copy = new b2FrictionJointDef(*(b2FrictionJointDef*)def);
            break;
        }
        case e_unknownJoint:
        case e_mouseJoint:
        default:
        {
            std::cout << "Unrecognised joint type" << std::endl;
            throw -1;
        }
    }
    Entity* bodyA = static_cast<Entity*>(def->bodyA->GetUserData());
    Entity* bodyB = static_cast<Entity*>(def->bodyB->GetUserData());
    auto crateIter = table.find(bodyA);
    auto geometryIter = table.find(bodyB);
    if (crateIter != table.end() && geometryIter != table.end())
    {
        jointToDefTable[world->createJoint(copy)] = copy;
    }
}
#define CREATE_FILE_NAME \
    char filename[strlen(name)+strlen("Resources/Levels/")+strlen(".lvl")];\
    strcpy(filename,"Resources/Levels/");\
    strcpy(filename+strlen("Resources/Levels/"),name);\
    strcpy(filename+strlen("Resources/Levels/")+strlen(name),".lvl")
void Level::removeBody(Entity* body, std::pair<std::string,FactoryParameters>* _saveConstruction)
{
    auto result = table.find(body);
    if (result != table.end())
    {
        if (_saveConstruction != nullptr)
        {
            _saveConstruction->first = result->second.first;
            _saveConstruction->second = result->second.second;
        }
        table.erase(body);
    }
    delete body;
}
void Level::removeJoint(b2Joint* joint)
{
    jointToDefTable.erase(joint);
}
#include <vector>
unsigned int getJointDefSize(b2JointType type);
void Level::loadLevel()
{
    ifstream file;
    file.open("Level.txt");
    unsigned short size;
    file >> size;
    for (unsigned short i = 0; i < size; i++)
    {
        std::string factory;
        file >> factory;
        FactoryParameters params;
        file >> params;
        Entity* body = AbstractFactories::global().useFactory<Entity>(factory, &params);
        table[body] = {factory,params};
    }
}
void Level::saveLevel()
{
    ofstream file;
    file.open("Level.txt");
    unsigned short size = table.size();
    file << size;
    file << ' ';
    for (auto i = table.begin(); i != table.end() ;i++)
    {
        std::string factory = i->second.first;
        file << factory;
        file << ' ';
        FactoryParameters params = i->second.second;
        file << params;
        file << ' ';
    }
}
unsigned int getJointDefSize(b2JointType type)
{
    switch (type)
    {
        case e_distanceJoint:
        {
            return sizeof(b2DistanceJointDef);
        }
        case e_revoluteJoint:
        {
            return sizeof(b2RevoluteJointDef);
        }
        case e_prismaticJoint:
        {
            return sizeof(b2PrismaticJointDef);
        }
        case e_pulleyJoint:
        {
            return sizeof(b2PulleyJointDef);
        }
        case e_gearJoint:
        {
            return sizeof(b2GearJointDef);
        }
        case e_lineJoint:
        {
            return sizeof(b2LineJointDef);
        }
        case e_weldJoint:
        {
            return sizeof(b2WeldJointDef);
        }
        case e_frictionJoint:
        {
            return sizeof(b2FrictionJointDef);
        }
        case e_unknownJoint:
        case e_mouseJoint:
        default:
        {
            cout << "Invalid joint to get size of" << endl;
            throw -1;
        }

    }
    return 0;
}
bool Level::update()
{
    return world->update();
}
#include <GL/gl.h>
void Level::render()
{
    world->render();
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        b2Joint* joint = i->first;
        Vec2f point = joint->GetAnchorA();
        glVertex2f(point.x,point.y);
        point = joint->GetAnchorB();
        glVertex2f(point.x,point.y);
    }
    glEnd();
    glColor3f(1,1,1);
}

















