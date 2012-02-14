#include "Vec2f.h"
#include <cassert>
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


float intersectionXValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
{
    /// y = mx + b
    float _adeltaX = _aEnd.x - _aStart.x;
    float _adeltaY = _aEnd.y - _aStart.y;
    float _bm = _adeltaY / _adeltaX;
    /// b = y - mx
    float _ab = _aStart.y - (_bm * _aStart.x);


    /// y = mx + b
    float _bdeltaX = _bEnd.x - _bStart.x;
    float _bdeltaY = _bEnd.y - _bStart.y;
    float _am = _bdeltaY / _bdeltaX;
    /// b = y - mx
    float _bb = _bStart.y - (_am * _bStart.x);

    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) = (_bm*x) + _bb - _ab
    /// (_am*x) - (_bm*x) = _bb - _ab
    /// (_am + _bm)x = _bb - _ab
    /// x = (_bb - _ab) / (_am + _bm)
    float x = (_bb - _ab) / (_am + _bm);

    return x;
}
float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
{
    /// y = mx + b
    float _adeltaX = _aEnd.x - _aStart.x;
    float _adeltaY = _aEnd.y - _aStart.y;
    float _am = _adeltaY / _adeltaX;
    if (_adeltaX == 0.0f)
    {
        assert(false);
    }
    /// b = y - mx
    float _ab = _aStart.y - (_am * _aStart.x);


    /// y = mx + b
    float _bdeltaX = _bEnd.x - _bStart.x;
    float _bdeltaY = _bEnd.y - _bStart.y;
    float _bm = _bdeltaY / _bdeltaX;
    if (_bdeltaX == 0.0f)
    {
        assert(false);
    }
    /// b = y - mx
    float _bb = _bStart.y - (_bm * _bStart.x);

    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) = (_bm*x) + _bb - _ab
    /// (_am*x) - (_bm*x) = _bb - _ab
    /// (_am + _bm)x = _bb - _ab
    /// x = (_bb - _ab) / (_am + _bm)
    float x = (_bb - _ab) / (_am + _bm);

    return (x - _aStart.x) / (_adeltaX);
}

Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect);
Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
{
    return intersectionPosition(_aStart, _aEnd, _bStart, _bEnd, true, true);
}
Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect)
{
    float _adeltaX = _aEnd.x - _aStart.x;
    float _bdeltaX = _bEnd.x - _bStart.x;
    if (_adeltaX == 0.0f || _bdeltaX == 0.0f)
    {
        /// m = dX / dY
        float _adeltaX = _aEnd.x - _aStart.x;
        float _adeltaY = _aEnd.y - _aStart.y;
        float _bdeltaX = _bEnd.x - _bStart.x;
        float _bdeltaY = _bEnd.y - _bStart.y;
if (_adeltaY == 0.0f)
{
    assert(false);
}
if (_bdeltaX == 0.0f)
{
    assert(false);
}
        float _am = _adeltaX / _adeltaY;
        float _bm = _bdeltaY / _bdeltaX;

        /// b = x - my
        float _ab = _aStart.x - (_am * _aStart.y);
        float _bb = _bStart.x - (_bm * _bStart.y);

        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) = (_bm*y) + _bb - _ab
        /// (_am*y) - (_bm*y) = _bb - _ab
        /// (_am + _bm)y = _bb - _ab
        /// y = (_bb - _ab) / (_am + _bm)
        float y = (_bb - _ab) / (_am + _bm);
        if (_am + _bm == 0.0f)
        {
            throw -1;
        }

        /// x = my + b
        float x = (_am * y) + _ab;

        float _aIntersection = (y - _aStart.y) / (_adeltaY);
        float _bIntersection = (y - _bStart.y) / (_bdeltaY);
        if (_aIntersection < 0 || _aIntersection > 1 || !_aNeedsIntersect)
        {

        }
        if (!_bNeedsIntersect || _bIntersection < 0 || _bIntersection > 1)
        {
            throw -1; /// Doesn't lie on the line
        }
        return {x, y};
    }
    /// y = mx + b
    float _adeltaY = _aEnd.y - _aStart.y;
    float _am = _adeltaY / _adeltaX;
    if (_adeltaX == 0.0f)
    {
        assert(false);
    }
    /// b = y - mx
    float _ab = _aStart.y - (_am * _aStart.x);


    /// y = mx + b
    float _bdeltaY = _bEnd.y - _bStart.y;
    float _bm = _bdeltaY / _bdeltaX;
    if (_bdeltaX == 0.0f)
    {
        assert(false);
    }
    /// b = y - mx
    float _bb = _bStart.y - (_bm * _bStart.x);

    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) = (_bm*x) + _bb - _ab
    /// (_am*x) - (_bm*x) = _bb - _ab
    /// (_am + _bm)x = _bb - _ab
    /// x = (_bb - _ab) / (_am + _bm)
    float x = (_bb - _ab) / (_am + _bm);
    if (_am + _bm == 0.0f)
    {
        throw -1;
    }

    /// y = mx + b
    float y = (_am * x) + _ab;

    float _aIntersection = (x - _aStart.x) / (_adeltaX);
    float _bIntersection = (x - _bStart.x) / (_bdeltaX);
    if (_aIntersection < 0 || _aIntersection > 1 || !_aNeedsIntersect)
    {

    }
    if (!_bNeedsIntersect || _bIntersection < 0 || _bIntersection > 1)
    {
        throw -1; /// Doesn't lie on the line
    }
    return {x, y};
}

Vec2f positionFromScalarValue(Vec2f _start, Vec2f _end, float _scalar)
{
    return _start + ((_end - _start) * _scalar);
}


















