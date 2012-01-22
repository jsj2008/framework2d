#ifndef TIMER_H
#define TIMER_H

#include <GameObject.h>

class Timer: public GameObject<Timer>
{
    public:
        void init();
        void pause();
        void unpause();
        unsigned int getTicks();
        unsigned int getFrame();
        void tick();
        static std::string name()
        {
            return "Timer";
        }
        static void registerActions(GameObjectType* _type);
        static Timer* global();
    protected:
    private:
        unsigned int startTime;
        unsigned int pauseTime;
        unsigned int frame;
        bool currentlyPaused;
};

#endif // TIMER_H
