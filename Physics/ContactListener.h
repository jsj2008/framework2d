#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <queue>
#include <stack>
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>
class Entity;
class Contact;
class ContactFactory;
class CollisionDatabase;

class ContactListener : public b2ContactListener
{
    public:
        ContactListener(CollisionDatabase* _database);
        virtual ~ContactListener();
        void process();
    protected:
    private:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

        Contact* contactList;
        CollisionDatabase* database;
};

#endif // CONTACTLISTENER_H
