#include "ParallaxLayer.h"
#include <Level/ParallaxSprite.h>

ParallaxLayer::ParallaxLayer(std::ifstream* file)
{
    //ctor
    unsigned short size;
    file->read((char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        sprites.push_back(new ParallaxSprite(file));
    }
}

ParallaxLayer::~ParallaxLayer()
{
    //dtor
    for (auto i = sprites.begin(); i != sprites.end(); i++)
    {
        delete *i;
    }
}

void ParallaxLayer::save(std::ofstream* file)
{
    file->write((const char*)&depth,sizeof(float));
    unsigned short size = sprites.size();
    file->write((const char*)&size,sizeof(unsigned short));
    for (unsigned short i = 0; i < size; i++)
    {
        sprites[i]->save(file);
    }
}
