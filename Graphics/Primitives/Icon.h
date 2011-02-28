#ifndef ICON_H
#define ICON_H

#include <Graphics/Primitives/Primitive2D.h>
class MaterialContext;

class Icon : public Primitive2D
{
    public:
        Icon(const char* iconName, const Vec2i _dimensions = Vec2i(0,0));
        virtual ~Icon();
        void draw(const Vec2i topLeft);
        void setDimensions(const Vec2i _dimensions){dimensions = _dimensions;}
    protected:
    private:
        MaterialContext* materialContext;
        Vec2i dimensions;
};

#endif // ICON_H
