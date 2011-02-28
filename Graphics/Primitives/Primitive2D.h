#ifndef PRIMITIVE2D_H
#define PRIMITIVE2D_H

#include <Graphics/Primitives/Primitive.h>
#include <Types/Vec2i.h>

class Primitive2D : public Primitive
{
    public:
        Primitive2D();
        virtual ~Primitive2D();
        virtual void draw(const Vec2i topLeft)=0;
    protected:
    private:
};

#endif // PRIMITIVE2D_H
