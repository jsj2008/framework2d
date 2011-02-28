#ifndef SLIDERBAR_H
#define SLIDERBAR_H

#include <Input/Mouse/ClickDragEvent.h>
class FontPrimitive;

/// Returns a value for the position between 0 and 1
class SliderBar : public ClickDragEvent
{
    public:
        SliderBar(const Vec2i& left, int width, const char* name, float initialPosition = 0.0f);
        virtual ~SliderBar();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        float getPosition(){return positionf;}
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
