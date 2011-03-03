#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H

#include <vector>
#include <fstream>
class ParallaxSprite;

class ParallaxLayer
{
    public:
        ParallaxLayer(std::ifstream* file);
        virtual ~ParallaxLayer();
        void render();
        void save(std::ofstream* file);
    protected:
    private:
        std::vector<ParallaxSprite*> sprites;
        float depth;
};

#endif // PARALLAXLAYER_H
