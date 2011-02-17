#ifndef CONVEXPOLYGONSKIN_H
#define CONVEXPOLYGONSKIN_H

#include "Skin.h"
#include <Box2D/Common/b2Math.h>


class ConvexPolygonSkin : public Skin
{
    public:
        ConvexPolygonSkin(float *_points, unsigned char _numPoints);
        virtual ~ConvexPolygonSkin();
        void vRender();
        SkinType getType(){return eConvexPolygonSkinType;}
    protected:
    private:
        b2Vec2 points[b2_maxPolygonVertices];
        unsigned char numPoints;
};

#endif // CONVEXPOLYGONSKIN_H
