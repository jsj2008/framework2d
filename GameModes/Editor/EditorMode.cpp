#include "EditorMode.h"
#include "GeometryEditor.h"
#include <Input/InputState.h>
#include <Input/InputManager.h>

EditorMode::EditorMode()
{
    //ctor
    geometryEditor = new InputState;
    Rect fullScreen(0,0,10000,10000);
    geometryEditor->registerEvent(new GeometryEditor(fullScreen));
    g_InputManager.setInputState(geometryEditor);
}

EditorMode::~EditorMode()
{
    //dtor
}
