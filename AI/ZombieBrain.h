#ifndef ZOMBIEBRAIN_H
#define ZOMBIEBRAIN_H

#include <AI/Brain.h>


class ZombieBrain : public Brain
{
    public:
        ZombieBrain();
        virtual ~ZombieBrain();
        void update();
    protected:
    private:
};

#endif // ZOMBIEBRAIN_H
