#ifndef SERVERTOCLIENTMESSAGE_H
#define SERVERTOCLIENTMESSAGE_H

#include <Networking/NetworkMessage.h>
class Client;

class ServerToClientMessage : public NetworkMessage
{
    public:
        ServerToClientMessage();
        virtual ~ServerToClientMessage();
        virtual unsigned short getServerToClientMessageId()=0;
        virtual void clientProcess(Client* _client, unsigned short _entityKey)=0; /// Consider this 'final' in the Intermediary/MultiCast class. Please don't override it
    protected:
        static unsigned short getNewMessageId();
    private:
};

template <typename DerivedMessage>
class ServerToClientMessageIntermediary : public ServerToClientMessage
{
    public:
        unsigned short getServerToClientMessageId(){return messageId;}
        static unsigned short staticServerToClientGetMessageId(){return messageId;}
        void clientProcess(Client* _client, unsigned short _entityKey);
    protected:
        virtual void virtualClientProcess(Client* _client, unsigned short _entityKey){}
    private:
        static unsigned int messageId;
};

#include <Networking/Client/ServerMessageEvent.h>
#include <Events/SingletonEvents/SingletonEventListener.h>
template <typename DerivedMessage>
unsigned int ServerToClientMessageIntermediary<DerivedMessage>::messageId = getNewMessageId();

template <typename DerivedMessage>
void ServerToClientMessageIntermediary<DerivedMessage>::clientProcess(Client* _client, unsigned short _entityKey)
{
    ServerMessageEvent<DerivedMessage> message;
    message.trigger();
    virtualClientProcess(_client, _entityKey);
}
#endif // SERVERTOCLIENTMESSAGE_H
