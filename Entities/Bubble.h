#ifndef BUBBLE_H
#define BUBBLE_H

#include <Entities/Entity.h>


class Bubble : public Entity
{
    public:
        Bubble();
        virtual ~Bubble();
        void update();
        EntityType getType(){return eBubbleEntityType;}
    protected:
    private:
};

#endif // BUBBLE_H
