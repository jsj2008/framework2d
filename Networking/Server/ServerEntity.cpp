#include "ServerEntity.h"
#include <Networking/DataStream.h>
#include <Networking/Server/Server.h>
#include <Log/Log.h>
#include <sys/socket.h>

ServerEntity::ServerEntity(int _socket, unsigned short _entityKey)
{
    //ctor
    socket = _socket;
    entityKey = _entityKey;
    name = "Undefined ServerEntity";
    inited = false;
}

ServerEntity::~ServerEntity()
{
    //dtor
}

void ServerEntity::initialise(const std::string& _name, Server* _server)
{
    name = _name;
    _server->bringUpToSpeed(this);
}
bool ServerEntity::process(Server* _server)
{
	char buffer[256];
	int recieved = recv(socket, buffer, 256, 0);
	if (recieved > 0)
	{
		DataStream stream(buffer, recieved);
		_server->process(this, &stream);
	}
	if (recieved == 0)
	{
		return false;
	}
    return true;
}

void ServerEntity::send(DataStream* _stream)
{
    _stream->transmit(socket);
}
