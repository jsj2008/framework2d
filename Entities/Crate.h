#ifndef CRATE_H
#define CRATE_H

#include "Entity.h"


class Crate : public Entity
{
    public:
        Crate();
        virtual ~Crate();
        void update();
        EntityType getType(){return eCrateEntityType;}
    protected:
    private:
};

#endif // CRATE_H
