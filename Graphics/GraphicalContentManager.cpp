#include "GraphicalContentManager.h"
#include <GL/gl.h>
#include <SDL/SDL_video.h>

GraphicalContentManager::GraphicalContentManager()
{
    //ctor
    textures = new TextureContext[1]{"player.bmp"};
}

GraphicalContentManager::~GraphicalContentManager()
{
    //dtor
}
TextureContext* GraphicalContentManager::getTexture(unsigned int reference)
{
    textures[reference].grab();
    return textures + reference;
}




























