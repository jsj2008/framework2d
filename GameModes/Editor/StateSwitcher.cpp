#include "StateSwitcher.h"
#include <GameModes/GameMode.h>

StateSwitcher::StateSwitcher(const Rect& _Rect, int _numElements, GameMode** _states)
:SelectionBox(_Rect,_numElements)
{
    //ctor
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
    states[currentSelection]->set();
}
