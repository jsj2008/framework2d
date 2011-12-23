#ifndef STATICSKIN_H
#define STATICSKIN_H

#include "Skin.h"


class StaticSkin : public Skin
{
    public:
        StaticSkin(float _width, float _height);
        virtual ~StaticSkin();
        void vRender();
        SkinType getType(){return eStaticSkinType;}
    protected:
    private:
        float width,height;
};

#endif // STATICSKIN_H
