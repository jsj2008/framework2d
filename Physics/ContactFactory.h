#ifndef CONTACTFACTORY_H
#define CONTACTFACTORY_H

#include <GameObject.h>
class Contact;
class b2Contact;

class ContactFactory
{
    public:
        ContactFactory();
        virtual ~ContactFactory();
        Contact* createContact(bool _inverted);
        void filter();
        void setEvent(GameObjectBase::ActionHandle* _action, bool _A);
    protected:
    private:
        bool isFiltered;
        GameObjectBase::ActionHandle* actionA,* actionB;
};

#endif // CONTACTFACTORY_H
