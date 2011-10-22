#ifndef SERVERTOCLIENTMESSAGEFACTORY_H
#define SERVERTOCLIENTMESSAGEFACTORY_H

class ServerToClientMessage;
class DataStream;

class ServerToClientMessageFactory
{
    public:
        ServerToClientMessageFactory();
        virtual ~ServerToClientMessageFactory();
        virtual ServerToClientMessage* create(DataStream* _stream)=0;
    protected:
    private:
};

#endif // SERVERTOCLIENTMESSAGEFACTORY_H
