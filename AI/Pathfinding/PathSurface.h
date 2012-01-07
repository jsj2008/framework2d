#ifndef PATHSURFACE_H
#define PATHSURFACE_H

#include <Types/Vec2f.h>

class PathSurface
{
    public:
        PathSurface(const Vec2f& _a, const Vec2f& _b);
        virtual ~PathSurface();
        Vec2f a,b;
    protected:
    private:
};

#endif // PATHSURFACE_H
