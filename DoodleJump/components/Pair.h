#pragma once
#include <iostream>

class Pair {
public:
	float x, y;
	Pair() { x = y = 0.0f; }
	int x_int() { return int(x); }
	int y_int() { return int(y); }
	Pair(int   _x, int   _y) { x = _x; y = _y; }
	Pair(float _x, float _y) { x = _x; y = _y; }

	Pair& operator+=(const Pair p) { x += p.x; y += p.y; return *this; }
	Pair& operator-=(const Pair p) { x -= p.x; y -= p.y; return *this; }
	Pair& operator*=(const Pair p) { x *= p.x; y *= p.y; return *this; }
	Pair& operator/=(const Pair p) { x /= p.x; y /= p.y; return *this; }
	friend Pair operator+(Pair p1, const Pair p2) { return p1 += p2; }
	friend Pair operator-(Pair p1, const Pair p2) { return p1 -= p2; }
	friend Pair operator*(Pair p1, const Pair p2) { return p1 *= p2; }
	friend Pair operator/(Pair p1, const Pair p2) { return p1 /= p2; }

	Pair& operator+=(const float k) { x += k; y += k; return *this; }
	Pair& operator-=(const float k) { x -= k; y -= k; return *this; }
	Pair& operator*=(const float k) { x *= k; y *= k; return *this; }
	Pair& operator/=(const float k) { x /= k; y /= k; return *this; }
	friend Pair operator+(const float k, Pair other) { return other += k; }
	friend Pair operator-(const float k, Pair other) { return other -= k; }
	friend Pair operator*(const float k, Pair other) { return other *= k; }
	friend Pair operator/(const float k, Pair other) { return other /= k; }

	friend std::ostream& operator<<(std::ostream& stream, const Pair& p) {
		return stream << '(' << p.x << ',' << p.y << ')';
	}
};

