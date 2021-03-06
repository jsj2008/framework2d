#ifndef CONVEXPOLYGONSKINFACTORY_H
#define CONVEXPOLYGONSKINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class Skin;

class ConvexPolygonSkinFactory : public AbstractFactory<Skin, ConvexPolygonSkinFactory>
{
    public:
        ConvexPolygonSkinFactory();
        virtual ~ConvexPolygonSkinFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "ConvexPolygonSkinFactory";
        }
        Skin* useFactory(FactoryParameters* _parameters);
    protected:
    private:
        std::string materialName;
};

#endif // CONVEXPOLYGONSKINFACTORY_H
