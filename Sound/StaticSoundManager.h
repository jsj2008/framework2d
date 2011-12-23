#ifndef STATICSOUNDMANAGER_H
#define STATICSOUNDMANAGER_H

class SoundManager;

class StaticSoundManager
{
    public:
        static SoundManager* getSoundManager(){return soundManager;}
        static void init();
        static void quit();
    protected:
    private:
        StaticSoundManager();
        ~StaticSoundManager();
        static SoundManager* soundManager;
};

#endif // STATICSOUNDMANAGER_H
