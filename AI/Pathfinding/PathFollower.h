#ifndef PATHFOLLOWER_H
#define PATHFOLLOWER_H

class Vec2f;

class PathFollower
{
    public:
        PathFollower();
        virtual ~PathFollower();
        void update(const Vec2f& position);
    protected:
    private:
};

#endif // PATHFOLLOWER_H
