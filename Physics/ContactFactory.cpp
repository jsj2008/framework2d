#include "ContactFactory.h"
#include <Physics/Contact.h>

ContactFactory::ContactFactory()
{
    //ctor
    isFiltered = true;
    actionA = actionB = nullptr;
}

ContactFactory::~ContactFactory()
{
    //dtor
}

Contact* ContactFactory::createContact(bool _inverted)
{
    return new Contact(_inverted, this);
}

void ContactFactory::filter()
{
    isFiltered = false;
}

void ContactFactory::setEvent(ActionHandle* _action, bool _A)
{
    if (_A)
        actionA = _action;
    else
        actionB = _action;
}
