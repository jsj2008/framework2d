#ifndef SERVERMESSAGEEVENT_H
#define SERVERMESSAGEEVENT_H

#include <Events/SingletonEvents/SingletonEvent.h>

template <typename MessageType>
class ServerMessageEvent : public SingletonEvent<ServerMessageEvent<MessageType>>
{
    public:
        ServerMessageEvent(MessageType* _message);
        virtual ~ServerMessageEvent();
        MessageType* getMessage(){return message;}
    protected:
    private:
        MessageType* message;
};


template <typename MessageType>
ServerMessageEvent<MessageType>::ServerMessageEvent(MessageType* _message)
{
    //ctor
    message = _message;
}

template <typename MessageType>
ServerMessageEvent<MessageType>::~ServerMessageEvent()
{
    //dtor
}

#endif // SERVERMESSAGEEVENT_H
