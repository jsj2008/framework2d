#ifndef FONTPRIMITIVE_H
#define FONTPRIMITIVE_H

#include <Graphics/Primitives/Primitive2D.h>
#include <string>

class FontPrimitive : public Primitive2D
{
    public:
        FontPrimitive(const char* name, unsigned int _texture, const Vec2i _dimensions);
        virtual ~FontPrimitive();
        std::string& getString(){return myString;}
        void draw(const Vec2i topLeft);
    protected:
    private:
        std::string myString;
        unsigned int texture;
        Vec2i dimensions;
};

#endif // FONTPRIMITIVE_H
