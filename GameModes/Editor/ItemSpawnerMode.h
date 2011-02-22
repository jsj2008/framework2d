#ifndef ITEMSPAWNERMODE_H
#define ITEMSPAWNERMODE_H

#include <GameModes/GameMode.h>
class FreeCamera;

class ItemSpawnerMode : public GameMode
{
    public:
        ItemSpawnerMode(FreeCamera* camera);
        virtual ~ItemSpawnerMode();
    protected:
    private:
};

#endif // ITEMSPAWNERMODE_H
