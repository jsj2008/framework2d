#ifndef CONTACTFACTORY_H
#define CONTACTFACTORY_H

#include <GameObject.h>
class Contact;
class b2Contact;

class ContactFactory
{
    public:
        ContactFactory(bool _isFiltered);
        virtual ~ContactFactory();
        Contact* createContact(bool _inverted);
        void filter();
        void setEvent(ActionHandle* _action, bool _A);
        bool getFiltered(){return isFiltered;}
        ActionHandle* getActionA(){return actionA;}
        ActionHandle* getActionB(){return actionB;}
    protected:
    private:
        bool isFiltered;
        ActionHandle* actionA,* actionB;
};

#endif // CONTACTFACTORY_H
