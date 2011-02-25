#ifndef CONVEXGEOMETRYDEF_H
#define CONVEXGEOMETRYDEF_H

#include <Factory/FactoryDef.h>


class ConvexGeometryDef : public FactoryDef
{
    public:
        ConvexGeometryDef();
        unsigned char numVertices;
        Vec2f vertices[b2_maxPolygonVertices];
        char materialName[32];
        void addPoint(const Vec2f& p);
        bool sort();
};

#endif // CONVEXGEOMETRYDEF_H
