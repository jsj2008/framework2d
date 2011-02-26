#ifndef BUBBLESKIN_H
#define BUBBLESKIN_H

#include <Graphics/Skins/Skin.h>


class BubbleSkin : public Skin
{
    public:
        BubbleSkin();
        virtual ~BubbleSkin();
        void vRender();
        SkinType getType(){return eBubbleSkinType;}
    protected:
    private:
};

#endif // BUBBLESKIN_H
