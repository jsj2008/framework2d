#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
class FactoryDef;
class Entity;
class Skin;
class MaterialContext;
class Factory
{
    public:
        Factory();
        virtual ~Factory();
        virtual Entity* createEntity(FactoryDef* data)=0;
    protected:
        void setMaterial(Skin* skin, MaterialContext* material);
    private:
};

#endif // FACTORY_H
