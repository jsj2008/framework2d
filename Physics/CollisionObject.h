#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

class b2Fixture;
class CollisionObject
{
    public:
        CollisionObject(b2Fixture* _me, b2Fixture* _other);
        virtual ~CollisionObject();
        unsigned short getCollisionCategory();
        b2Fixture* getMe(){return me;}
        b2Fixture* getOther(){return other;}
    protected:
    private:
        b2Fixture* me,* other;
};

#endif // COLLISIONOBJECT_H
