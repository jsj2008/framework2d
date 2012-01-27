#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

class BodyPart;

class CollisionObject
{
    public:
        CollisionObject(BodyPart* _me, BodyPart* _other);
        virtual ~CollisionObject();
        unsigned short getCollisionCategory();
        BodyPart* getMe(){return me;}
        BodyPart* getOther(){return other;}
    protected:
    private:
        BodyPart* me,* other;
};

#endif // COLLISIONOBJECT_H
