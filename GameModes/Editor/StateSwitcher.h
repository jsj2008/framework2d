#ifndef STATESWITCHER_H
#define STATESWITCHER_H

#include <Input/Mouse/SelectionBox.h>
class GameMode;

class StateSwitcher : public SelectionBox
{
    public:
        StateSwitcher(const Rect& _Rect, int _numElements, GameMode* _root, GameMode** _states);
        virtual ~StateSwitcher();
    protected:
    private:
        void selectionTrigger();
        GameMode** states;
        GameMode* root;
};

#endif // STATESWITCHER_H
