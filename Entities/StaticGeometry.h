#ifndef STATICGEOMETRY_H
#define STATICGEOMETRY_H

#include "Entity.h"


class StaticGeometry : public Entity
{
    public:
        StaticGeometry();
        void update();
    protected:
    private:
        virtual ~StaticGeometry();
};

#endif // STATICGEOMETRY_H
