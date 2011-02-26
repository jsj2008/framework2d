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
    geometryDefs.push_back(*def);
    b2Body* body = g_FactoryList.useFactory(def,FactoryList::eConvexPolygonFactory)->mBody;
    bodyToGeometryDefTable[body] = geometryDefs.size()-1;
}
void Level::addCrate(CrateDef* def)
{
    crateDefs.push_back(*def);
    b2Body* body = g_FactoryList.useFactory(def,FactoryList::eCrateFactory)->mBody;
    bodyToCrateDefTable[body] = crateDefs.size()-1;
}
#define CREATE_FILE_NAME \
    char filename[strlen(name)+strlen("Levels/")+strlen(".lvl")];\
    strcpy(filename,"Levels/");\
    strcpy(filename+strlen("Levels/"),name);\
    strcpy(filename+strlen("Levels/")+strlen(name),".lvl")
void Level::removeBody(b2Body* body)
{
    auto result = bodyToGeometryDefTable.find(body);
    if (result != bodyToGeometryDefTable.end())
    {
        geometryDefs.erase(geometryDefs.begin() + result->second);
        bodyToGeometryDefTable.erase(body);
    }
    else
    {
        auto result = bodyToCrateDefTable.find(body);
        if (result != bodyToCrateDefTable.end())
        {
            crateDefs.erase(crateDefs.begin() + result->second);
            bodyToCrateDefTable.erase(body);
        }
    }
    g_PhysicsManager.destroyBody(body);
}
void Level::loadLevel()
{
    CREATE_FILE_NAME;
    ifstream file(filename,ios::binary);
    if(!file.is_open())
    {
        cout << "Error: File does not appear to exist, or maybe this program doesn't have filesystem rights" << filename << endl;
        throw -1;
    }
    unsigned short size;
    file.read((char*)&size,sizeof(unsigned short));
    geometryDefs.resize(size);
    file.read((char*)&geometryDefs[0],sizeof(ConvexGeometryDef)*size);
    Vec2f origin(0,0);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&geometryDefs[i],FactoryList::eConvexPolygonFactory)->mBody;
        bodyToGeometryDefTable[body] = i;
    }

    file.read((char*)&size,sizeof(unsigned short));
    crateDefs.resize(size);
    file.read((char*)&crateDefs[0],sizeof(CrateDef)*size);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&crateDefs[i],FactoryList::eCrateFactory)->mBody;
        bodyToCrateDefTable[body] = i;
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
    unsigned short size = geometryDefs.size();
    file.write((const char*)&size,sizeof(unsigned short));
    file.write((const char*)&geometryDefs[0],sizeof(ConvexGeometryDef)*size);
    geometryDefs.clear();
    for (auto i = bodyToCrateDefTable.begin(); i != bodyToCrateDefTable.end(); i++)
    {
        crateDefs[i->second].position = i->first->GetPosition();
    }
    size = crateDefs.size();
    file.write((const char*)&size,sizeof(unsigned short));
    file.write((const char*)&crateDefs[0],sizeof(CrateDef)*size);
}



















