#include "TextureContext.h"
#include <cassert>
#include <GL/gl.h>
#include <SDL/SDL_video.h>

TextureContext::TextureContext(const char* _textureName)
:GraphicalContext(_textureName)
{
    //ctor
}

TextureContext::~TextureContext()
{
    //dtor
}

void TextureContext::assertDelete()
{
    assert(referenceCount == 0);
}
void TextureContext::bind()
{
    glBindTexture(GL_TEXTURE_2D,texture);
}
void TextureContext::unload()
{
    glDeleteTextures(1,&texture);
}
#define GL_BGRA                                 0x80E1
#define GL_BGR                                  0x80E0
void TextureContext::load()
{
	texture = 0;
	if (name[0] != '\0')
	{
        char fullFileName[strlen("Resources/Graphics/Textures/")+MAX_NAME+strlen(".bmp")];
        memcpy(fullFileName,"Resources/Graphics/Textures/",strlen("Resources/Graphics/Textures/"));
        strcpy(fullFileName+strlen("Resources/Graphics/Textures/"),name);
        strcpy(fullFileName+strlen("Resources/Graphics/Textures/")+strlen(name),".bmp");
        SDL_Surface *surface = SDL_LoadBMP(fullFileName);
        if (surface)
        {
            GLenum texture_format;
            GLint  nOfColors;

            nOfColors = surface->format->BytesPerPixel;
            if (nOfColors == 4)     // contains an alpha channel
            {
                if (surface->format->Rmask == 0x000000ff)
                    texture_format = GL_RGBA;
                else
                    texture_format = GL_BGRA;
            }
            else if (nOfColors == 3)     // no alpha channel
            {
                if (surface->format->Rmask == 0x000000ff)
                    texture_format = GL_RGB;
                else
                    texture_format = GL_BGR;
            }
            else
            {
                texture_format = 0;
                throw "Image is not truecolour";
            }

            // Have OpenGL generate a texture object handle for us
            glGenTextures( 1, &texture );

            // Bind the texture object
            glBindTexture( GL_TEXTURE_2D, texture );

            //Set the texture's stretching properties
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            // Edit the texture object's image data using the information SDL_Surface gives us
            glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                texture_format, GL_UNSIGNED_BYTE, surface->pixels );
            SDL_FreeSurface( surface );
        }
        else
        {
            throw name;
        }
	}
}
