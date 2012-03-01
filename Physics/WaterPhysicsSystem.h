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
  void renderWireframe();
  void addFixture(b2FixtureBodyPart* _bodyPart);
  std::vector<Vec2f> getContainer(const Vec2f& _position);
protected:
private:
  void addEdge(const Vec2f& _a, const Vec2f& _b, b2FixtureBodyPart* _destructionListener);

  struct Vertex;
  struct Volume;
  struct Boundary;
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
    ~Edge();
    void setA(Vertex* _a);
    void setB(Vertex* _b);
    void setA(Vertex* _a, const Vec2f& _bPosition);
    void setB(const Vec2f& _aPosition, Vertex* _b);
    Vertex* getA(){return a;}
    Vertex* getB(){return b;}
    Vec2f aPosition(){return a->position;}
    Vec2f bPosition(){return b->position;}
    EdgeType getEdgeType();
    Edge* split(Vec2f _point, Boundary* _boundary);
    void setVolume(Volume* _volume);
    Volume* getVolume();
  private:
    Vertex* a,* b;
    Volume* volume;
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
    Vertex(const Vec2f& _position, Boundary* _boundary = nullptr, bool _anchor = false);
    ~Vertex();
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
    Boundary* boundary;
    bool anchor;
    //Edge* a,* b;
    //VertexType getVertexType();
    //VertexShape getVertexShape();
  };
  class Boundary
  {
  public:
    Boundary(){left = right = nullptr;}
    ~Boundary();
    void setLeft(Vertex* _left);
    void setRight(Vertex* _right);
    Vertex* getLeft(){return left;}
    Vertex* getRight(){return right;}
    Vec2f getLeftPosition();
    Vec2f getRightPosition();
  private:
    Vertex* left,* right;
  };
  class Volume
  {
  public:
    Volume(){left = right = nullptr;}
    ~Volume();
    Edge* getLeft(){return left;}
    Edge* getRight(){return right;}
    void setLeft(Edge* _left);
    void setRight(Edge* _right);
  private:
    Edge* left,* right;
  };
  Edge* findIntersectingEdge(Vec2f _a, Vec2f* _b, Edge* _exception = nullptr, Edge* _exception2 = nullptr);
  void addFinalisedVertex(Vertex* _vertex, Edge* _edge, bool _leftEdge);
  void addFinalisedEdge(Edge* _edge);
  void createVertex(const Vec2f& _position, Edge* _a, Edge* _b, Vec2f* _bBPosition = nullptr);

  //std::unordered_map<b2FixtureBodyPart*, std::vector<Edge>> edgeMap;
  std::vector<Edge*> edges;
  std::vector<Volume*> volumes;
  std::vector<Boundary*> boundaries;
};

#endif // WATERPHYSICSSYSTEM_H
