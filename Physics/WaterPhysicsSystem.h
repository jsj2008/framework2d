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
        class Edge
        {
            public:
                enum EdgeType
                {
                    eLeftFloor,
                    eRightFloor,
                    eRightRoof,
                    eLeftRoof,
                    eEdgeTypeMax
                };
                Edge(){a = b = nullptr;}
                void setA(Vertex* _a);
                void setB(Vertex* _b);
                void setA(Vertex* _a, const Vec2f& _bPosition);
                void setB(const Vec2f& _aPosition, Vertex* _b);
                Vertex* getA(){return a;}
                Vertex* getB(){return b;}
                Vec2f aPosition(){return a->position;}
                Vec2f bPosition(){return b->position;}
                EdgeType getEdgeType();
            private:
                Vertex* a,* b;
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
            Vertex(const Vec2f& _position){position = _position;}
            Vec2f position;
            struct EdgeAttachment
            {
                float angle;
                Edge* edge;
            };
            std::vector<EdgeAttachment> edges;
            void addInwardsEdge(Edge* _edge);
            void addOutwardsEdge(Edge* _edge);
            void addInwardsEdge(const Vec2f& _a, Edge* _edge);
            void addOutwardsEdge(Edge* _edge, const Vec2f& _b);
            void removeEdge(Edge* _edge);
            Edge* getNextOutfacing(Edge* _edge);
            //Edge* a,* b;
            //VertexType getVertexType();
            //VertexShape getVertexShape();
        };

        void createVertex(const Vec2f& _position, Edge* _a, Edge* _b, Vec2f* _bBPosition = nullptr);
        //std::unordered_map<b2FixtureBodyPart*, std::vector<Edge>> edgeMap;
        std::vector<Edge*> edges;
};

#endif // WATERPHYSICSSYSTEM_H
