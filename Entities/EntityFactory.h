#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
class GraphicsManager;
struct EntityFactoryDef
{
    /// Types
    union EntityDef
    {
        /// Types
        struct PlayerTypeDef
        {
            int startingHealth;
        };
        struct CrateTypeDef
        {

        };
        struct StaticGeometryTypeDef
        {
        };
        struct AIEntityTypeDef
        {
            int startingHealth;
            BrainFactoryDef brainFactoryDef;
        };
        /// Members
        EntityDef(EntityType _type);
        PlayerTypeDef playerTypeDef;
        CrateTypeDef crateTypeDef;
        AIEntityTypeDef aiEntityTypeDef;
    };
    /// Members
    EntityFactoryDef(EntityType _type);
    EntityType type;
    EntityDef entityDef;
    PhysicsFactoryDef physicsDef;
    GraphicsFactoryDef graphicsDef;
};
class EntityFactory
{
    public:
        EntityFactory(GraphicsManager* _GraphicsManager,
                      PhysicsManager* _PhysicsManager);
        virtual ~EntityFactory();
        Entity* entityFactory(EntityFactoryDef& def, b2Vec2& initialPosition);
        void setCameraTarget(const Entity* entity);
    protected:
    private:
        GraphicsManager* pGraphicsManager;
        PhysicsManager* pPhysicsManager;
        AIManager* pAIManager;
};

#endif // ENTITYFACTORY_H
