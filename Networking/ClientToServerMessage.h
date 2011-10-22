#ifndef CLIENTTOSERVERMESSAGE_H
#define CLIENTTOSERVERMESSAGE_H

#include <Networking/NetworkMessage.h>
class ServerEntity;
class Client;
class Server;
class DataStream;

class ClientToServerMessage : public NetworkMessage
{
    public:
        ClientToServerMessage();
        virtual ~ClientToServerMessage();
        virtual void serverProcess(Server* _server, ServerEntity* _client)=0;
        virtual unsigned short getClientToServerMessageId()=0;
        virtual void encode(DataStream* _stream)=0;
    protected:
        static unsigned short getNewMessageId();
    private:
};

template <typename DerviedMessage>
class ClientToServerMessageIntermediary : public ClientToServerMessage
{
    public:
        unsigned short getClientToServerMessageId(){return messageId;}
        static unsigned short staticClientToServerGetMessageId(){return messageId;}
    private:
        static unsigned int messageId;
};
template <typename DerviedMessage>
unsigned int ClientToServerMessageIntermediary<DerviedMessage>::messageId = getNewMessageId();
#endif // CLIENTTOSERVERMESSAGE_H
