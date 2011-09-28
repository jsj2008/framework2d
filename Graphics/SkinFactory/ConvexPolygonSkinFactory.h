#ifndef CONVEXPOLYGONSKINFACTORY_H
#define CONVEXPOLYGONSKINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>


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
        Skin* useFactory(FactoryParameters* parameters);
    protected:
    private:
        std::string materialName;
};

#endif // CONVEXPOLYGONSKINFACTORY_H
