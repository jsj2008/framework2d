#ifndef UpwardsGravityBubble_H
#define UpwardsGravityBubble_H

#include <Entities/Bubble.h>


class UpwardsGravityBubble : public Bubble
{
    public:
        UpwardsGravityBubble();
        virtual ~UpwardsGravityBubble();
        BubbleType getBubbleType(){return eUpwardsGravityBubbleType;}
    protected:
    private:
        void affectBody(b2Body* body, Vec2f directionTo);
};

#endif // UpwardsGravityBubble_H
