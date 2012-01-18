#ifndef SERVER_H
#define SERVER_H

#include <Networking/FrameUpdate.h>
#include <vector>
#include <stack>
class ServerEntity;
class DataStream;
class ClientToServerMessageFactory;

class Server
{
    public:
        Server(int _serverPort);
        virtual ~Server();
        void update();
        void process(ServerEntity* _client, DataStream* _stream);
        void multicast(DataStream* _stream);
        void multicast(ServerEntity* _exception, DataStream* _stream);
        void addUpdates(FrameUpdate* _update);
        void bringUpToSpeed(ServerEntity* _client);
    protected:
    private:
        std::vector<ServerEntity*> clients;
        std::stack<ServerEntity*> newlyInitedClients;
        std::stack<unsigned int> unusedClients;
        std::vector<ClientToServerMessageFactory*> clientMessageFactories;
        template <typename Message>
        void addClientMessageFactory();
        int newClientListen;
        //FrameUpdate nextUpdate;
};

#endif // SERVER_H
