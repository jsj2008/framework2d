#ifndef CLIENTTOSERVERMESSAGEFACTORY_H
#define CLIENTTOSERVERMESSAGEFACTORY_H

class ClientToServerMessage;
class DataStream;

class ClientToServerMessageFactory
{
    public:
        ClientToServerMessageFactory();
        virtual ~ClientToServerMessageFactory();
        virtual ClientToServerMessage* create(DataStream* _stream)=0;
    protected:
    private:
};

#endif // CLIENTTOSERVERMESSAGEFACTORY_H
