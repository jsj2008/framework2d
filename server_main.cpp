#include <Networking/Server/Server.h>
#include <Timer.h>
int main(int argv, char* argc[])
{
    Timer::global()->init();
    Timer::global()->pause();

    Server server(8001);
    unsigned int startTime = Timer::global()->getTicks();
    unsigned int stepsTaken = 0;
    while (true)
    {
        unsigned int currentTime = Timer::global()->getTicks();
        unsigned int totalTimePassed = currentTime - startTime;
        if (currentTime < startTime) /// FIXME
            totalTimePassed = 0;
        unsigned int stepsToTake = totalTimePassed*60.0f/1000.0f;
        if (stepsToTake > stepsTaken) /// FIXME needs to loop
        {
            server.update();
            stepsTaken++;
        }
    }
    return 0;
}
