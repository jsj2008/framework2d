#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <Input/Mouse/ClickReleaseEvent.h>


class ItemSpawner : public ClickReleaseEvent
{
    public:
        ItemSpawner(const Rect& _Rect);
        virtual ~ItemSpawner();
        void click(Vec2i mouse, unsigned char button);
    protected:
    private:
};

#endif // ITEMSPAWNER_H
