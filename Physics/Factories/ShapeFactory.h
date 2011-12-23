#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>

class ShapeFactory : public AbstractFactory<b2Shape, ShapeFactory>
{
    public:
        ShapeFactory();
        virtual ~ShapeFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        b2Shape* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "ShapeFactory";
        }
    protected:
    private:
        enum ShapeType
        {
            e_Circle = b2Shape::e_circle,
            e_Polygon = b2Shape::e_polygon,
            e_Rect,
            e_ShapeTypeMax,
        };
        ShapeType type;
};

#endif // SHAPEFACTORY_H
