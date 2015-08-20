#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct vector2
{
	const double PI = 2.0 * acos(0.0);
	double x, y;

	explicit vector2(double x = 0, double y = 0) : x(x), y(y) {}

	bool operator == (const vector2& rhs) const 
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const 
	{
		return x != rhs.x? x < rhs.x: y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const 
	{
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const 
	{
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const 
	{
		return vector2(x * rhs, y * rhs);
	}

	// 벡터의 길이
	double norm() const {return hypot(x, y);}

	vector2 normalize() const
	{
		return vector2(x / norm(), y / norm());
	}

	// x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	double polar() const {return fmod(atan2(y, x) + 2 * PI, 2 * PI);}

	// 내적
	double dot(const vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	// 외적
	double cross(const vector2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	// rhs에 사영
	vector2 project(const vector2& rhs) const
	{
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};


int main()
{

	return 0;
}