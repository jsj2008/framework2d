#ifndef PLAYERINPUTBRAIN_H
#define PLAYERINPUTBRAIN_H

#include "Brain.h"
#include <Input/Mouse/InputContext.h>
#include <Events/EventListener.h>
#include <Events/Events/ButtonPressEvent.h>
#include <Events/Events/ButtonReleaseEvent.h>
#include <Events/InstanceEvents/InstanceEventListener.h>
#include <map>
class PathFollower;
class NetworkedPlayerControl;

class PlayerInputBrain : public Brain, public InstanceEventListener<ButtonPressEvent>, public InstanceEventListener<ButtonReleaseEvent>, public InputContext
{
    public:
        PlayerInputBrain(unsigned short _entityKey, std::vector<std::string> controls);
        virtual ~PlayerInputBrain();
        bool trigger(ButtonPressEvent* _event);
        bool trigger(ButtonReleaseEvent* _event);
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void activate();
        void update();
    protected:
    private:
        PathFollower* follower;
        NetworkedPlayerControl* networkControl;
        std::map<unsigned int, unsigned char> buttonActionMap;
};

#endif // PLAYERINPUTBRAIN_H
