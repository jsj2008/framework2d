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

void DynamicEditorMode::create()
{
    this->finish();
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->finish();
    }
    g_LevelManager.addBody(name, params);
}
