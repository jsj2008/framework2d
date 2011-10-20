#ifndef FIRINGMECHANISM_H
#define FIRINGMECHANISM_H

class Vec2f;

class FiringMechanism
{
    public:
        FiringMechanism();
        virtual ~FiringMechanism();
        virtual bool fireBegin(const Vec2f& source, const Vec2f& position){return false;}
        virtual bool fireMove(const Vec2f& source, const Vec2f& position){return false;}
        virtual bool fireEnd(const Vec2f& source, const Vec2f& position)=0;
    protected:
    private:
};

#endif // FIRINGMECHANISM_H
