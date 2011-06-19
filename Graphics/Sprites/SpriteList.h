#ifndef SPRITELIST_H
#define SPRITELIST_H

class Sprite;

class SpriteList
{
    public:
        SpriteList();
        virtual ~SpriteList();
        void addSprite(Sprite* _sprite);
        void deleteSprite(Sprite* _sprite);
    protected:
    private:
        Sprite* first;
};

#endif // SPRITELIST_H
