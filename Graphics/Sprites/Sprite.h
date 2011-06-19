#ifndef SPRITE_H
#define SPRITE_H

class Skin;

class Sprite
{
    public:
        Sprite(Skin* _skin);
        void render();
    protected:
    private:
        Skin* skin;

        friend class SpriteList;
        virtual ~Sprite();
        Sprite* next,* prev;
};

#endif // SPRITE_H
