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
        virtual BubbleType getBubbleType()=0; /// Should I combine these types? Its odd, but its useful
        EntityType getType(){return eBubbleEntityType;}
    protected:
        virtual ~Bubble();
    private:
        virtual void affectBody(b2Body* body, Vec2f directionTo)=0;
};

#endif // BUBBLE_H
