#include "Level.h"
#include <Factory/ConvexGeometryDef.h>
#include <Factory/FactoryList.h>
#include <Physics/PhysicsManager.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
Level::Level()
{
    name = NULL;
}
Level::Level(const char* _name)
{
    //ctor
    name = _name;
    loadLevel();
}

Level::~Level()
{
    //dtor
    if (name == NULL)
    {
        name = "default";
    }
    saveLevel();
}
void Level::addPlatform(ConvexGeometryDef* def)
{
    b2Body* body = g_FactoryList.useFactory(def,FactoryList::eConvexPolygonFactory)->mBody;
    bodyToGeometryDefTable[body] = *def;
}
void Level::addCrate(CrateDef* def)
{
    b2Body* body = g_FactoryList.useFactory(def,FactoryList::eCrateFactory)->mBody;
    bodyToCrateDefTable[body] = *def;
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
        default:
        {
            std::cout << "Unrecognised joint type" << std::endl;
            throw -1;
        }
    }
    b2Body* bodyA = def->bodyA;
    b2Body* bodyB = def->bodyB;
    auto crateIter = bodyToCrateDefTable.find(bodyA);
    auto geometryIter = bodyToGeometryDefTable.find(bodyB);
    if (crateIter == bodyToCrateDefTable.end())
    {
        crateIter = bodyToCrateDefTable.find(bodyB);
        geometryIter = bodyToGeometryDefTable.find(bodyA);
    }
    if (crateIter != bodyToCrateDefTable.end() && geometryIter != bodyToGeometryDefTable.end())
    {
        jointToDefTable[g_PhysicsManager.createJoint(copy)] = copy;
    }
}
#define CREATE_FILE_NAME \
    char filename[strlen(name)+strlen("Resources/Levels/")+strlen(".lvl")];\
    strcpy(filename,"Resources/Levels/");\
    strcpy(filename+strlen("Resources/Levels/"),name);\
    strcpy(filename+strlen("Resources/Levels/")+strlen(name),".lvl")
void Level::removeBody(b2Body* body)
{
    auto result = bodyToGeometryDefTable.find(body);
    if (result != bodyToGeometryDefTable.end())
    {
        bodyToGeometryDefTable.erase(body);
    }
    else
    {
        auto result = bodyToCrateDefTable.find(body);
        if (result != bodyToCrateDefTable.end())
        {
            bodyToCrateDefTable.erase(body);
        }
    }
    g_PhysicsManager.destroyBody(body);
}
#include <vector>
unsigned int getJointDefSize(b2JointType type);
void Level::loadLevel()
{
    CREATE_FILE_NAME;
    ifstream file(filename,ios::binary);
    if(!file.is_open())
    {
        cout << "Error: File does not appear to exist, or maybe this program doesn't have filesystem rights" << filename << endl;
        return;
    }
    std::vector<ConvexGeometryDef> geometryDefs;
    unsigned short size;
    file.read((char*)&size,sizeof(unsigned short));
    geometryDefs.resize(size);
    file.read((char*)&geometryDefs[0],sizeof(ConvexGeometryDef)*size);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&geometryDefs[i],FactoryList::eConvexPolygonFactory)->mBody;
        bodyToGeometryDefTable[body] = geometryDefs[i];
    }

    std::vector<CrateDef> crateDefs;
    file.read((char*)&size,sizeof(unsigned short));
    crateDefs.resize(size);
    file.read((char*)&crateDefs[0],sizeof(CrateDef)*size);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&crateDefs[i],FactoryList::eCrateFactory)->mBody;
        bodyToCrateDefTable[body] = crateDefs[i];
    }

    file.read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        b2JointType type;
        file.read((char*)&type,sizeof(b2JointType));
        unsigned int size = getJointDefSize(type);
        b2JointDef* def = (b2JointDef*)new char[size-sizeof(b2JointType)];
        file.read((char*)def+sizeof(b2JointType),size);
        def->type = type;
        {
            auto iter = bodyToCrateDefTable.begin();
            for (unsigned int i = 0; i < def->bodyA; i++)iter++;
            def->bodyA = iter->first;
        }
        {
            auto iter = bodyToGeometryDefTable.begin();
            for (unsigned int i = 0; i < def->bodyB; i++)iter++;
            def->bodyB = iter->first;
        }
        addJoint(def);
    }
}
void Level::saveLevel()
{
    CREATE_FILE_NAME;
    ofstream file;
    file.open(filename,ios::binary);
    if(!file.is_open())
    {
        cout << "Error: File failed to open for writing, make sure the directory already exists, or maybe this program just doesn't have filesystem rights" << filename << endl;
        throw -1;
    }
    unsigned short size = bodyToGeometryDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = bodyToGeometryDefTable.begin(); i != bodyToGeometryDefTable.end(); i++)
    {
        file.write((const char*)&i->second,sizeof(ConvexGeometryDef));
    }

    size = bodyToCrateDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = bodyToCrateDefTable.begin(); i != bodyToCrateDefTable.end(); i++)
    {
        i->second.position = i->first->GetPosition();
        file.write((const char*)&i->second,sizeof(CrateDef));
    }

    size = jointToDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        b2Body* bodyA = i->second->bodyA;
        b2Body* bodyB = i->second->bodyB;
        auto crateIter = bodyToCrateDefTable.find(bodyA);
        auto geometryIter = bodyToGeometryDefTable.find(bodyB);
        if (crateIter == bodyToCrateDefTable.end())
        {
            crateIter = bodyToCrateDefTable.find(bodyB);
            geometryIter = bodyToGeometryDefTable.find(bodyA);
        }
        if (crateIter == bodyToCrateDefTable.end() || geometryIter == bodyToGeometryDefTable.end())
        {
            assert(false);
        }
        unsigned int position = 0;
        for (auto crateFind = bodyToCrateDefTable.begin(); crateFind != crateIter; crateFind++)
        {
            position++;
        }
        i->second->bodyA = position;
        position = 0;
        for (auto geometryFind = bodyToGeometryDefTable.begin(); geometryFind != geometryIter; geometryFind++)
        {
            position++;
        }
        i->second->bodyB = position;
        file.write((const char*)i->second,getJointDefSize(i->second->type));
    }
    bodyToCrateDefTable.clear();
    bodyToGeometryDefTable.clear();
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        delete i->second;
    }
    jointToDefTable.clear();
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
    }
    return 0;
}


















