#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickNoEvent.h>
class EditorStateSwitcher;
class SelectionBox;
class b2Body;
class FreeCamera;
#define NUM_ITEM_SPAWNERS 2

class ItemSpawner : public GameMode, public ClickNoEvent
{
    public:
        ItemSpawner(FreeCamera* camera);
        void init();
        virtual ~ItemSpawner();
        void registerEvent(InputContext* event);
        bool activate(const CEGUI::EventArgs&);
    protected:
    private:
        InputContext* modes[NUM_ITEM_SPAWNERS];
        EditorStateSwitcher* stateSwitcher;
};

#endif // ITEMSPAWNER_H
