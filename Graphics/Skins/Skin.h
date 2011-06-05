#ifndef SKIN_H
#define SKIN_H

class b2Body;
class MaterialContext;
enum SkinType
{
    eStaticSkinType,
    eConvexPolygonSkinType,
    eBubbleSkinType,
    eSkinTypeMax
};
class Skin
{
    public:
        Skin();
        virtual ~Skin();
        void render(b2Body* body);
        virtual void vRender()=0;
        virtual SkinType getType()=0;
    protected:
    private:
        friend class Factory;
        friend class AbstractFactory;
        MaterialContext* material;
};

#endif // SKIN_H
