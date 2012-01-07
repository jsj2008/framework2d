#ifndef MULTICASTMESSAGE_H
#define MULTICASTMESSAGE_H

#include <Networking/ClientToServerMessage.h>
#include <Networking/ServerToClientMessage.h>

class MultiCastMessage : public ClientToServerMessage, public ServerToClientMessage
{
    public:
        MultiCastMessage();
        virtual ~MultiCastMessage();
        virtual bool directCastToClients(){return false;}
    protected:
    private:
};

template <typename DerviedMessage>
class MultiCastMessageIntermediary : public MultiCastMessage
{
    public:
        unsigned short getServerToClientMessageId(){return serverToClientMessageId;}
        static unsigned short staticServerToClientGetMessageId(){return serverToClientMessageId;}

        unsigned short getClientToServerMessageId(){return clientToServerMessageId;}
        static unsigned short staticClientToServerGetMessageId(){return clientToServerMessageId;}

        void clientProcess(Client* _client, unsigned short _entityKey);

    private:
        static unsigned int clientToServerMessageId;
        static unsigned int serverToClientMessageId;

        virtual void virtualClientProcess(Client* _client, unsigned short _entityKey){}
};


#include <Networking/Client/ServerMessageEvent.h>

template <typename DerviedMessage>
unsigned int MultiCastMessageIntermediary<DerviedMessage>::serverToClientMessageId = ServerToClientMessage::getNewMessageId();

template <typename DerviedMessage>
unsigned int MultiCastMessageIntermediary<DerviedMessage>::clientToServerMessageId = ClientToServerMessage::getNewMessageId();


template <typename DerivedMessage>
void MultiCastMessageIntermediary<DerivedMessage>::clientProcess(Client* _client, unsigned short _entityKey)
{
    ServerMessageEvent<DerivedMessage> message(this);
    message.trigger();
    virtualClientProcess(_client, _entityKey);
}
#endif // MULTICASTMESSAGE_H
