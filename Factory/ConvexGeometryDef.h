#ifndef CONVEXGEOMETRYDEF_H
#define CONVEXGEOMETRYDEF_H

#include <Factory/FactoryDef.h>


class ConvexGeometryDef : public FactoryDef
{
    public:
        unsigned char numVertices;
        float vertices[b2_maxPolygonVertices*2];
        Vec2f& getVertex(unsigned int i);
        void addPoint(const Vec2f& p);
        bool sort();
};

#endif // CONVEXGEOMETRYDEF_H
