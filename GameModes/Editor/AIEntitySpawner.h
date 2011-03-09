#ifndef AIENTITYSPAWNER_H
#define AIENTITYSPAWNER_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <Factory/AIEntityDef.h>
class FreeCamera;

class AIEntitySpawner : public ClickReleaseEvent
{
    public:
        AIEntitySpawner(FreeCamera* camera);
        virtual ~AIEntitySpawner();
        void click(Vec2i mouse, unsigned char button);
    protected:
    private:
        AIEntityDef def;
};

#endif // AIENTITYSPAWNER_H
