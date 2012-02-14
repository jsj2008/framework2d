#ifndef WATERPHYSICSSYSTEM_H
#define WATERPHYSICSSYSTEM_H

#include <GameObject.h>
#include <Types/Vec2f.h>
#include <unordered_map>
class b2FixtureBodyPart;

class WaterPhysicsSystem : public GameObject<WaterPhysicsSystem>
{
    public:
        WaterPhysicsSystem();
        virtual ~WaterPhysicsSystem();
        static std::string name()
        {
            return "WaterPhysicsSystem";
        }
        static void registerActions(GameObjectType* _type);
        void addFixture(b2FixtureBodyPart* _bodyPart);
        std::vector<Vec2f> getContainer(const Vec2f& _position);
    protected:
    private:
        void addEdge(const Vec2f& _a, const Vec2f& _b, b2FixtureBodyPart* _destructionListener);

        struct Vertex;
        struct Edge
        {
            enum EdgeType
            {
                eLeftFloor,
                eRightFloor,
                eRightRoof,
                eLeftRoof,
                eEdgeTypeMax
            };
            Edge(){a = b = nullptr;}
            Vertex* a,* b;
            Vec2f aPosition(){return a->position;}
            Vec2f bPosition(){return b->position;}
            EdgeType getEdgeType();
        };
        struct Vertex
        {
            enum VertexType
            {
                eBed,
                eRoot,
                eChangeInGradient,
                eVertexTypeMax
            };
            enum VertexShape
            {
                eLeft,
                eRight,
                eVertexShapeMax
            };
            Vertex(const Vec2f& _position){position = _position; a = b = nullptr;}
            Vec2f position;
            Edge* a,* b;
            VertexType getVertexType();
            VertexShape getVertexShape();
        };

        void createVertex(const Vec2f& _position, Edge* _a, Edge* _b);
        //std::unordered_map<b2FixtureBodyPart*, std::vector<Edge>> edgeMap;
        std::vector<Edge*> edges;
};

#endif // WATERPHYSICSSYSTEM_H
