#include "LevelManager.h"
#include <Factory/ConvexGeometryDef.h>
#include <Factory/FactoryList.h>
#include <Physics/PhysicsManager.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
LevelManager g_LevelManager;
LevelManager::LevelManager()
{
    //ctor
}

LevelManager::~LevelManager()
{
    //dtor
}
void LevelManager::addPlatform(ConvexGeometryDef* def)
{
    defs.push_back(*def);
    g_FactoryList.useFactory(def,FactoryList::eConvexPolygonFactory);
}
#define CREATE_FILE_NAME \
    char filename[strlen(name)+strlen("Levels/")+strlen(".lvl")];\
    strcpy(filename,"Levels/");\
    strcpy(filename+strlen("Levels/"),name);\
    strcpy(filename+strlen("Levels/")+strlen(name),".lvl")
void LevelManager::removeBody(b2Body* body)
{
    auto result = bodyToDefTable.find(body);
    if (result != bodyToDefTable.end())
    {
        defs.erase(defs.begin() + result->second);
        bodyToDefTable.erase(body);
    }
    g_PhysicsManager.destroyBody(body);
    /*g_PhysicsManager.clear();
    bodyToDefTable.clear();
    Vec2f origin(0,0);
    for (unsigned int i = 0; i < defs.size(); i++)
    {
        b2Body* body = g_EntityFactory.createEntity(defs[i],origin)->mBody;
        bodyToDefTable[body] = i;
    }*/
}
void LevelManager::loadLevel(const char* name)
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
    defs.resize(size);
    file.read((char*)&defs[0],sizeof(ConvexGeometryDef)*size);
    Vec2f origin(0,0);
    for (unsigned short i = 0; i < size; i++)
    {
        b2Body* body = g_FactoryList.useFactory(&defs[i],FactoryList::eConvexPolygonFactory)->mBody;
        //b2Body* body = g_FactoryList.factory(&file,origin)->mBody;
        bodyToDefTable[body] = i;
    }
}
void LevelManager::saveLevel(const char* name)
{
    CREATE_FILE_NAME;
    ofstream file;
    file.open(filename,ios::binary);
    if(!file.is_open())
    {
        cout << "Error: File failed to open for writing, make sure the directory already exists, or maybe this program just doesn't have filesystem rights" << filename << endl;
        throw -1;
    }
    unsigned short size = defs.size();
    file.write((const char*)&size,sizeof(unsigned short));
    file.write((const char*)&defs[0],sizeof(ConvexGeometryDef)*size);
    defs.clear();
}
