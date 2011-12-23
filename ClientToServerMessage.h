#ifndef CLIENTTOSERVERMESSAGE_H
#define CLIENTTOSERVERMESSAGE_H

#include <Networking/NetworkMessage.h>
class Client;

class ClientToServerMessage : public NetworkMessage
{
    public:
        ClientToServerMessage();
        virtual ~ClientToServerMessage();
    private:
};

#endif // CLIENTTOSERVERMESSAGE_H
