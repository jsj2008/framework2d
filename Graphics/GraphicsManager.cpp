#include "GraphicsManager.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Graphics/Camera/Camera.h>
#include <cassert>
#include <iostream>
#include <Graphics/Skins/AllSkins.h>
#include <Input/InputManager.h>
GraphicsManager g_GraphicsManager;

GraphicsManager::GraphicsManager()
:mFontRenderer("FreeSans",16)
{
    //ctor
    int result = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        assert(result == 0);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL,0);
    resize(Vec2i(800,600));

    glDisable(GL_DEPTH_TEST);
	glClearColor(1,0,0,0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glLineWidth(3);
    glPointSize(5);

    mCamera = 0;
}

GraphicsManager::~GraphicsManager()
{
    //dtor
}

void GraphicsManager::beginScene()
{
    if (mCamera != 0)
    {
        mCamera->updateView(resolution);
    }
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, resolution.x, resolution.y, 0, 0, 1); // Parralel projection (no 3d or depth test)

    glMatrixMode(GL_MODELVIEW);
}

void GraphicsManager::endScene()
{
	glFlush();
    glFinish();
	SDL_GL_SwapBuffers();
    GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
	    std::cout << (const char*)gluErrorString(errorCode) << std::endl;
	    throw -1;
	}
}
void GraphicsManager::resize(Vec2i newResolution)
{
    resolution = newResolution;
    SDL_Surface* screen = SDL_SetVideoMode(resolution.x, resolution.y, 0, SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
        assert(screen != NULL);

    glViewport(0,0,resolution.x,resolution.y);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, resolution.x, resolution.y, 0, 0, 1); // Parralel projection (no 3d or depth test)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    g_InputManager.changeResolution(newResolution);
}
const Vec2i& GraphicsManager::getView()
{
    return mCamera->getView();
}
float GraphicsManager::getPixelsPerMeter()
{
    return mCamera->getPixelsPerMeter();
}


