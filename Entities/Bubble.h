#ifndef BUBBLE_H
#define BUBBLE_H

#include <Entities/Entity.h>
#include <Types/Vec2f.h>

class Bubble : public Entity
{
    public:
        Bubble();
        void update();
        enum BubbleType
        {
            eSuctionBubbleType,
            eUpwardsGravityBubbleType,
            eBubbleTypesMax
        };
        virtual BubbleType getBubbleType()=0;
    protected:
        virtual ~Bubble();
    private:
        virtual void affectBody(BodyPart* body, Vec2f directionTo)=0;
};

#endif // BUBBLE_H
