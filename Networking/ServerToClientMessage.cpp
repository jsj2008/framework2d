#include "ServerToClientMessage.h"

ServerToClientMessage::ServerToClientMessage()
{
    //ctor
}

ServerToClientMessage::~ServerToClientMessage()
{
    //dtor
}

unsigned short ServerToClientMessage::getNewMessageId()
{
    static unsigned short id = 0;
    return id++;
}
