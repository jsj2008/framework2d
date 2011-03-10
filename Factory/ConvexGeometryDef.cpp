#include "ConvexGeometryDef.h"

Vec2f& ConvexGeometryDef::getVertex(unsigned int i)
{
    float* f = &vertices[i*2];
    Vec2f* vec = (Vec2f*)f;
    return *vec;
}
void ConvexGeometryDef::addPoint(const Vec2f& p)
{
    assert(numVertices != b2_maxPolygonVertices);
    if (!((getVertex(numVertices-1)-p).LengthSquared() > b2_epsilon * b2_epsilon))
    {
        return; /// Discard polygon
    }
    getVertex(numVertices) = p;
    numVertices++;
}
#define M_PI 3.14159265358979323846
bool ConvexGeometryDef::sort()
{
    bool alreadySorted = false;
    for (unsigned char i = 0; i < numVertices; i++)
    {
#define vertices(i) getVertex(i%numVertices)
        Vec2f start = vertices(i);
        Vec2f middle = vertices((i+1));
        Vec2f end = vertices((i+2));
#undef vertices
        Vec2f a = start - middle;
        Vec2f b = end - middle;
        a.Normalize();
        b.Normalize();

		float myAngle = atan2(a.y,a.x);
		float tAngle = atan2(b.y,b.x);
		float angle = myAngle - tAngle;
		if (angle <= -M_PI)
		{
			angle += M_PI*2.0;
		}
		if (angle >= M_PI)
		{
			angle -= M_PI*2.0;
		}
		angle *= 180/M_PI;
        if (angle < 0.0f)
        {
            if (alreadySorted)
            {
                return false;
            }
            else
            {
                for (unsigned char ii = 0; ii < numVertices/2; ii++)
                {
                    Vec2f temp = getVertex(ii);
                    getVertex(ii) = getVertex(numVertices-(ii+1));
                    getVertex(numVertices-(ii+1)) = temp;
                }
                alreadySorted = true;
                i = 0;
            }
        }
    }
    return true;
}
