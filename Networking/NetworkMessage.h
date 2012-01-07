#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H


class NetworkMessage
{
    public:
        NetworkMessage();
        virtual ~NetworkMessage();
    protected:
        unsigned short messageEnum;
    private:
};

#endif // NETWORKMESSAGE_H
