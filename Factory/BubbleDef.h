#ifndef BUBBLEDEF_H
#define BUBBLEDEF_H

#include <Factory/FactoryDef.h>
#include <Entities/Bubble.h>

class BubbleDef : public FactoryDef
{
    public:
        BubbleDef();
        float radius;
        Bubble::BubbleType type;
};

#endif // BUBBLEDEF_H
