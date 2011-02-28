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
        case e_unknownJoint:
        case e_mouseJoint:
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
void Level::removeJoint(b2Joint* joint)
{
    jointToDefTable.erase(joint);
}
#include <vector>
unsigned int getJointDefSize(b2JointType type);
void Level::loadLevel()
{
    CREATE_FILE_NAME;
    std::vector<b2Body*> readLocations;
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
        readLocations.push_back(body);
    }

    std::vector<CrateDef> crateDefs;
    file.read((char*)&size,sizeof(unsigned short));
    crateDefs.resize(size);
    file.read((char*)&crateDefs[0],sizeof(CrateDef)*size);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&crateDefs[i],FactoryList::eCrateFactory)->mBody;
        bodyToCrateDefTable[body] = crateDefs[i];
        readLocations.push_back(body);
    }
    file.read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        unsigned short bodyA, bodyB;
        file.read((char*)&(bodyA),sizeof(unsigned short));
        file.read((char*)&(bodyB),sizeof(unsigned short));
        b2JointType type;
        file.read((char*)&(type),sizeof(b2JointType));
        switch (type)
        {
            case e_distanceJoint:
            {
                Vec2f worldAnchorA;
                Vec2f worldAnchorB;
                file.read((char*)&(worldAnchorA),sizeof(Vec2f));
                file.read((char*)&(worldAnchorB),sizeof(Vec2f));
                b2DistanceJointDef def;
                def.Initialize(readLocations[bodyA],readLocations[bodyB],worldAnchorA, worldAnchorB);
                file.read((char*)&(def.collideConnected),sizeof(bool));
                file.read((char*)&(def.frequencyHz),sizeof(float));
                file.read((char*)&(def.dampingRatio),sizeof(float));
                addJoint(&def);
                break;
            }
            case e_revoluteJoint:
            case e_prismaticJoint:
            case e_pulleyJoint:
            case e_gearJoint:
            case e_lineJoint:
            case e_weldJoint:
            case e_frictionJoint:
            case e_unknownJoint:
            case e_mouseJoint:
            default:
            {
                cout << "Invalid joint to load" << endl;
                throw -1;
            }
        }
    }
}
void Level::saveLevel()
{
    std::unordered_map<b2Body*, unsigned short> writeLocations;
    unsigned short writeLocation = 0;
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
        writeLocations[i->first] = writeLocation;
        writeLocation++;
    }

    size = bodyToCrateDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = bodyToCrateDefTable.begin(); i != bodyToCrateDefTable.end(); i++)
    {
        i->second.position = i->first->GetPosition();
        file.write((const char*)&i->second,sizeof(CrateDef));
        writeLocations[i->first] = writeLocation;
        writeLocation++;
    }
    size = jointToDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        b2JointType type = i->first->GetType();
        if (type != e_distanceJoint) continue;
        auto bodyA = writeLocations.find(i->first->GetBodyA());
        auto bodyB = writeLocations.find(i->first->GetBodyB());
        if (bodyA == writeLocations.end() || bodyB == writeLocations.end()) continue;
        file.write((const char*)&(bodyA->second),sizeof(unsigned short));
        file.write((const char*)&(bodyB->second),sizeof(unsigned short));
        file.write((const char*)&(type),sizeof(b2JointType));
        switch (type)
        {
            case e_distanceJoint:
            {
                Vec2f worldAnchorA = i->first->GetAnchorA();
                Vec2f worldAnchorB = i->first->GetAnchorB();
                file.write((const char*)&(worldAnchorA),sizeof(Vec2f));
                file.write((const char*)&(worldAnchorB),sizeof(Vec2f));
                b2DistanceJointDef* distanceCast = (b2DistanceJointDef*)i->second;
                file.write((const char*)&(distanceCast->collideConnected),sizeof(bool));
                file.write((const char*)&(distanceCast->frequencyHz),sizeof(float));
                file.write((const char*)&(distanceCast->dampingRatio),sizeof(float));
                break;
            }
            case e_revoluteJoint:
            case e_prismaticJoint:
            case e_pulleyJoint:
            case e_gearJoint:
            case e_lineJoint:
            case e_weldJoint:
            case e_frictionJoint:
            case e_unknownJoint:
            case e_mouseJoint:
            default:
            {
                cout << "Invalid joint to save" << endl;
                throw -1;
            }
        }
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
#include <GL/gl.h>
#include <Types/Vec2i.h>
void Level::tempRender()
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        b2Joint* joint = i->first;
        Vec2f point = joint->GetAnchorA();
        //point.worldToScreenSpace();
        glVertex2f(point.x,point.y);
        point = joint->GetAnchorB();
        glVertex2f(point.x,point.y);
    }
    glEnd();
    glColor3f(1,1,1);
}

















