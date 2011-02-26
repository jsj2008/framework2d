#ifndef BUBBLESKIN_H
#define BUBBLESKIN_H

#include <Graphics/Skins/Skin.h>


class BubbleSkin : public Skin
{
    public:
        BubbleSkin(float _radius);
        virtual ~BubbleSkin();
        void vRender();
        SkinType getType(){return eBubbleSkinType;}
    protected:
    private:
        float radius;
};

#endif // BUBBLESKIN_H
