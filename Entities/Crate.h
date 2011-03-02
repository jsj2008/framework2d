#ifndef CRATE_H
#define CRATE_H

#include "Entity.h"


class Crate : public Entity
{
    public:
        Crate();
        void update();
        EntityType getType(){return eCrateEntityType;}
    protected:
    private:
        virtual ~Crate();
};

#endif // CRATE_H
