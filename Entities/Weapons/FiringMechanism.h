#ifndef FIRINGMECHANISM_H
#define FIRINGMECHANISM_H

#include <GameObject.h>
class Vec2f;

class FiringMechanism : public GameObject<FiringMechanism>
{
    public:
        FiringMechanism();
        virtual ~FiringMechanism();
        static void registerActions();
        virtual bool fireBegin(const Vec2f& source, const Vec2f& position){return false;}
        virtual bool fireMove(const Vec2f& source, const Vec2f& position){return false;}
        virtual bool fireEnd(const Vec2f& source, const Vec2f& position)=0;

        static std::string name()
        {
            return "FiringMechanism";
        }
    protected:
    private:
};

#endif // FIRINGMECHANISM_H
