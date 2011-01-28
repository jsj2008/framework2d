#ifndef STATICSKIN_H
#define STATICSKIN_H

#include "Skin.h"


class StaticSkin : public Skin
{
    public:
        StaticSkin(int _width, int _height);
        virtual ~StaticSkin();
        void vRender();
        SkinType getType(){return eStaticSkinType;}
    protected:
    private:
        int width,height;
};

#endif // STATICSKIN_H
