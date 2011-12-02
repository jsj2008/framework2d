#include "Contact.h"
#include <Physics/CollisionObject.h>
#include <Box2D/Box2D.h>

Contact::Contact(bool _inverted, bool _collides, GameObjectBase::ActionHandle* _actionA, GameObjectBase::ActionHandle* _actionB)
{
    //ctor
    contact = nullptr;
    inverted = _inverted;
    collides = _collides;
    next = prev = nullptr;
    actionA = _actionA;
    actionB = _actionB;
}

Contact::~Contact()
{
    //dtor
}
void Contact::setContact(b2Contact* _contact)
{
    contact = _contact;
    //assert(getObjectA()); /// FIXME put these back in. Need two-body bodies like the character to be handled correctly
    //assert(getObjectB());
}

Contact::ManifoldInterface::ManifoldInterface(const b2Manifold* _manifold, bool _inverted)
{
    manifold = _manifold;
    inverted = _inverted;
}
Contact::ImpulseInterface::ImpulseInterface(const b2ContactImpulse* _impulse, bool _inverted)
{
    impulse = _impulse;
    inverted = _inverted;
}

bool Contact::preSolveInterface(const b2Manifold* _oldManifold) /// Returns filtering flag
{
    ManifoldInterface oldManifold(_oldManifold, inverted);
    if (!inverted)
    {
        GameObjectBase* objectA = getObjectA();
        if (actionA != nullptr && objectA != nullptr) /// FIXME remove the null checks on object, they should always have one
        {
            CollisionObject object(contact->GetFixtureA(), contact->GetFixtureB());
            actionA->execute<CollisionObject>(objectA, &object);
        }
        GameObjectBase* objectB = getObjectB();
        if (actionB != nullptr && objectB != nullptr)
        {
            CollisionObject object(contact->GetFixtureB(), contact->GetFixtureA());
            actionB->execute<CollisionObject>(objectB, &object);
        }
    }
    else
    {
        GameObjectBase* objectA = getObjectA();
        if (actionA != nullptr && objectA != nullptr)
        {
            CollisionObject object(contact->GetFixtureB(), contact->GetFixtureA());
            actionA->execute<CollisionObject>(objectA, &object);
        }
        GameObjectBase* objectB = getObjectB();
        if (actionB != nullptr && objectB != nullptr)
        {
            CollisionObject object(contact->GetFixtureA(), contact->GetFixtureB());
            actionB->execute<CollisionObject>(objectB, &object);
        }
    }
    preSolve(&oldManifold);
    return collides;
}

void Contact::postSolveInterface(const b2ContactImpulse* _impulse) /// Returns filtering flag
{
    ImpulseInterface impulse(_impulse, inverted);
    postSolve(&impulse);
}

void Contact::preSolve(ManifoldInterface* _oldManifold)
{
    _oldManifold = _oldManifold; /// Removes annoying gcc warning
}
void Contact::postSolve(ImpulseInterface* _impulse)
{
    _impulse = _impulse; /// Removes annoying gcc warning
}

void Contact::insertInFront(Contact* _next)
{
    if (_next != nullptr)
    {
        prev = _next->prev;
        next = _next;
        _next->prev = this;
    }
}
GameObjectBase* Contact::getObjectA()
{
    b2Fixture* fixture = (inverted)? contact->GetFixtureB() : contact->GetFixtureA();
    return static_cast<GameObjectBase*>(fixture->GetBody()->GetUserData());
}
GameObjectBase* Contact::getObjectB()
{
    b2Fixture* fixture = (inverted)? contact->GetFixtureA() : contact->GetFixtureB();
    return static_cast<GameObjectBase*>(fixture->GetBody()->GetUserData());
}












