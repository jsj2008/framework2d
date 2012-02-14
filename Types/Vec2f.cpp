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
/*float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
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
}*/

Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect);
Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
{
    return intersectionPosition(_aStart, _aEnd, _bStart, _bEnd, true, true);
}
float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect);
float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd)
{
    return intersectionValue(_aStart, _aEnd, _bStart, _bEnd, true, true);
}

//  public domain function by Darel Rex Finley, 2006



//  Determines the intersection point of the line segment defined by points A and B
//  with the line segment defined by points C and D.
//
//  Returns YES if the intersection point was found, and stores that point in X,Y.
//  Returns NO if there is no determinable intersection point, in which case X,Y will
//  be unmodified.

bool lineSegmentIntersection(
float Ax, float Ay,
float Bx, float By,
float Cx, float Cy,
float Dx, float Dy,
float *X, float *Y,
float *aIntercept, bool _aNeedsIntersect)
{

  float  distAB, theCos, theSin, newX, ABpos ;

  //  Fail if either line segment is zero-length.
  if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy) return false;

  //  Fail if the segments share an end-point.
  if (Ax==Cx && Ay==Cy || Bx==Cx && By==Cy
  ||  Ax==Dx && Ay==Dy || Bx==Dx && By==Dy) {
    return false; }

  //  (1) Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;

  //  Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);

  //  (2) Rotate the system so that point B is on the positive X axis.
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;


  //  Fail if segment C-D doesn't cross line A-B.
  if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.) return false;

  //  (3) Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);
  *aIntercept = ABpos;

  //  Fail if segment C-D crosses line A-B outside of segment A-B.
  if ((ABpos<0. || ABpos>distAB) && _aNeedsIntersect) return false;

  //  (4) Apply the discovered position to line A-B in the original coordinate system.
  *X=Ax+ABpos*theCos;
  *Y=Ay+ABpos*theSin;

  //  Success.
  return true;
}
float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect)
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
            assert(_adeltaX != 0.0f);
            return (_bStart.x - _aStart.x) / (_aEnd.x - _aStart.x);
        }
        if (_bdeltaY == 0.0f)
        {
            assert(_bdeltaX != 0.0f);
            float aIntersect1 = (_bStart.y - _aStart.y) / (_aEnd.y - _aStart.y);
            float aIntersect2 = (_bEnd.y - _aStart.y) / (_aEnd.y - _aStart.y);
            float bIntersect1 = (_aStart.x - _bStart.x) / (_bEnd.x - _bStart.x);
            float bIntersect2 = (_aEnd.x - _bStart.x) / (_bEnd.x - _bStart.x);
            return aIntersect1;
        }
        /*if (_bdeltaX == 0.0f)
        {
            assert(false);
        }*/
        float _am = _adeltaX / _adeltaY;
        float _bm = _bdeltaX / _bdeltaY;

        /// b = x - my
        float _ab = _aStart.x - (_am * _aStart.y);
        float _bb = _bStart.x - (_bm * _bStart.y);

        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) = (_bm*y) + _bb - _ab
        /// (_am*y) - (_bm*y) = _bb - _ab
        /// (_am - _bm)y = _bb - _ab
        /// y = (_bb - _ab) / (_am - _bm)
        float y = (_bb - _ab) / (_am - _bm);
        if (_am + _bm == 0.0f)
        {
            throw -1;
        }

        /// x = my + b
        float x = (_am * y) + _ab;

        float _aIntersection = (y - _aStart.y) / (_adeltaY);
        float _bIntersection = (y - _bStart.y) / (_bdeltaY);
        if ((_aIntersection < 0 || _aIntersection > 1) && _aNeedsIntersect)
        {
            throw -1;
        }
        if (_bNeedsIntersect && (_bIntersection < 0 || _bIntersection > 1))
        {
            throw -1; /// Doesn't lie on the line
        }
        return (y - _aStart.y) / (_adeltaY);
    }
    else
    {
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
        /// (_am - _bm)x = _bb - _ab
        /// x = (_bb - _ab) / (_am - _bm)
        float x = (_bb - _ab) / (_am - _bm);
        if (_am + _bm == 0.0f)
        {
            throw -1;
        }

        /// y = mx + b
        float y = (_am * x) + _ab;

        float _aIntersection = (x - _aStart.x) / (_adeltaX);
        float _bIntersection = (x - _bStart.x) / (_bdeltaX);
        if ((_aIntersection < 0 || _aIntersection > 1) && _aNeedsIntersect)
        {
            throw -1;
        }
        if (_bNeedsIntersect && (_bIntersection < 0 || _bIntersection > 1))
        {
            throw -1; /// Doesn't lie on the line
        }
        return (x - _aStart.x) / (_adeltaX);
    }
}
Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect)
{
    float intersect = intersectionValue(_aStart, _aEnd, _bStart, _bEnd, _aNeedsIntersect, _bNeedsIntersect);
    return ((_aEnd - _aStart) * intersect) + _aStart;
    /*
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
            assert(_adeltaX != 0.0f);
            return {_bStart.x, _aStart.y};
        }
        /*if (_bdeltaX == 0.0f)
        {
            assert(false);
        }* /
        float _am = _adeltaX / _adeltaY;
        float _bm = _bdeltaX / _bdeltaY;

        /// b = x - my
        float _ab = _aStart.x - (_am * _aStart.y);
        float _bb = _bStart.x - (_bm * _bStart.y);

        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) + _ab = (_bm*y) + _bb
        /// (_am*y) = (_bm*y) + _bb - _ab
        /// (_am*y) - (_bm*y) = _bb - _ab
        /// (_am - _bm)y = _bb - _ab
        /// y = (_bb - _ab) / (_am - _bm)
        float y = (_bb - _ab) / (_am - _bm);
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
            throw -1;
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
    /// y = mx + b
    /// m1x + b1 = m2x + b2
    /// (_am*x) + _ab = (_bm*x) + _bb
    /// (_am*x) = (_bm*x) + _bb - _ab
    /// (_am*x) - (_bm*x) = _bb - _ab
    /// (_am - _bm)x = _bb - _ab
    /// x = (_bb - _ab) / (_am - _bm)
    float x = (_bb - _ab) / (_am - _bm);
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
        throw -1;
    }
    if (!_bNeedsIntersect || _bIntersection < 0 || _bIntersection > 1)
    {
        throw -1; /// Doesn't lie on the line
    }
    return {x, y};*/
}

Vec2f positionFromScalarValue(Vec2f _start, Vec2f _end, float _scalar)
{
    return _start + ((_end - _start) * _scalar);
}


















