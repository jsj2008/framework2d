#include "Contact.h"
#include <Physics/CollisionObject.h>
#include <Physics/ContactFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Entities/Entity.h>
#include <Box2D/Box2D.h>

Contact::Contact(bool _inverted, ContactFactory* _factoryHandle)
{
    //ctor
    contact = nullptr;
    inverted = _inverted;
    next = prev = nullptr;
    factoryHandle = _factoryHandle;
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
        Entity* objectA = getObjectA();
        if (factoryHandle->getActionA() != nullptr && objectA != nullptr) /// FIXME remove the null checks on object, they should always have one
        {
            CollisionObject object(contact->GetFixtureA(), contact->GetFixtureB());
            factoryHandle->getActionA()->execute<CollisionObject>(objectA, &object);
        }
        Entity* objectB = getObjectB();
        if (factoryHandle->getActionB() != nullptr && objectB != nullptr)
        {
            CollisionObject object(contact->GetFixtureB(), contact->GetFixtureA());
            factoryHandle->getActionB()->execute<CollisionObject>(objectB, &object);
        }
    }
    else
    {
        GameObjectBase* objectA = getObjectA();
        if (factoryHandle->getActionA() != nullptr && objectA != nullptr)
        {
            CollisionObject object(contact->GetFixtureB(), contact->GetFixtureA());
            factoryHandle->getActionA()->execute<CollisionObject>(objectA, &object);
        }
        GameObjectBase* objectB = getObjectB();
        if (factoryHandle->getActionB() != nullptr && objectB != nullptr)
        {
            CollisionObject object(contact->GetFixtureA(), contact->GetFixtureB());
            factoryHandle->getActionB()->execute<CollisionObject>(objectB, &object);
        }
    }
    preSolve(&oldManifold);
    return factoryHandle->getFiltered();
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
Entity* Contact::getObjectA()
{
    b2Fixture* fixture = (inverted)? contact->GetFixtureB() : contact->GetFixtureA();
    return fixture->getBodyPart()->getEntity();
}
Entity* Contact::getObjectB()
{
    b2Fixture* fixture = (inverted)? contact->GetFixtureA() : contact->GetFixtureB();
    return fixture->getBodyPart()->getEntity();
}












