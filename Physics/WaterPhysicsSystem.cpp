#include "WaterPhysicsSystem.h"
#include <Physics/BodyParts/b2FixtureBodyPart.h>
#include <Box2D/Box2D.h>
#include <Types/Vec2f.h>

WaterPhysicsSystem::WaterPhysicsSystem()
{
  //ctor
  addEdge({5,5}, {10,-5}, nullptr);
  addEdge({-5,0}, {-7,10}, nullptr);
  addEdge({-10,-6}, {-5,0}, nullptr);
  addEdge({-7,10}, {5,5}, nullptr);
}

WaterPhysicsSystem::~WaterPhysicsSystem()
{
  //dtor
}

void WaterPhysicsSystem::registerActions(GameObjectType* _type)
{

}
#include <iostream>
#define OUTPUT_VEC2F (a, b) a.x << ',' << a.y << ")->(" << b.x << ',' << b.y << ')'
void WaterPhysicsSystem::addFixture(b2FixtureBodyPart* _bodyPart)
{
  /*  b2Fixture* fixture = _bodyPart->getFixture();
  b2Shape* shape = fixture->GetShape();
  assert(dynamic_cast<b2PolygonShape*>(shape)); /// Can't support circles at this time
  b2PolygonShape* polygon = static_cast<b2PolygonShape*>(shape);
  for (int i = 0; i != polygon->GetVertexCount(); i++)
    {
      Vec2f a = polygon->GetVertex(i);
      Vec2f b = polygon->GetVertex((i+1)%polygon->GetVertexCount());
      std::cout << "Edges size: " << edges.size() << std::endl;
      for (unsigned int i = 0; i != edges.size(); i++)
        {
	  Vec2f a = edges[i]->aPosition();
	  Vec2f b = edges[i]->bPosition();
	  std::cout << "\t (" << a.x << ',' << a.y << ")->(" << b.x << ',' << b.y << ')' << std::endl;
        }
      std::cout << "Adding (" << a.x << ',' << a.y << ")->(" << b.x << ',' << b.y << ')' << std::endl;
      addEdge(a, b, _bodyPart);
    }
  std::cout << "Edges size: " << edges.size() << std::endl;
  for (unsigned int i = 0; i != edges.size(); i++)
    {
      Vec2f a = edges[i]->aPosition();
      Vec2f b = edges[i]->bPosition();
      std::cout << "\t (" << a.x << ',' << a.y << ")->(" << b.x << ',' << b.y << ')' << std::endl;
      }*/
}

void WaterPhysicsSystem::addEdge(const Vec2f& _a, const Vec2f& _b, b2FixtureBodyPart* _destructionListener)
{
  Edge* edge = new Edge;
  Edge* intersections[2] = {0, 0};
  unsigned int numIntersections = 0;
  for (unsigned int i = 0; i != edges.size(); i++)
    {
      try
        {
	  Vec2f position = intersectionPosition(_a, _b, edges[i]->aPosition(), edges[i]->bPosition());
	  assert(numIntersections < 2);
	  intersections[numIntersections] = edges[i];
	  numIntersections++;
        }
      catch (int ii)
        {
        }
    }
  switch (numIntersections)
    {
    case 0:
      {
	edge->setA(new Vertex(_a), _b);
	edge->setB(new Vertex(_b));
	addFinalisedEdge(edge);
	break;
      }
    case 1:
      {
	float scalar = intersectionValue(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
	if (scalar < 0.2f)
	  {
	    Vec2f position = intersectionPosition(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
	    edge->setB(position, new Vertex(_b));
	    createVertex(position, intersections[0], edge);
	  }
	else if (scalar > 0.8f)
	  {
	    Vec2f position = intersectionPosition(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
	    edge->setA(new Vertex(_a), position);
	    createVertex(position, edge, intersections[0]);
	  }
	else
	  {
	    std::cout << "Error: scalar is " << scalar << std::endl;
	    assert(false);
	  }
	addFinalisedEdge(edge);
	break;
      }
    case 2:
      {
	float scalar0 = intersectionValue( _a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
	float scalar1 = intersectionValue( _a, _b, intersections[1]->aPosition(), intersections[1]->bPosition());
	if (scalar0 > scalar1)
	  {
	    {
	      Edge* temp = intersections[0];
	      intersections[0] = intersections[1];
	      intersections[1] = temp;
	    }
	    {
	      float temp = scalar0;
	      scalar0 = scalar1;
	      scalar1 = temp;
	    }
	  }
	Vec2f position0 = positionFromScalarValue(_a, _b, scalar0); /// FIXME might be the wrong line
	Vec2f position1 = positionFromScalarValue(_a, _b, scalar1);

	createVertex(position0, intersections[0], edge, &position1);
	createVertex(position1, edge, intersections[1]);
	addFinalisedEdge(edge);
	break;
      }
    default:
      {
	assert(false);
      }
    }
  //edges.push_back({_a, _b});
}

WaterPhysicsSystem::Edge* WaterPhysicsSystem::findIntersectingEdge(Vec2f _a, Vec2f* _b, Edge* _exception, Edge* _exception2)
{
  Edge* ret = nullptr;
  for (unsigned int i = 0; i != edges.size(); i++)
    {
      if (edges[i] != _exception && edges[i] != _exception2)
	try
	  {
	    *_b = intersectionPosition(_a, *_b, edges[i]->aPosition(), edges[i]->bPosition());
	    ret = edges[i];
	  }
	catch (int i)
	  {
	  }
    }
  return ret;
}
void WaterPhysicsSystem::addFinalisedVertex(Vertex* _vertex, Edge* _edge, bool _leftEdge)
{
  Vec2f a = _vertex->position;
  Vec2f b;
  Vertex* left;
  Vertex* right;
  Vertex** unsetVertex;
  Boundary* boundary = _vertex->getBoundary();
  if (boundary == nullptr)
    {
      boundary = new Boundary(this);
      boundaries.push_back(boundary);
    }
  if (_leftEdge)
    {
      b = a + Vec2f(500, 0);
      left = _vertex;
      unsetVertex = &right;
      boundary->setLeft(_vertex);
    }
  else
    {
      b = a - Vec2f(500, 0);
      right = _vertex;
      unsetVertex = &left;
      boundary->setRight(_vertex);
      }
  Edge* opposingEdge = findIntersectingEdge(a, &b, _edge);
  if (opposingEdge)
    {
      *unsetVertex = new Vertex(b, nullptr, true);
    }
  else
    {
      *unsetVertex = nullptr;
    }
    if (left)
    boundary->setLeft(left);
  if (right)
    boundary->setRight(right);
}
void WaterPhysicsSystem::addFinalisedEdge(Edge* _edge)
{
  edges.push_back(_edge);
  Edge::EdgeType type = _edge->getEdgeType();
  bool leftEdge;
  if (type == Edge::eLeftFloor || type == Edge::eLeftRoof)
    {
      leftEdge = true;
    }
  else
    {
      leftEdge = false;
    }
  addFinalisedVertex(_edge->getA(), _edge, leftEdge);
  addFinalisedVertex(_edge->getB(), _edge, leftEdge);

  //  for (Boundary* boundary = boundaries.front(); boundary; boundary = boundary->getNextObject())
  for (unsigned int i = 0; i != boundaries.size(); i++)
    {
      Boundary* boundary = boundaries[i];
      if (boundary)
      try
	{
	  Vec2f position = intersectionPosition(_edge->aPosition(), _edge->bPosition(), boundary->getLeftPosition(), boundary->getRightPosition());
	  Vertex* vertex = new Vertex(position, nullptr, true);
	  if (leftEdge)
	    {
	      //assert(boundary->getLeft() == nullptr);
	      boundary->setLeft(vertex);
	    }
	  else
	    {
	      // assert(boundary->getRight() == nullptr);
	      boundary->setRight(vertex);
	    }
	}
      catch (int i)
	{}
    }
  /*
  edges.push_back(_edge);
  Vec2f a = _edge->aPosition();
  Vertex* vertex = _edge->getA();
  bool jump = true;
  goto ACTUAL_START;
 START:
  vertex = _edge->getB();
  jump = false;
 ACTUAL_START:
  Vec2f b;
  Edge::EdgeType type = _edge->getEdgeType();
  bool leftEdge;
  if (type == Edge::eLeftFloor | type == Edge::eLeftRoof)
    {
      b = a + Vec2f(500, 0);
      leftEdge = true;
    }
  else
    {
      b = a - Vec2f(500, 0);
      leftEdge = false;
    }
  Edge* opposingEdge = findIntersectingEdge(a, &b, _edge);
  if (opposingEdge)
    {
      Vec2f a2 = opposingEdge->aPosition();
      Vec2f b2 = a2 + Vec2f((leftEdge)?-500:500,0);
      Edge* opposingOpposingEdge = findIntersectingEdge(a2, &b2, opposingEdge);
      if (opposingOpposingEdge == _edge)
	{
	  Edge* selfSplit = _edge->split(b2, nullptr);
	  edges.push_back(selfSplit);
	}
      //      else
      {
	a2 = opposingEdge->bPosition();
	b2 = a2 + Vec2f((leftEdge)?-500:500,0);
	opposingOpposingEdge = findIntersectingEdge(a2, &b2, opposingEdge);
	if (opposingOpposingEdge == _edge)
	  {
	    Edge* selfSplit = _edge->split(b2, nullptr);
	    edges.push_back(selfSplit);
	  }
      }
      Edge* newEdge = opposingEdge->split(b, nullptr);
      edges.push_back(newEdge);
    }
  if (jump)
    {
      a = _edge->bPosition();
      goto START;
      }*/
}
void WaterPhysicsSystem::createVertex(const Vec2f& _position, Edge* _a, Edge* _b, Vec2f* _bBPosition)
{
  Vertex* vertex = nullptr;
  Vertex* oldA = _a->getB();
  Vertex* oldB = _b->getA();
  if (oldA == nullptr)
    {
      if (oldB == nullptr)
        {
	  vertex = new Vertex(_position);
        }
      else
        {
	  vertex = oldB;
	  vertex->position = _position;
        }
    }
  else
    {
      vertex = oldA;
      vertex->position = _position;
    }
  assert(vertex);
  _a->setB(vertex);
  if (_bBPosition)
    _b->setA(vertex, *_bBPosition);
  else
    _b->setA(vertex);
}

Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect);

std::vector<Vec2f> WaterPhysicsSystem::getContainer(const Vec2f& _position)
{
  Vec2f a = _position;
  Vec2f b = a;
  a.x -= 10000;
  b.x += 10000;

  Edge* left = nullptr;
  float leftX;
  Edge* right = nullptr;
  float rightX;
  unsigned int edgesSize = edges.size();
  for (unsigned int i = 0; i != edgesSize; i++)
    {
      Edge* edge = edges[i];
      try
        {
	  Vec2f position = intersectionPosition(edge->aPosition(), edge->bPosition(), a, b, true, false);
	  if (position.x < _position.x)
            {
	      if (left)
                {
		  if (leftX < position.x)
                    {
		      left = edge;
		      leftX = position.x;
                    }
                }
	      else
                {
		  left = edge;
		  leftX = position.x;
                }
            }
	  else
            {
	      if (right)
                {
		  if (rightX > position.x)
                    {
		      right = edge;
		      rightX = position.x;
                    }
                }
	      else
                {
		  right = edge;
		  rightX = position.x;
                }
            }
        }
      catch (int i)
        {
        }
    }
  if (left == nullptr || right == nullptr)
    {
      assert(false);
    }
  std::vector<Vec2f> shape;
  shape.push_back({rightX, _position.y});
  while (true)
    {
      if (right == left)
        {
	  shape.push_back({leftX, _position.y});
	  return shape;
        }
      //if (right->getA()->getVertexShape() == Vertex::eLeft) /// FIXME make this get the next on the vertex
      {
	shape.push_back(right->aPosition());
	right = right->getA()->getNextOutfacing(right);
      }
      //else assert(false);
    }
}

#include <GL/gl.h>

void WaterPhysicsSystem::renderWireframe()
{
  for (unsigned int i = 0; i != edges.size(); i++)
    {
      Edge* edge = edges[i];
      glBegin(GL_LINES);
      {
	glColor3f(1,1,1);
	glVertex2f(edge->aPosition().x, edge->aPosition().y);
	glVertex2f(edge->bPosition().x, edge->bPosition().y);
      }
      glEnd();
      glBegin(GL_POINTS);
      {
	glColor3f(1,0,0);
	glVertex2f(edge->aPosition().x, edge->aPosition().y);
	glVertex2f(edge->bPosition().x, edge->bPosition().y);
      }
      glEnd();
    }
  glColor3f(0,0,1);
  for (unsigned int i = 0; i != volumes.size(); i++)
    {
      Volume* volume = volumes[i];
      Vec2f center;
      center = volume->getLeft()->aPosition();
      center += volume->getLeft()->bPosition();
      center += volume->getRight()->aPosition();
      center += volume->getRight()->bPosition();
      center /= 4.0f;
      glBegin(GL_LINES);
      {
	glVertex2f(volume->getLeft()->aPosition().x, volume->getLeft()->aPosition().y);
	glVertex2f(center.x, center.y);
	glVertex2f(volume->getRight()->aPosition().x, volume->getRight()->aPosition().y);
	glVertex2f(center.x, center.y);

	glVertex2f(volume->getRight()->bPosition().x, volume->getRight()->bPosition().y);
	glVertex2f(center.x, center.y);
	glVertex2f(volume->getLeft()->bPosition().x, volume->getLeft()->bPosition().y);
	glVertex2f(center.x, center.y);
      }
      glEnd();
    }
  glBegin(GL_LINES);
  glColor3f(1,1,0.5f);
  //  for (Boundary* boundary = boundaries.front(); boundary; boundary = boundary->getNextObject())
  for (unsigned int i = 0; i != boundaries.size(); i++)
    {
      Boundary* boundary = boundaries[i];
      if (boundary)
	{
	  Vec2f p = boundary->getLeftPosition();
	  glVertex2f(p.x, p.y);
	  p = boundary->getRightPosition();
	  glVertex2f(p.x, p.y);
	}
    }
  glEnd();
}
/*WaterPhysicsSystem::Vertex::VertexShape WaterPhysicsSystem::Vertex::getVertexShape()
  {
  Vec2f dirA = a->aPosition() - position;
  Vec2f dirB = b->bPosition() - position;
  dirA /= dirA.Length();
  dirB /= dirB.Length();
  float angleA = atan2(dirA.x, dirA.y);
  float angleB = atan2(dirB.x, dirB.y);
  float angleDiff = angleB - angleA;
  return eLeft;
  }*/

void WaterPhysicsSystem::Edge::setA(Vertex* _a)
{
  if (a)
    if (a == _a)
      return;
    else
      a->removeEdge(this);
  a = _a;
  a->addOutwardsEdge(this);
}
void WaterPhysicsSystem::Edge::setB(Vertex* _b)
{
  if (b)
    if (b == _b)
      return;
    else
      b->removeEdge(this);
  b = _b;
  b->addInwardsEdge(this);
}
void WaterPhysicsSystem::Edge::setA(Vertex* _a, const Vec2f& _b)
{
  if (a)
    a->removeEdge(this);
  a = _a;
  a->addOutwardsEdge(this, _b);
}
void WaterPhysicsSystem::Edge::setB(const Vec2f& _a, Vertex* _b)
{
  if (b)
    b->removeEdge(this);
  b = _b;
  b->addInwardsEdge(_a, this);
}
WaterPhysicsSystem::Edge* WaterPhysicsSystem::Edge::split(Vec2f _point, Boundary* _boundary)
{
  Vertex* anchor = new Vertex(_point, _boundary, true);
  Edge* edge = new Edge;
  edge->setA(anchor, bPosition());
  edge->setB(b);
  setB(anchor);
  return edge;
}
WaterPhysicsSystem::Vertex::Vertex(const Vec2f& _position, Boundary* _boundary, bool _anchor)
{
  position = _position;
  boundary = _boundary;
  anchor = _anchor;
}
void WaterPhysicsSystem::Vertex::setBoundary(Boundary* _boundary)
{
  if (boundary != _boundary)
    {
      if (boundary)
	boundary->removeVertex(this);
      boundary = _boundary;
    }
}
void WaterPhysicsSystem::Boundary::removeVertex(Vertex* _vertex)
{
  if (_vertex == left)
    {
      left = nullptr;
      //      if (right == nullptr)
	//	system->_removeBoundary(this);
//	      delete this;
    }
  else if (_vertex == right)
    {
      assert(_vertex == right);
      right = nullptr;
      //      if (left == nullptr)
	// delete this
	//	system->_removeBoundary(this);
    }
}
WaterPhysicsSystem::Edge* WaterPhysicsSystem::Vertex::getNextOutfacing(Edge* _b)
{
  for (unsigned int i = 0; i != edges.size(); i++)
    {
      if (edges[i].edge == _b)
        {
	  i++;
	  if (i == edges.size())
	    i = 0;
	  return edges[i].edge;
        }
    }
  throw -1;
}
void WaterPhysicsSystem::Vertex::addInwardsEdge(Edge* _edge)
{
  addInwardsEdge(_edge->aPosition(), _edge);
}
void WaterPhysicsSystem::Vertex::addOutwardsEdge(Edge* _edge)
{
  addOutwardsEdge(_edge, _edge->bPosition());
}
WaterPhysicsSystem::Vertex::~Vertex()
{
  assert(false);
}
WaterPhysicsSystem::Boundary::~Boundary()
{
  if (left)
    left->setBoundary(nullptr);
  if (right)
    right->setBoundary(nullptr);
  system->_removeBoundary(this);
}
void WaterPhysicsSystem::_removeBoundary(Boundary* _boundary)
{
  for (unsigned int i = 0; i != boundaries.size(); i++)
    if (boundaries[i] == _boundary)
      boundaries[i] = nullptr;
}
void WaterPhysicsSystem::Boundary::setLeft(Vertex* _left)
{
  if (_left)
    _left->setBoundary(this);
  if (left)
    left->setBoundary(nullptr);
  left = _left;
  if (left == nullptr && right == nullptr)
    delete this;
  else assert(left != right);
}
void WaterPhysicsSystem::Boundary::setRight(Vertex* _right)
{
  if (_right)
    _right->setBoundary(this);
  if (right)
    right->setBoundary(nullptr);
  right = _right;
  if (left == nullptr && right == nullptr)
    delete this;
  else assert(left != right);
}
Vec2f WaterPhysicsSystem::Boundary::getLeftPosition()
{
  if (left)
    return left->position;
  else
    {
      Vec2f ret = right->position;
      ret.x -= 100;
      return ret;
    }
}
Vec2f WaterPhysicsSystem::Boundary::getRightPosition()
{
  if (right)
    return right->position;
  else
    {
      Vec2f ret = left->position;
      ret.x += 100;
      return ret;
    }
}
void WaterPhysicsSystem::Vertex::addInwardsEdge(const Vec2f& _a, Edge* _edge)
{
  assert(_edge->getB() == this);
  Vec2f dir = _a - position;
  dir /= dir.Length();
  float angle = atan2(dir.y, dir.x);
  for (auto i = edges.begin(); i != edges.end(); i++)
    {
      if (i->angle > angle)
        {
	  edges.insert(i, {angle, _edge});
	  return;
        }
    }
  edges.push_back({angle, _edge});
}
void WaterPhysicsSystem::Vertex::addOutwardsEdge(Edge* _edge, const Vec2f& _b)
{
  assert(_edge->getA() == this);
  Vec2f dir = _b - position;
  dir /= dir.Length();
  float angle = atan2(dir.y, dir.x);
  for (auto i = edges.begin(); i != edges.end(); i++)
    {
      if (i->angle > angle)
        {
	  edges.insert(i, {angle, _edge});
	  return;
        }
    }
  edges.push_back({angle, _edge});
}
void WaterPhysicsSystem::Vertex::removeEdge(Edge* _b)
{
  for (auto i = edges.begin(); i != edges.end(); i++)
    {
      if (i->edge == _b)
        {
	  edges.erase(i);
	  if (edges.size() == 0)
	    delete this;
	  return;
        }
    }
  throw -1;
}
WaterPhysicsSystem::Edge::EdgeType WaterPhysicsSystem::Edge::getEdgeType()
{
  if (aPosition().y < bPosition().y)
    { /// Downwards pointing
      if (aPosition().x < bPosition().x)
	{
	  return eLeftFloor;
	}
      else
	{
	  return eLeftRoof;
	}
    }
  else
    { /// Upwards pointing
      if (aPosition().x < bPosition().x)
	{
	  return eRightFloor;
	}
      else
	{
	  return eRightRoof;
	}
    }
}

































