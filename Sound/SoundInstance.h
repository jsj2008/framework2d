#ifndef SOUNDINSTANCE_H
#define SOUNDINSTANCE_H


class SoundInstance
{
    public:
        SoundInstance();
        virtual ~SoundInstance();
        virtual bool update(unsigned char* _streamSize, int _length)=0; /// Returns true if still active
    protected:
    private:
};

#endif // SOUNDINSTANCE_H
