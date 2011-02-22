#include "GraphicsManager.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Graphics/Camera/Camera.h>
#include <cassert>
#include <Graphics/Skins/AllSkins.h>
GraphicsManager g_GraphicsManager;
GraphicsFactoryDef::GraphicsFactoryDef(SkinType _type)
:graphicsDef(_type)
{
    type = _type;
}
GraphicsFactoryDef::GraphicsDef::GraphicsDef(SkinType _type)
{
    switch (_type)
    {
        case eStaticSkinType:
        {
            staticSkinDef.texture = 0;
            staticSkinDef.width = staticSkinDef.height = 50;
            break;
        }
        case eConvexPolygonSkinType:
        {
            convexPolygonSkinDef.texture = 0;
            convexPolygonSkinDef.numPoints = 0;
        }
        case eSkinTypeMax:
        {
            throw "Enum out of range";
        }
    }
}

GraphicsManager::GraphicsManager()
{
    //ctor
    int result = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        assert(result == 0);
    resize(Vec2i(800,600));

    glDisable(GL_DEPTH_TEST);
	glClearColor(1,0,0,0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glLineWidth(5);
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
	    throw (const char*)gluErrorString(errorCode);
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
}
const Vec2i& GraphicsManager::getView()
{
    return mCamera->getView();
}
float GraphicsManager::getPixelsPerMeter()
{
    return mCamera->getPixelsPerMeter();
}
Skin* GraphicsManager::skinFactory(GraphicsFactoryDef& def)
{
    Skin* returnValue = NULL;
    switch (def.type)
    {
        case eStaticSkinType:
        {
            returnValue = new StaticSkin(def.graphicsDef.staticSkinDef.width,def.graphicsDef.staticSkinDef.height);
            returnValue->material = mContentManager.getMaterial(def.graphicsDef.staticSkinDef.texture);
            break;
        }
        case eConvexPolygonSkinType:
        {
            returnValue = new ConvexPolygonSkin(def.graphicsDef.convexPolygonSkinDef.points,def.graphicsDef.convexPolygonSkinDef.numPoints);
            returnValue->material = mContentManager.getMaterial(def.graphicsDef.convexPolygonSkinDef.texture);
            break;
        }
        case eSkinTypeMax:
        {
            throw "Enum out of range";
        }
    }
    return returnValue;
}




