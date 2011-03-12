#ifndef ZOMBIEBRAIN_H
#define ZOMBIEBRAIN_H

#include <AI/Brain.h>
class PathFollower;

class ZombieBrain : public Brain
{
    public:
        ZombieBrain();
        virtual ~ZombieBrain();
        void update();
    protected:
    private:
        PathFollower* follower;
};

#endif // ZOMBIEBRAIN_H
