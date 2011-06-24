#include "Traversable.h"
#ifndef NULL
#define NULL 0
#endif
Traversable::Traversable()
{
    //ctor
    next = NULL;
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
            *prevNext = NULL;
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
