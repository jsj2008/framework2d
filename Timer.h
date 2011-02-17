#ifndef TIMER_H
#define TIMER_H


extern class Timer
{
    public:
        void init();
        void pause();
        void unPause();
        unsigned int getTicks();
    protected:
    private:
        unsigned int startTime;
        unsigned int pauseTime;
        bool currentlyPaused;
}g_Timer;

#endif // TIMER_H
