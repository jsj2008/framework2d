#ifndef ICON_H
#define ICON_H

#include <Graphics/Primitives/Primitive2D.h>
class MaterialContext;

class Icon : public Primitive2D
{
    public:
        Icon(const char* iconName);
        virtual ~Icon();
        void draw(Vec2i& topLeft, Vec2i& bottomRight);
    protected:
    private:
        MaterialContext* materialContext;
};

#endif // ICON_H
