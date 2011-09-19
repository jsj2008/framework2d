#ifndef BEATDISPLAY_H
#define BEATDISPLAY_H

#define FREQUENCIES 8
class BarDisplay;

class BeatDisplay
{
    public:
        BeatDisplay();
        virtual ~BeatDisplay();
        void updateStream(unsigned char* _stream, int _length); /// Might wanna abstract this input method so it can be passed in differently?
        void render();
    protected:
    private:
        unsigned char lastValue[FREQUENCIES];
        class Frequency
        {
            public:
                Frequency();
                ~Frequency();
                void init(int _positionInDisplay);
                void volumeThisStep(unsigned char _volume);
                static void static_update(Frequency* _frequencies, unsigned int _size = FREQUENCIES); /// Genius. This should be polymorphic and the non static one, not
                static void static_render(Frequency* _frequencies, unsigned int _size = FREQUENCIES);
            private:
                /// Data
                int positionInDisplay;
                /// State
                void update();
                void pumpVolume(unsigned char _volume);
                unsigned int height; /// Signed difference might cause type conversion with maths?
                float velocity; /// Also this is a float

                /// Rendering
                BarDisplay* barDisplay;
                void render();
        };

        Frequency frequencys[FREQUENCIES];
        static int frequencyStepSizes[FREQUENCIES];
};

#endif // BEATDISPLAY_H
