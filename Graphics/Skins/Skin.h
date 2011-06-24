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
        MaterialContext* material; // FIXME make this private once the entity factory is a concrete type
    protected:
    private:
};

#endif // SKIN_H
