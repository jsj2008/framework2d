#ifndef CLIENTINITIALISATIONMESSAGE_H
#define CLIENTINITIALISATIONMESSAGE_H

#include <Networking/MultiCastMessage.h>
#include <Types/Vec2f.h>
class DataStream;

class ClientInitialisationMessage : public MultiCastMessageIntermediary<ClientInitialisationMessage>
{
    public:
        ClientInitialisationMessage(DataStream* _stream); /// Called in server
        ClientInitialisationMessage(const std::string& _name, const Vec2f& _position, unsigned short _entityKey); /// Called in client
        virtual ~ClientInitialisationMessage();
        void serverProcess(Server* _server, ServerEntity* _client);
        void virtualClientProcess(Client* _client, unsigned short _entityKey);
        bool directCastToClients(){return true;}
        unsigned short getEntityKey(){return entityKey;}
        void encode(DataStream* _stream);
    protected:
    private:
        std::string name;
        Vec2f position;
        unsigned short entityKey;
};

#endif // CLIENTINITIALISATIONMESSAGE_H
