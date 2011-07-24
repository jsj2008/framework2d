#ifndef SUCTIONBUBBLE_H
#define SUCTIONBUBBLE_H

#include <Entities/Bubble.h>


class SuctionBubble : public Bubble
{
    public:
        SuctionBubble(Skin* _skin);
        virtual ~SuctionBubble();
        BubbleType getBubbleType(){return eSuctionBubbleType;}
        static std::string name()
        {
            return "SuctionBubble";
        }
    protected:
    private:
        void affectBody(b2Body* body, Vec2f directionTo);
};

#endif // SUCTIONBUBBLE_H
