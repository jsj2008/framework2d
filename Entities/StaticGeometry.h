#ifndef STATICGEOMETRY_H
#define STATICGEOMETRY_H

#include "Entity.h"


class StaticGeometry : public Entity
{
    public:
        StaticGeometry();
        virtual ~StaticGeometry();
        void update();
        EntityType getType(){return eStaticGeometryEntityType;}
    protected:
    private:
};

#endif // STATICGEOMETRY_H
