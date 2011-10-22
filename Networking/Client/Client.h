#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
class ServerToClientMessageFactory;
class ClientToServerMessage;
class FrameUpdate;

class Client
{
    public:
        Client(const char* _serverIp, int _serverPort);
        virtual ~Client();
        void update(const FrameUpdate& _sendingUpdate);
        void send(ClientToServerMessage* _message);
    protected:
    private:
        template <typename Message>
        void addServerMessageFactory();
        int transmissionSocket;
        std::vector<ServerToClientMessageFactory*> serverMessageFactories;
};

#endif // CLIENT_H
