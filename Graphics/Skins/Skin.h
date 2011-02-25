#ifndef SKIN_H
#define SKIN_H

class b2Body;
class MaterialContext;
enum SkinType
{
    eStaticSkinType,
    eConvexPolygonSkinType,
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
        MaterialContext* material; /// FIXME
    protected:
    private:
        friend class Factory;
};

#endif // SKIN_H
