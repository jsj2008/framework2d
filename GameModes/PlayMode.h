#ifndef PLAYMODE_H
#define PLAYMODE_H

#include "GameMode.h"
class b2Body;
class SelectionBox;

class PlayMode : public GameMode
{
    public:
        PlayMode(b2Body* cameraBody = 0);
        virtual ~PlayMode();
        void setBody(b2Body* cameraBody);
    protected:
    private:
        SelectionBox* selectionBox;
};

#endif // PLAYMODE_H
