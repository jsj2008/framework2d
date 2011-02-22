#include "StateSwitcher.h"
#include <GameModes/GameMode.h>
#include <Game.h>

StateSwitcher::StateSwitcher(const Rect& _Rect, int _numElements, GameMode* _root, GameMode** _states)
:SelectionBox(_Rect,_numElements)
{
    //ctor
    root = _root;
    states = new GameMode*[_numElements]; /// numElements is private but we can intercept it here :)
    for (int i = 0; i < _numElements; i++)
    {
        states[i] = _states[i];
    }
}

StateSwitcher::~StateSwitcher()
{
    //dtor
}

void StateSwitcher::selectionTrigger()
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
