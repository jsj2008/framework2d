#ifndef CONTACT_H
#define CONTACT_H

#include <GameObject.h>
class Entity;
class b2Contact;
class b2Manifold;
class b2ContactImpulse;
class ContactFactory;

class Contact
{
    public:
        Contact(bool _inverted, ContactFactory* _factoryHandle);
        void setContact(b2Contact* _contact);
        virtual ~Contact();
    protected:
        /// These flip if inverted is true
        Entity* getObjectA();
        Entity* getObjectB();
        void setCollides(bool _collides);
        class ManifoldInterface
        {
            public:
                ManifoldInterface(const b2Manifold* _manifold, bool _inverted);
            private:
                const b2Manifold* manifold;
                bool inverted;
        };
        virtual void preSolve(ManifoldInterface* _oldManifold);
        class ImpulseInterface
        {
            public:
                ImpulseInterface(const b2ContactImpulse* _impulse, bool _inverted);
            private:
                const b2ContactImpulse* impulse;
                bool inverted;
        };
        virtual void postSolve(ImpulseInterface* _impulse);
    private:
        b2Contact* contact;
        bool inverted;
        ContactFactory* factoryHandle;

        friend class ContactListener;
        bool preSolveInterface(const b2Manifold* _oldManifold); /// Returns filtering flag
        void postSolveInterface (const b2ContactImpulse* _impulse);
        virtual void update(){} /// Called every tick
        void insertInFront(Contact* _next);
        Contact* next,* prev;
};

#endif // CONTACT_H
