#ifndef SLIDERBAR_H
#define SLIDERBAR_H

#include <Input/Mouse/ClickDragEvent.h>
class FontPrimitive;

class SliderBar : public ClickDragEvent
{
    public:
        SliderBar(const Vec2i& left, int width, const char* name, float initialPosition = 0);
        virtual ~SliderBar();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        float getPosition();
        void render();
    protected:
    private:
        float positionf;
        float positioni;
        int length;
        void calculatePosition(int mousePosition);
        FontPrimitive* mText;
};

#endif // SLIDERBAR_H
