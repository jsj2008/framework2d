#include "Vec2f.h"
using namespace std;
std::ostream& operator<< (ostream &out, Vec2f &vec)
{
    out << vec.x << " " << vec.y << " ";
    return out;
}

istream& operator>> (istream &in, Vec2f &vec)
{
    in >> vec.x;
    in >> vec.y;
    return in;
}
