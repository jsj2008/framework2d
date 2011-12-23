#ifndef BARDISPLAY_H
#define BARDISPLAY_H


class BarDisplay
{
    public:
        BarDisplay(float _maxHeight);
        virtual ~BarDisplay();
        void setHeight(float _height); /// 0 to 1
        void render();
    protected:
    private:
        float height;
        float maxHeight;
};

#endif // BARDISPLAY_H
