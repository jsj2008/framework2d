#include "Client.h"
#include <Networking/DataStream.h>
#include <Networking/ClientToServer/ClientInitialisationMessage.h>
#include <Networking/Client/ServerToClientMessageFactory.h>
#include <Networking/ServerToClient/FrameUpdateMessage.h>
#include <Networking/FrameUpdate.h>
#include <Log/Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

template <typename Message>
class TemplateServerToClientMessageFactory: public ServerToClientMessageFactory
{
    public:
        TemplateServerToClientMessageFactory()
        {
        }
        ServerToClientMessage* create(DataStream* _stream)
        {
            return new Message(_stream);
        }
};

Client::Client(const char* _serverIp, int _serverPort)
{
    //ctor
	/*int Error = WSAStartup (0x0202, &m_WSData);
	if (Error)
	{
		printf("Error:  You need WinSock 2.2!\n");
	}
	if (m_WSData.wVersion != 0x0202)
	{
		printf("Error:  Wrong WinSock version!\n");
		WSACleanup ();
	}*/
	sockaddr_in local;
	hostent* server;
	transmissionSocket = socket(AF_INET, SOCK_STREAM, 0);
	/*{
        int flag = 1;
        int ret = setsockopt( transmissionSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag) );
        if (ret == -1)
        {
            g_Log.error("Couldn't disable Nagle algorithm");
        }
	}*/


	server = gethostbyname(_serverIp);
	local.sin_family = AF_INET;
	local.sin_port = htons (_serverPort);
	//local.sin_addr.s_addr = inet_addr (_serverIp);

    bcopy((char *)server->h_addr,
         (char *)&local.sin_addr.s_addr,
         server->h_length);

	if (connect(transmissionSocket, reinterpret_cast<sockaddr*>(&local), sizeof(local)) < 0)
	{
        g_Log.error("Unable to connect to server");
		//WSACleanup ();
	}
    /// Linux
    int nonBlocking = 1;
    if ( fcntl( transmissionSocket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
    {
        g_Log.error("Failed to set non-blocking socket");
    }
    /// Windows
    /*
	int nonBlocking = 1;
	ioctlsocket(newClientListen, FIONBIO, &nonBlocking);*/

	printf("Connected to server\n");

	ClientInitialisationMessage message("Alasdair", {0,0}, 0);
	ClientToServerMessage* messagePtr = &message;
	send(messagePtr);

	addServerMessageFactory<ClientInitialisationMessage>();
	addServerMessageFactory<FrameUpdateMessage>();
}

Client::~Client()
{
    //dtor
    close(transmissionSocket);
}

template <typename Message>
void Client::addServerMessageFactory()
{
    unsigned short id = Message::staticServerToClientGetMessageId();
    if (serverMessageFactories.size() <= id)
        serverMessageFactories.resize(id+1);

    auto factory = new TemplateServerToClientMessageFactory<Message>;
	serverMessageFactories[id] = factory;
}
#include <SDL/SDL.h>
void Client::update(const FrameUpdate& _sendingUpdate)
{
    if (_sendingUpdate.getActionsSize() != 0)
    {
        FrameUpdateMessage message(_sendingUpdate);
        send(&message);
    }
	while (true)
	{
		char buffer[256];
		int size = recv(transmissionSocket, buffer, 256, 0);
		if (size > 0)
		{
            DataStream stream(buffer, size);
		    while (true)
		    {
                unsigned short messageId;
                try
                {
                    messageId = stream.decode<unsigned short>();
                }
                catch (int i)
                {
                    break;
                }
                unsigned short clientId = stream.decode<unsigned short>();
                if (messageId < serverMessageFactories.size())
                {
                    auto factory = serverMessageFactories[messageId];
                    ServerToClientMessage* message = factory->create(&stream);
                    assert(message->getServerToClientMessageId() == messageId);
                    message->clientProcess(this, clientId);
                //readerList->process(&stream);
                }
		    }
		}
		else break;
	}
}

void Client::send(ClientToServerMessage* _message)
{
    char buffer[256];
    DataStream stream(buffer, 0);
    stream.encode<unsigned short>(_message->getClientToServerMessageId());
    _message->encode(&stream);
    stream.transmit(transmissionSocket);
}












