#include "ContactFactory.h"
#include <Physics/Contact.h>

ContactFactory::ContactFactory()
{
    //ctor
    isFiltered = false;
    actionA = actionB = nullptr;
}

ContactFactory::~ContactFactory()
{
    //dtor
}

Contact* ContactFactory::createContact(bool _inverted)
{
    return new Contact(_inverted, !isFiltered, actionA, actionB);
}

void ContactFactory::filter()
{
    isFiltered = true;
}

void ContactFactory::setEvent(ActionHandle* _action, bool _A)
{
    if (_A)
        actionA = _action;
    else
        actionB = _action;
}
