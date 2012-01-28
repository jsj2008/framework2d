#include "ContactFactory.h"
#include <Physics/Contact.h>

ContactFactory::ContactFactory(bool _isFiltered)
{
    //ctor
    isFiltered = _isFiltered;
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
    isFiltered = true;
}

void ContactFactory::setEvent(ActionHandle* _action, bool _A)
{
    if (_A)
        actionA = _action;
    else
        actionB = _action;
}
