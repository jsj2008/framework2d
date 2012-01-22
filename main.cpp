#include <Game.h>
#include <Filesystem/Filesystem.h>
int main(int argv, char* argc[])
{
    g_Game.init();
    g_Game.run();
    Filesystem::global()->shutdown();
    return 0;
}
