#include "MaterialContext.h"
#include "TextureContext.h"
#include <cassert>

MaterialContext::MaterialContext(const char* _name)
:GraphicalContext(_name)
{
    mTextureContext = nullptr;
}
MaterialContext::MaterialContext(TextureContext* _TextureContext)
:GraphicalContext(nullptr)
{
    //ctor
    mTextureContext = _TextureContext;
}

MaterialContext::~MaterialContext()
{
    //dtor
}

void MaterialContext::bind()
{
    mTextureContext->bind();
}
void MaterialContext::vGrab()
{
    mTextureContext->grab();
}

void MaterialContext::vRelease()
{
    mTextureContext->release();
}
