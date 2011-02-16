#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <vector>

#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
class GraphicsManager;
/// Types
struct PlayerTypeDef
{
    EntityType type;
    int startingHealth;
};
struct CrateTypeDef
{
    EntityType type;
};
struct StaticGeometryTypeDef
{
    EntityType type;
};
struct AIEntityTypeDef
{
    EntityType type;
    int startingHealth;
    BrainFactoryDef brainFactoryDef;
};
struct EntityFactoryDef
{
    /// Types
    union EntityDef
    {
        EntityType type;
        /// Members
        EntityDef(EntityType _type);
        PlayerTypeDef playerTypeDef;
        CrateTypeDef crateTypeDef;
        AIEntityTypeDef aiEntityTypeDef;
        StaticGeometryTypeDef staticGeometryTypeDef;
    };
    /// Members
    EntityFactoryDef(EntityType _type);
    EntityDef entityDef;
    PhysicsFactoryDef physicsDef;
    GraphicsFactoryDef graphicsDef;
};
struct CreatureDef
{
    b2Vec2 dimensions;
    int texture;
    BrainType type;
};
struct PlatformDef
{
    b2Vec2 points[b2_maxPolygonVertices];
    unsigned char numPoints;
    int texture;
};
class EntityFactory
{
    public:
        EntityFactory(GraphicsManager* _GraphicsManager,
                      PhysicsManager* _PhysicsManager);
        virtual ~EntityFactory();
        unsigned int addEntityDef(CreatureDef& def);
        unsigned int addEntityDef(PlatformDef& def);
        Entity* createEntity(unsigned int index, b2Vec2& initialPosition);
        void setCameraTarget(const Entity* entity);
    protected:
    private:
        Entity* entityFactory(EntityFactoryDef& def, b2Vec2& initialPosition);
        std::vector<EntityFactoryDef> factoryDefs;
        GraphicsManager* pGraphicsManager;
        PhysicsManager* pPhysicsManager;
        AIManager* pAIManager;
        Entity* createContainer(EntityFactoryDef::EntityDef& def);
        Entity* crateEntity(CrateTypeDef& def);
        Entity* staticGeometryEntity(StaticGeometryTypeDef& def);
        Entity* aiEntity(AIEntityTypeDef& def);
};

#endif // ENTITYFACTORY_H
