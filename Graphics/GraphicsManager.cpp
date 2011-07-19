#include "GraphicsManager.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Graphics/Camera/Camera.h>
#include <cassert>
#include <iostream>
#include <Graphics/Skins/AllSkins.h>
#include <Graphics/Sprites/SpriteList.h>
#include <Log/GameConsole.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
GraphicsManager g_GraphicsManager;
bool function(const CEGUI::EventArgs& e);
bool function(const CEGUI::EventArgs& e)
{
    std::cout << "Jumped" << std::endl;
    return true;
}
GameConsole* g_Console; /// FIXME
GraphicsManager::GraphicsManager()
{
    //ctor
    int result = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        assert(result == 0);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL,0);
    resize(Vec2i(1200,800));

    CEGUI::OpenGLRenderer::bootstrapSystem();
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
    (CEGUI::System::getSingleton().getResourceProvider());

    rp->setResourceGroupDirectory("schemes", "Resources/CEGUI/schemes/");
    rp->setResourceGroupDirectory("imagesets", "Resources/CEGUI/imagesets/");
    rp->setResourceGroupDirectory("fonts", "Resources/CEGUI/fonts/");
    rp->setResourceGroupDirectory("layouts", "Resources/CEGUI/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "Resources/CEGUI/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", "Resources/CEGUI/lua_scripts/");
    rp->setResourceGroupDirectory("schemas", "Resources/CEGUI/xml_schemas/");

    CEGUI::Imageset::setDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");

    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme", "schemes");
    CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );

    CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow");
    CEGUI::System::getSingleton().setGUISheet(myRoot);
    CEGUI::Window *myWindow = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditorRoot.layout");
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(myWindow);

    g_Console = new GameConsole();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
	glClearColor(0,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(3);
    glPointSize(5);
    glColor4f(1,1,1,1);

    mCamera = 0;
    spriteList = new SpriteList();
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
    glOrtho(0, resolution.x, resolution.y, 0, 0, 1);
    gluLookAt(0,0,1,0,0,-1,0,1,0);

    glMatrixMode(GL_MODELVIEW);
}

void GraphicsManager::endScene()
{
    CEGUI::System::getSingleton().renderGUI();
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
        assert(screen != nullptr);

    glViewport(0,0,resolution.x,resolution.y);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, resolution.x, resolution.y, 0, 0, 1); // Parralel projection (no 3d or depth test)
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
void GraphicsManager::addSprite(Sprite* _sprite)
{
    spriteList->addSprite(_sprite);
}
void GraphicsManager::deleteSprite(Sprite* _sprite)
{
    spriteList->deleteSprite(_sprite);
}

