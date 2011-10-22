#include "FrameUpdateMessage.h"
#include <Networking/Server/Server.h>

FrameUpdateMessage::FrameUpdateMessage(const FrameUpdate& _update)
{
    //ctor
    update = _update;
}
FrameUpdateMessage::FrameUpdateMessage(DataStream* _stream)
:update(_stream)
{
    //ctor
}

FrameUpdateMessage::~FrameUpdateMessage()
{
    //dtor
}

void FrameUpdateMessage::encode(DataStream* _stream)
{
    update.encode(_stream);
}
void FrameUpdateMessage::serverProcess(Server* _server, ServerEntity* _client)
{
    _server->addUpdates(&update);
}
