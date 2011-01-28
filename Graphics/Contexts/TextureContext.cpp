#include "TextureContext.h"
#include <cstring>
#include <GL/gl.h>
#include <SDL/SDL_video.h>

TextureContext::TextureContext(const char* _textureName)
{
    //ctor
    strcpy(textureName,_textureName);
    referenceCount = 0;
}

TextureContext::~TextureContext()
{
    //dtor
}

void TextureContext::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D,texture);
}
void TextureContext::grab()
{
    if (referenceCount == 0)
    {
        loadFromFile();
    }
    referenceCount++;
}

void TextureContext::release()
{
    referenceCount--;
    if (referenceCount == 0)
    {
        glDeleteTextures(1,&texture);
    }
}

#define GL_BGRA                                 0x80E1
#define GL_BGR                                  0x80E0
void TextureContext::loadFromFile()
{
	texture = 0;
	SDL_Surface *surface = SDL_LoadBMP(textureName);
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
		throw textureName;
	}
}
