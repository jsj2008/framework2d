#ifndef PLAYER_H
#define PLAYER_H

#include <Entities/Entity.h>


class Player : public Entity
{
    public:
        Player();
        virtual ~Player();
        void update();
        EntityType getType(){return ePlayerEntityType;}
    protected:
    private:
};

#endif // PLAYER_H
