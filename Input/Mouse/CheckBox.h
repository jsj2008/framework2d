#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <Input/Mouse/ClickReleaseEvent.h>
class FontPrimitive;

class CheckBox : public ClickReleaseEvent
{
    public:
        CheckBox(const Vec2i position, const char* _text, bool initial = true);
        virtual ~CheckBox();
        void click(Vec2i mouse, unsigned char button);
        void render();
        bool getChecked(){return checked;}
    protected:
    private:
        FontPrimitive* text;
        bool checked;
};

#endif // CHECKBOX_H
