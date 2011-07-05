#include "DynamicEditorMode.h"
#include <Level/LevelManager.h>

DynamicEditorMode::DynamicEditorMode()
{
    //ctor
}

DynamicEditorMode::~DynamicEditorMode()
{
    //dtor
}

void DynamicEditorMode::finish()
{
    g_LevelManager.addBody(name, params);
}
