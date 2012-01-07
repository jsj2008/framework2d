#ifndef SUCTIONBUBBLE_H
#define SUCTIONBUBBLE_H

#include <Entities/Bubble.h>
class BodyPart;

class SuctionBubble : public Bubble
{
    public:
        SuctionBubble();
        virtual ~SuctionBubble();
        BubbleType getBubbleType(){return eSuctionBubbleType;}
        static std::string name()
        {
            return "SuctionBubble";
        }
    protected:
    private:
        void affectBody(BodyPart* body, Vec2f directionTo);
};

#endif // SUCTIONBUBBLE_H
