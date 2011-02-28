#include "EditorStateSwitcher.h"
#include <GameModes/GameMode.h>
#include <Game.h>

EditorStateSwitcher::EditorStateSwitcher(const Rect& _Rect, std::initializer_list<Icon*> icons, GameMode* _root, GameMode** _states)
:SelectionBox(_Rect,icons)
{
    //ctor
    root = _root;
    states = new GameMode*[icons.size()]; /// numElements is private but we can intercept it here :)
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        states[i] = _states[i];
    }
}

EditorStateSwitcher::~EditorStateSwitcher()
{
    //dtor
}

void EditorStateSwitcher::selectionTrigger()
{
    g_Game.set(root,states[currentSelection]);
    /*GameMode* top = g_Game.top();
    while (top != root)
    {
        g_Game.pop();
        top = g_Game.top();
    }
    g_Game.push(states[currentSelection]);
    states[currentSelection]->set();*/
}
