#include "ClientInitialisationMessage.h"
#include <Networking/DataStream.h>
#include <Networking/Server/ServerEntity.h>
#include <Log/Log.h>

ClientInitialisationMessage::ClientInitialisationMessage(DataStream* _stream)
{
    //ctor
    _stream->decodeString<std::string, char>(&name);
    position = _stream->decode<Vec2f>();
    entityKey = _stream->decode<unsigned short>();
}
ClientInitialisationMessage::ClientInitialisationMessage(const std::string& _name, const Vec2f& _position, unsigned short _entityKey)
{
    //ctor
    name = _name;
    position = _position;
    entityKey = _entityKey;
}

ClientInitialisationMessage::~ClientInitialisationMessage()
{
    //dtor
}

void ClientInitialisationMessage::serverProcess(Server* _server, ServerEntity* _client)
{
    _client->initialise(name, _server);
    entityKey = _client->getEntityKey();
}

void ClientInitialisationMessage::encode(DataStream* _stream)
{
    _stream->encodeString<std::string, char>(&name);
    _stream->encode<Vec2f>(position);
    _stream->encode<unsigned short>(entityKey);
}

void ClientInitialisationMessage::virtualClientProcess(Client* _client, unsigned short _entityKey)
{
    g_Log.message("Client connected: " + name);
}
