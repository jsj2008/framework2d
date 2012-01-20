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
        void setEvent(ActionHandle* _action, bool _A);
    protected:
    private:
        bool isFiltered;
        ActionHandle* actionA,* actionB;
};

#endif // CONTACTFACTORY_H
