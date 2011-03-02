#include "FontRenderer.h"
#include <Graphics/Primitives/FontPrimitive.h>
#include <iostream>

FontRenderer::FontRenderer(const char* fontname, int pointSize)
{
    //ctor
    static bool ttfInitialised = false;
    if (!ttfInitialised)
    {
        if (TTF_Init() == -1)
        {
            std::cout << "Unable to initialise SDL_ttf" << std::endl;
            throw -1;
        }
        ttfInitialised = true;
        std::string filename("Resources/Graphics/Fonts/");
        filename.append(fontname);
        filename.append(".otf");
        font = TTF_OpenFont(filename.c_str(), pointSize);
    }
}

FontRenderer::~FontRenderer()
{
    //dtor
}
int nextpoweroftwo(int x)
{
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}
unsigned int surfaceToTexture(SDL_Surface* surface);
FontPrimitive* FontRenderer::renderFont(const char* string, int wrap)
{
    if (string[0] == '\0')
    {
        return NULL;
    }
    /*auto iter = fontMap.find(string);
    if (iter != fontMap.end())
    {
        return iter->second;
    }
    else*/
    {
        SDL_Colour colour = {0,255,0,1};
        SDL_Surface* initial = TTF_RenderText_Blended(font,string,colour);
        unsigned int texture = surfaceToTexture(initial);

        FontPrimitive* primitive = new FontPrimitive(string,texture,Vec2i(initial->w,initial->h));
        //fontMap[primitive->getString()] = primitive;

        SDL_FreeSurface(initial);
        return primitive;
    }
}