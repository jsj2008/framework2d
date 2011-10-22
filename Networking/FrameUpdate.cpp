#include "FrameUpdate.h"
#include <Networking/DataStream.h>

FrameUpdate::FrameUpdate()
{
    //ctor
}

FrameUpdate::FrameUpdate(DataStream* _stream)
{
    //ctor
    _stream->decodeString<std::vector<Action>, Action>(&frameUpdates);
}

FrameUpdate::~FrameUpdate()
{
    //dtor
}

void FrameUpdate::encode(DataStream* _stream)const
{
    _stream->encodeString<std::vector<Action>, Action>(&frameUpdates);
}

void FrameUpdate::append(FrameUpdate* _update)
{
    for (unsigned short i = 0; i != _update->getActionsSize(); i++)
    {
        addAction(_update->getAction(i));
    }
}
