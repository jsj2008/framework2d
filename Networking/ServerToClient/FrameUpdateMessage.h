#ifndef FRAMEUPDATEMESSAGE_H
#define FRAMEUPDATEMESSAGE_H

#include <Networking/MultiCastMessage.h>
#include <Networking/FrameUpdate.h>

class FrameUpdateMessage : public MultiCastMessageIntermediary<FrameUpdateMessage>
{
    public:
        FrameUpdateMessage(const FrameUpdate& _update);
        FrameUpdateMessage(DataStream* _stream);
        virtual ~FrameUpdateMessage();
        void encode(DataStream* _stream);
        void serverProcess(Server* _server, ServerEntity* _client);
        FrameUpdate* getUpdate(){return &update;}
    protected:
    private:
        FrameUpdate update;
};

#endif // FRAMEUPDATEMESSAGE_H
