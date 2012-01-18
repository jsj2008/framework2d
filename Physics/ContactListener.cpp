#include "ContactListener.h"
#include <Entities/Entity.h>
#include <Physics/CollisionObject.h>
#include <Entities/CollisionDatabase.h>
#include <Physics/ContactFactory.h>
#include <Physics/Contact.h>
#include <cstring>

ContactListener::ContactListener(CollisionDatabase* _database)
{
    //ctor
    contactList = nullptr;
    database = _database;
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::BeginContact(b2Contact* _contact)
{
    CollisionResponse* a = _contact->GetFixtureA()->GetFilterData().response;
    CollisionResponse* b = _contact->GetFixtureB()->GetFilterData().response;
    if (a != nullptr && b != nullptr)
    {
        unsigned short catA = a->getId();
        unsigned short catB = b->getId();
        //ContactFactory* factory = contactFactories[catA][catB];
        //if (factory != nullptr)
        {
            //Contact* contact = factory->createContact(_contact, catA > catB);
            Contact* contact = database->createContact(catA, catB);
            if (contact != nullptr)
            {
                contact->setContact(_contact);
                _contact->SetUserData(contact);
                contact->insertInFront(contactList);
                contactList = contact;
            }
        }
    }
}

void ContactListener::EndContact(b2Contact* _contact)
{
    Contact* contact = static_cast<Contact*>(_contact->GetUserData());
    if (contact != nullptr)
    {
        if (contact == contactList)
        {
            contactList = contactList->next;
            if (contactList != nullptr)
                contactList->prev = nullptr;
        }
        else
        {
            if (contact->prev != nullptr)
                contact->prev->next = contact->next;
            else
                contactList = contact->next;
            if (contact->next != nullptr)
                contact->next->prev = contact->prev;
        }
        delete contact;
    }
}
void ContactListener::PreSolve(b2Contact* _contact, const b2Manifold* oldManifold)
{
    Contact* contact = static_cast<Contact*>(_contact->GetUserData());
    if (contact != nullptr)
    {
        _contact->SetEnabled(contact->preSolveInterface(oldManifold));
    }
}

void ContactListener::PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse)
{
    Contact* contact = static_cast<Contact*>(_contact->GetUserData());
    if (contact != nullptr)
    {
        contact->postSolveInterface(_impulse);
    }
}
void ContactListener::process()
{
    for (Contact* contact = contactList; contact != nullptr; contact = contact->next)
    {
        contact->update();
    }
}
