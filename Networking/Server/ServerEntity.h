#ifndef ServerEntity_H
#define ServerEntity_H

#include <string>
class Server;
class ServerEntityInitialisationMessage;
class DataStream;

class ServerEntity
{
    public:
        ServerEntity(int _socket, unsigned short _entityKey);
        virtual ~ServerEntity();
        void initialise(const std::string& _name);
        bool process(Server* _server);
        void send(DataStream* _stream);
        const std::string& getName(){return name;}
        unsigned short getEntityKey(){return entityKey;}
    protected:
    private:
        int socket;
        unsigned short entityKey;
        std::string name;
};

#endif // ServerEntity_H
