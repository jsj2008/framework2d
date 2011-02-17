#include "GraphicsManager.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Graphics/Camera.h>
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
    resize(800,600);

    glDisable(GL_DEPTH_TEST);
	glClearColor(1,0,0,0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

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
        mCamera->updateView(xRes, yRes);
    }
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, xRes, yRes, 0, 0, 1); // Parralel projection (no 3d or depth test)

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
void GraphicsManager::resize(int newXRes, int newYRes)
{
    xRes = newXRes;
    yRes = newYRes;
    SDL_Surface* screen = SDL_SetVideoMode(xRes, yRes, 0, SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
        assert(screen != NULL);

    glViewport(0,0,xRes,yRes);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, xRes, yRes, 0, 0, 1); // Parralel projection (no 3d or depth test)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int GraphicsManager::getViewX()
{
    return mCamera->getViewX();
}
int GraphicsManager::getViewY()
{
    return mCamera->getViewY();
}
Skin* GraphicsManager::skinFactory(GraphicsFactoryDef& def)
{
    Skin* returnValue;
    switch (def.type)
    {
        case eStaticSkinType:
        {
            returnValue = new StaticSkin(def.graphicsDef.staticSkinDef.width,def.graphicsDef.staticSkinDef.height);
            returnValue->texture = mContentManager.getTexture(def.graphicsDef.staticSkinDef.texture);
            break;
        }
        case eConvexPolygonSkinType:
        {
            returnValue = new ConvexPolygonSkin(def.graphicsDef.convexPolygonSkinDef.points,def.graphicsDef.convexPolygonSkinDef.numPoints);
            returnValue->texture = mContentManager.getTexture(def.graphicsDef.convexPolygonSkinDef.texture);
            break;
        }
        case eSkinTypeMax:
        {
            throw "Enum out of range";
        }
    }
    return returnValue;
}




