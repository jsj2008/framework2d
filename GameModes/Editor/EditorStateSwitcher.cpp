#include "EditorStateSwitcher.h"
#include <GameModes/GameMode.h>
#include <Game.h>

EditorStateSwitcher::EditorStateSwitcher(const Rect& _Rect, std::initializer_list<const char*> _icons, GameMode* _root, GameMode** _states)
:SelectionBox(_Rect,_icons)
{
    //ctor
    root = _root;
    states = new GameMode*[_icons.size()];
    for (unsigned int i = 0; i < _icons.size(); i++)
    {
        states[i] = _states[i];
    }
}

EditorStateSwitcher::~EditorStateSwitcher()
{
    //dtor
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        delete states[i];
    }
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
