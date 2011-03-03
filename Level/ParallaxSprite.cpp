#include "ParallaxSprite.h"
#include <Graphics/Contexts/TextureContext.h>
#include <Graphics/GraphicsManager.h>
#include <cstring>

ParallaxSprite::ParallaxSprite(std::ifstream* file)
{
    //ctor
    file->read((char*)&position,sizeof(Vec2f));
    file->read((char*)&size,sizeof(Vec2f));
    char string[32];
    file->read(string,32);
    texture = g_GraphicsManager.getTexture(string);
}

ParallaxSprite::~ParallaxSprite()
{
    //dtor
    texture->release();
}

void ParallaxSprite::save(std::ofstream* file)
{
    file->write((const char*)&position,sizeof(Vec2f));
    file->write((const char*)&size,sizeof(Vec2f));
    char string[32];
    strcpy(string,texture->getName());
    file->write(string,32);
}
