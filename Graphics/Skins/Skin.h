#ifndef SKIN_H
#define SKIN_H

#include <GameObject.h>
class BodyPart;
class MaterialContext;
enum SkinType
{
    eStaticSkinType,
    eConvexPolygonSkinType,
    eBubbleSkinType,
    eSkinTypeMax
};
class Skin : public GameObject<Skin>
{
    public:
        Skin();
        virtual ~Skin();
        void render(BodyPart* body);
        virtual void vRender()=0;
        virtual SkinType getType()=0;
        static void registerActions();
        MaterialContext* material; // FIXME make this private once the entity factory is a concrete type

        static std::string name()
        {
            return "Skin";
        }
    protected:
    private:
};

#endif // SKIN_H
