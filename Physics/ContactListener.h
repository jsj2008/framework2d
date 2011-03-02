#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>


class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();
    protected:
    private:
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // CONTACTLISTENER_H
