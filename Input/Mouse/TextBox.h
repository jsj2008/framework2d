#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include <Input/Mouse/ClickReleaseEvent.h>
class FontPrimitive;

class TextBox : public ClickReleaseEvent
{
    public:
        TextBox(const Vec2i position, const char* name);
        virtual ~TextBox();
        void render();
        void inputCharacter(char c);
        void click(Vec2i mouse, unsigned char button);
        const char* getString(){return text.c_str();}
    protected:
    private:
        FontPrimitive* title, *textGraphic;
        std::string text;
};

#endif // TEXTBOX_H
