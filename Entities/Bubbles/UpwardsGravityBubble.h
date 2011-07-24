#ifndef UpwardsGravityBubble_H
#define UpwardsGravityBubble_H

#include <Entities/Bubble.h>


class UpwardsGravityBubble : public Bubble
{
    public:
        UpwardsGravityBubble(Skin* _skin);
        virtual ~UpwardsGravityBubble();
        BubbleType getBubbleType(){return eUpwardsGravityBubbleType;}
        static std::string name()
        {
            return "UpwardsGravityBubble";
        }
    protected:
    private:
        void affectBody(b2Body* body, Vec2f directionTo);
};

#endif // UpwardsGravityBubble_H
