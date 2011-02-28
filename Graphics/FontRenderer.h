#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <unordered_map>
#include <string>
#include <SDL/SDL_ttf.h>
class FontPrimitive;

class FontRenderer
{
    public:
        FontRenderer(const char* fontname, int pointSize);
        virtual ~FontRenderer();
        FontPrimitive* renderFont(const char* string, int wrap);
    protected:
    private:
        std::unordered_map<std::string,FontPrimitive*> fontMap;
        TTF_Font* font;
};

#endif // FONTRENDERER_H
