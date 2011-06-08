//#include <stdio.h>
#include "Vec2f.h"
using namespace std;
std::ostream& operator<< (ostream &out, Vec2f &vec)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << vec.x << " " << vec.y << " ";
}

istream& operator>> (istream &in, Vec2f &vec)
{
    in >> vec.x;
    in >> vec.y;
    return in;
}
