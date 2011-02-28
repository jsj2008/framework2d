#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickReleaseEvent.h>
#include <vector>
#include <Factory/CrateDef.h>
class SelectionBox;
class FreeCamera;
class SelectionBox;

class ItemSpawner : public GameMode, public ClickReleaseEvent
{
    public:
        ItemSpawner(FreeCamera* camera, const Rect& _Rect);//, SelectionBox* _selectionBox
        virtual ~ItemSpawner();
        void click(Vec2i mouse, unsigned char button);
    protected:
    private:
        SelectionBox* selectionBox;
        std::vector<CrateDef> crateDefs;
        void addElement();
};

#endif // ITEMSPAWNER_H
