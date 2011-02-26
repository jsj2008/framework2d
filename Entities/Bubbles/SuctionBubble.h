#ifndef SUCTIONBUBBLE_H
#define SUCTIONBUBBLE_H

#include <Entities/Bubble.h>


class SuctionBubble : public Bubble
{
    public:
        SuctionBubble();
        virtual ~SuctionBubble();
        BubbleType getBubbleType(){return eSuctionBubbleType;}
    protected:
    private:
        void affectBody(b2Body* body, Vec2f directionTo);
};

#endif // SUCTIONBUBBLE_H
