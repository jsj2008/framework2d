#include "Vec2i.h"
#include <Graphics/GraphicsManager.h>

const Vec2f Vec2i::ScreenToWorldSpace() const
{
    Vec2i view = g_GraphicsManager.getView();
    Vec2i world = *this + view;
    Vec2f ret(world.x,world.y);
    ret /= g_GraphicsManager.getPixelsPerMeter();
    return ret;
}

void Vec2i::worldToScreenSpace(Vec2f world)
{
    world *= g_GraphicsManager.getPixelsPerMeter();
    *this = Vec2i(world.x,world.y);
    *this -= g_GraphicsManager.getView();
}
using namespace std;
std::ostream& operator<< (ostream &out, Vec2i &vec)
{
    out << vec.x << " " << vec.y << " ";
    return out;
}

istream& operator>> (istream &in, Vec2i &vec)
{
    in >> vec.x;
    in >> vec.y;
    return in;
}
