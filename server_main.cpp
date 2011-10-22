#include <Networking/Server/Server.h>
int main(int argv, char* argc[])
{
    Server server(8001);
    while (true)
        server.update();
    return 0;
}
