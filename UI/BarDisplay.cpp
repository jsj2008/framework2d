#include "BarDisplay.h"

BarDisplay::BarDisplay(float _maxHeight)
{
    //ctor
    maxHeight = _maxHeight;
}

BarDisplay::~BarDisplay()
{
    //dtor
}

void BarDisplay::setHeight(float _height)
{
    height = _height;
}

/// FIXME, obviously lol
#include <iostream>
using namespace std;

void BarDisplay::render()
{
    cout << static_cast<unsigned int>(height * 128) << ' ';
}
