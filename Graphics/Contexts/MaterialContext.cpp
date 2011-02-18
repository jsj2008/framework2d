#include "MaterialContext.h"
#include "TextureContext.h"
#include <cassert>

MaterialContext::MaterialContext()
{
}
MaterialContext::MaterialContext(TextureContext* _TextureContext)
{
    //ctor
    mTextureContext = _TextureContext;
}

MaterialContext::~MaterialContext()
{
    //dtor
}

void MaterialContext::assertDelete()
{
}
void MaterialContext::bindTexture()
{
}
void MaterialContext::grab()
{
    mTextureContext->grab();
}

void MaterialContext::release()
{
    mTextureContext->release();
}
