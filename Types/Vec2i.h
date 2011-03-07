#ifndef VEC2I_H
#define VEC2I_H
#include <math.h>
#include <Types/Vec2f.h>

struct Vec2i { //Simple vector class
	int x;
	int y;

	Vec2i( int pX = 0, int pY = 0 ) : x( pX ), y( pY ) { }

	~Vec2i() { }

	Vec2i operator*( int s ) { return Vec2i( x*s, y*s ); }
	Vec2i operator/( int s ) { return Vec2i( x/s, y/s ); }
	Vec2i operator+( int s ) { return Vec2i( x+s, y+s ); }
	Vec2i operator+(const Vec2i B ) const{ return Vec2i( x + B.x, y + B.y ); }
	Vec2i operator-(const Vec2i B ) const{ return Vec2i( x - B.x, y - B.y ); }
	Vec2i operator-() { return Vec2i( -x, -y ); }
	int operator*( Vec2i B ) { return x*B.x + y*B.y; }
	void operator=( Vec2i B ) { x = B.x; y = B.y; }
	void operator+=( Vec2i B ) { x += B.x; y += B.y; }
	void operator-=( Vec2i B ) { x -= B.x; y -= B.y; }
	void operator*=( int s ) { x *= s; y *= s; }
	void operator/=( int s ) { x /= s; y /= s; }
	bool operator==( Vec2i B ) { return x == B.x && y == B.y; }
	bool operator!=( Vec2i B ) { return x != B.x || y != B.y; }
	int Length() { return sqrt( float(x*x) + float(y*y) ); }
	const Vec2f ScreenToWorldSpace() const;
	void worldToScreenSpace(Vec2f world);

};

#endif // VEC2I_H
