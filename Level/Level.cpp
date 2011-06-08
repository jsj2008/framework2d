#include "Level.h"
#include <Factory/FactoryDefList.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>
#include <Graphics/Contexts/TextureContext.h>
#include <AbstractFactory/AbstractFactoryList.h>
#include <Level/ParallaxLayer.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
Level::Level(const char* _name)
{
    //ctor
    name = _name;
    loadLevel();
}

Level::~Level()
{
    //dtor
    saveLevel();
}
void Level::addBody(StandardFactoryDef def)
{
    b2Body* body = g_FactoryDefList.singleUse(def)->mBody;
    bodyToDefTable[body] = def;
    std::cout << bodyToDefTable.size() << std::endl;
}
void Level::addBody(const std::string& factory, FactoryParameters* parameters)
{
    b2Body* body = g_AbstractFactoryList.useFactory(factory, parameters)->mBody;
    table[body] = {factory,*parameters};
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
    auto crateIter = bodyToDefTable.find(bodyA);
    auto geometryIter = bodyToDefTable.find(bodyB);
    if (crateIter != bodyToDefTable.end() && geometryIter != bodyToDefTable.end())
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
    auto result = bodyToDefTable.find(body);
    if (result != bodyToDefTable.end())
    {
        bodyToDefTable.erase(body);
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
    std::vector<StandardFactoryDef> bodyDefs;
    unsigned short size;
    file.read((char*)&size,sizeof(unsigned short));
    bodyDefs.resize(size);
    file.read((char*)&bodyDefs[0],sizeof(StandardFactoryDef)*size);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryDefList.singleUse(bodyDefs[i])->mBody;
        bodyToDefTable[body] = bodyDefs[i];
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
    file.read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        parallaxLayers.push_back(new ParallaxLayer(&file));
    }
    for (auto i = parallaxLayers.begin(); i != parallaxLayers.end(); i++)
    {
        delete *i;
    }
    file.close();
    file.open("Level.txt");
    file >> size;
    //file.read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        std::string factory;
        file >> factory;
        FactoryParameters params;
        file >> params;
        b2Body* body = g_AbstractFactoryList.useFactory(factory, &params)->mBody;
        table[body] = {factory,params};
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
    unsigned short size = bodyToDefTable.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (auto i = bodyToDefTable.begin(); i != bodyToDefTable.end(); i++)
    {
        i->second.baseDef.position = i->first->GetPosition();
        i->second.baseDef.rotation = i->first->GetAngle();
        file.write((const char*)&i->second,sizeof(StandardFactoryDef));
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
    size = parallaxLayers.size();
    file.write((const char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        parallaxLayers[i]->save(&file);
    }
    for (auto i = parallaxLayers.begin(); i != parallaxLayers.end(); i++)
    {
        delete *i;
    }
    parallaxLayers.clear();
    bodyToDefTable.clear();
    for (auto i = jointToDefTable.begin(); i != jointToDefTable.end(); i++)
    {
        delete i->second;
    }
    jointToDefTable.clear();
    /**
    file.read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        std::string name;
        file >> name;
        FactoryParameters params;
        file >> params;
        params.clear();
        b2Body* body = g_AbstractFactoryList.useFactory(name, &params)->mBody;
        table[body] = {name,params};
    }
    */
    file.close();
    file.open("Level.txt");
    size = table.size();
    file << size;
    file << ' ';
    //file.write((const char*)&size,sizeof(unsigned short));
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

















