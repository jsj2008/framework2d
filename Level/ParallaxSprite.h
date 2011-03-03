#ifndef PARALLAXSPRITE_H
#define PARALLAXSPRITE_H

#include <fstream>
#include <Types/Vec2f.h>
class TextureContext;

class ParallaxSprite
{
    public:
        ParallaxSprite(std::ifstream* file);
        virtual ~ParallaxSprite();
        void render();
        void save(std::ofstream* file);
    protected:
    private:
        TextureContext* texture;
        Vec2f position, size;
};

#endif // PARALLAXSPRITE_H
