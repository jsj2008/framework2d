#include "Server.h"
#include <Networking/Server/ServerEntity.h>
#include <Networking/DataStream.h>
#include <Networking/ClientToServer/ClientInitialisationMessage.h>
#include <Networking/Server/ClientToServerMessageFactory.h>
#include <Networking/ServerToClient/FrameUpdateMessage.h>
#include <Log/Log.h>
#include <cstdio>
#include <sys/types.h>
#include <netinet/in.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

template <typename Message>
class TemplateClientToServerMessageFactory: public ClientToServerMessageFactory
{
    public:
        TemplateClientToServerMessageFactory()
        {
        }
        ClientToServerMessage* create(DataStream* _stream)
        {
            return new Message(_stream);
        }
};


Server::Server(int _serverPort)
{
    //ctor
	sockaddr_in Server;
	int sa_size = sizeof(sockaddr);
	/*WSADATA w;
	int error = WSAStartup (0x0202,&w);
	if (error)
	{
		printf("Error:  You need WinSock 2.2!\n");
		return;
	}
	if (w.wVersion!=0x0202)
	{
		printf("Error:  Wrong WinSock version!\n");
		WSACleanup ();
		return;
	}*/


	newClientListen = socket (AF_INET,SOCK_STREAM,0);
	Server.sin_family = AF_INET;
	Server.sin_port = htons (_serverPort);
	Server.sin_addr.s_addr = htonl (INADDR_ANY);

	//notice the different byte order for network
	u_short PortNo;
	PortNo = (Server.sin_port >> 8)|(Server.sin_port << 8);
	printf("My PORT address is: %d\n", (int)PortNo);


	if (bind(newClientListen, (sockaddr* )&Server, sizeof(Server)) < 0)
	{
        g_Log.error("Unable to bind socket");
	}
    /// Linux
    int nonBlocking = 1;
    if ( fcntl( newClientListen, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
    {
        g_Log.error("Failed to set non-blocking socket");
    }
    /// Windows
    /*
	int nonBlocking = 1;
	ioctlsocket(newClientListen, FIONBIO, &nonBlocking);*/

	if (listen(newClientListen, 1) < 0)
	{
        g_Log.error("Unable to listen");
	}

    addClientMessageFactory<ClientInitialisationMessage>();
    addClientMessageFactory<FrameUpdateMessage>();
}

Server::~Server()
{
    //dtor
}

template <typename Message>
void Server::addClientMessageFactory()
{
    unsigned short id = Message::staticClientToServerGetMessageId();
    if (clientMessageFactories.size() <= id)
        clientMessageFactories.resize(id+1);

    auto factory = new TemplateClientToServerMessageFactory<Message>;
	clientMessageFactories[id] = factory;
}
void Server::update()
{
    int newSocket;
    while (true)
    {
        sockaddr client;
        socklen_t sa_size;
        newSocket = accept (newClientListen, &client, &sa_size);
        if (newSocket >= 0)
        {
            //DWORD nonBlocking = 1;
            //ioctlsocket(newSocket, FIONBIO, &nonBlocking);
            int nonBlocking = 1;
            if ( fcntl( newSocket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
            {
                g_Log.error("Failed to set non-blocking socket");
            }
            if (unusedClients.empty())
            {
                clients.push_back(new ServerEntity(newSocket, clients.size()));
            }
            else
            {
                int position = unusedClients.top();
                unusedClients.pop();
                clients.push_back(new ServerEntity(newSocket, position));
            }
            printf("Client has connected\n");
        }
        else break;
    }

    for (unsigned int i = 0; i != clients.size(); i++)
    {
        ServerEntity* entity = clients[i];
        if (entity != nullptr && !(entity)->process(this))
        {
            printf("Client \"%s\" has disconnected\n", entity->getName().c_str());
            delete entity;
            clients[i] = nullptr;
        }
    }

    if (nextUpdate.getActionsSize() != 0)
    {
        /*char log[256];
        sprintf(log, "Updates: %d", nextUpdate.getActionsSize());
        g_Log.message(log);*/
        FrameUpdateMessage message(nextUpdate);
        char buffer[256];
        DataStream stream(buffer, 0);
        stream.encode<unsigned short>(message.getServerToClientMessageId());
        stream.encode<unsigned short>(0);
        message.encode(&stream);
        multicast(&stream);
        nextUpdate.clear();
    }
}

void Server::process(ServerEntity* _client, DataStream* _stream)
{
    unsigned short messageType = _stream->decode<unsigned short>();
    ClientToServerMessageFactory* factory = clientMessageFactories[messageType];
    int startIter = _stream->getIter();
    ClientToServerMessage* message = factory->create(_stream);
    assert(message->getClientToServerMessageId() == messageType);
    MultiCastMessage* multiCastMessage = dynamic_cast<MultiCastMessage*>(message);
    if (multiCastMessage != nullptr && multiCastMessage->directCastToClients())
    {
        message->serverProcess(this, _client);

        char buffer[256];
        DataStream stream(buffer, 0);
        stream.encode<unsigned short>(multiCastMessage->getServerToClientMessageId());
        stream.encode<unsigned short>(_client->getEntityKey());
        //stream.append(_stream, startIter);
        message->encode(&stream);
        multicast(&stream);
    }
    else
    {
        message->serverProcess(this, _client);
    }
    delete message;
}

void Server::multicast(DataStream* _stream)
{
    for (unsigned int i = 0; i != clients.size(); i++)
    {
        ServerEntity* entity = clients[i];
        if (entity != nullptr)
        {
            entity->send(_stream);
        }
    }
}
void Server::addUpdates(FrameUpdate* _update)
{
    nextUpdate.append(_update);
}
