#include "ClientToServerMessage.h"
#include <Networking/DataStream.h>
#include <Networking/Client/Client.h>

ClientToServerMessage::ClientToServerMessage()
{
    //ctor
}

ClientToServerMessage::~ClientToServerMessage()
{
    //dtor
}

unsigned short ClientToServerMessage::getNewMessageId()
{
    static unsigned short id = 0;
    return id++;
}

