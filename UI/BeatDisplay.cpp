#include "BeatDisplay.h"
#include <UI/BarDisplay.h>
#include <cmath>

int BeatDisplay::frequencyStepSizes[FREQUENCIES];
BeatDisplay::BeatDisplay()
{
    //ctor
    for (unsigned int i = 0; i < FREQUENCIES; i++)
    {
        frequencys[i].init(i);
        frequencyStepSizes[i] = pow(2, i);
    }
}
BeatDisplay::Frequency::Frequency()
{
    barDisplay = new BarDisplay(128.0f);
    height = velocity = 0;
}

BeatDisplay::~BeatDisplay()
{
    //dtor
}
BeatDisplay::Frequency::~Frequency()
{
}

void BeatDisplay::Frequency::init(int _positionInDisplay)
{
    positionInDisplay = _positionInDisplay;
}

void BeatDisplay::updateStream(unsigned char* _stream, int _length)
{
    for (int i = 0; i < _length; i++)
    {
        for (int frequencyStep = 0; frequencyStep < FREQUENCIES; frequencyStep++) /// Need to take more samples and average them together to make this less shit
        {
            int frequency = frequencyStepSizes[frequencyStep];
            if (i == frequency)
            {
                int volumeAtThisFrequency = lastValue[frequencyStep] - _stream[i];
                if (volumeAtThisFrequency < 0)
                { /// This sign might be important - ups and downs
                    volumeAtThisFrequency = -volumeAtThisFrequency;
                }
                frequencys[frequencyStep].volumeThisStep(volumeAtThisFrequency); /// Might make this polymorphic
                lastValue[frequencyStep] = _stream[i];
            }
            else break;
        }
    }
    Frequency::static_update(frequencys);
}

void BeatDisplay::Frequency::volumeThisStep(unsigned char _volume)
{
    pumpVolume(_volume);
}

void BeatDisplay::Frequency::pumpVolume(unsigned char _volume)
{
    velocity += _volume;
    velocity *= 0.5f;
    velocity -= 64.0f;
    height += velocity;

    if (height <= 0)
    {
        velocity = 0;
        height = 0;
    }
}

void BeatDisplay::render()
{
    Frequency::static_render(frequencys);
}
/// FIXME, obviously lol
#include <iostream>
using namespace std;
/// Needs to build a data structure


void BeatDisplay::Frequency::static_update(Frequency* _frequencies, unsigned int _size)
{
    for (unsigned int i = 0; i < _size; i++)
    {
        _frequencies[i].update();
    }
}

void BeatDisplay::Frequency::update()
{
    float scaledHeight = static_cast<float>(height)/128.0f;
    barDisplay->setHeight(scaledHeight);
}

void BeatDisplay::Frequency::static_render(Frequency* _frequencies, unsigned int _size)
{
    for (unsigned int i = 0; i < _size; i++)
    {
        _frequencies[i].render();
    }
    cout << endl;
}

void BeatDisplay::Frequency::render()
{
    barDisplay->render();
}

























