#include "Traversable.h"

Traversable::Traversable()
{
    //ctor
    next = nullptr;
}

Traversable::~Traversable()
{
    //dtor
}

void Traversable::traverse(Traversable** prevNext)
{
    if (!update()) /// Virtual function that returns a death flag
    { /// Death
        if (next)
        {
            Traversable* localNext = next;
            delete this;
            localNext->traverse(prevNext);
        }
        else
        {
            *prevNext = nullptr;
            delete this;
        }
    }
    else
    { /// This node stays alive, for now
        *prevNext = this;
        if (next)
        {
            next->traverse(&next);
        }
    }
}
