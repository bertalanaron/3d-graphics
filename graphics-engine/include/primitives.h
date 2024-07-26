﻿#pragma once
#ifdef GRAPHICS_PCH
#include "pch.h"
#else
#include <iostream>
#include <optional>
#endif // GRAPHICS_PCH

#define _VEC2_OPERATION(operation) vec2 operator##operation##(const vec2& v) const {\
	return vec2(x operation v.x, y operation v.y);\
}

namespace graphics {

struct vec2 {
	float x, y;

	vec2(float _x = 0, float _y = 0)
		: x(_x), y(_y)
	{ }

	_VEC2_OPERATION(+)

	_VEC2_OPERATION(-)

	_VEC2_OPERATION(*)

	_VEC2_OPERATION(/)

	vec2 operator*(float s) const {
		return vec2(x * s, y * s);
	}

	vec2 operator/(float s) const {
		return vec2(x / s, y / s);
	}
};

}

namespace graphics {

struct vec2i {
	int x, y;

	vec2i(int _x = 0, int _y = 0)
		: x(_x), y(_y)
	{ }

	bool operator==(const vec2i& v) const { return x == v.x && y == v.y; }

	vec2i operator-(const vec2i& v) const { return vec2i(x - v.x, y - v.y); }

	operator vec2() { return vec2(x, y); }
};

}
namespace graphics {

#define _VEC3_OPERATION(operation) vec3 operator##operation##(const vec3& v) const {\
	return vec3(x operation v.x, y operation v.y, z operation v.z);\
}

struct vec4;

struct vec3 {
	float x, y, z;

	vec3(float _x = 0, float _y = 0, float _z = 0)
		: x(_x), y(_y), z(_z)
	{ }

	vec3(const vec2& v)
		: x(v.x), y(v.y), z(0)
	{ }

	vec3(const vec2i& v)
		: x(v.x), y(v.y), z(0)
	{ }

	vec3(const vec4& v);

	_VEC3_OPERATION(+)

	_VEC3_OPERATION(-)

	_VEC3_OPERATION(*)
	
	_VEC3_OPERATION(/)

	vec3 operator*(float s) const {
		return vec3(x * s, y * s, z * s);
	}

	vec3 operator/(float s) const {
		return vec3(x / s, y / s, z / s);
	}

	vec3 operator-() const {
		return vec3(-x, -y, -z);
	}

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}
};

struct vec3i {
	int x, y, z;

	vec3i(int _x = 0, int _y = 0, int _z = 0)
		: x(_x), y(_y), z(_z)
	{ }

	vec3i(const vec2& v)
		: x(v.x), y(v.y), z(0)
	{ }

	vec3i(const vec2i& v)
		: x(v.x), y(v.y), z(0)
	{ }

	_VEC3_OPERATION(+)

	_VEC3_OPERATION(-)

	_VEC3_OPERATION(*)

	_VEC3_OPERATION(/ )

	vec3i operator*(float s) const {
		return vec3i(x * s, y * s, z * s);
	}

	vec3i operator/(float s) const {
		return vec3i(x / s, y / s, z / s);
	}

	vec3i operator-() const {
		return vec3i(-x, -y, -z);
	}

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}
};

}

inline graphics::vec3 normalize(const graphics::vec3& v) {
		auto res = v / v.length();
		return res;
}

inline graphics::vec3 cross(const graphics::vec3& v1, const graphics::vec3& v2) {
	return graphics::vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

inline float dot(const graphics::vec3& v1, const graphics::vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

namespace graphics {

#define _VEC4_OPERATION(operation) vec4 operator##operation##(const vec4& v) const {\
	return vec4(x operation v.x, y operation v.y, z operation v.z, w operation v.w);\
}

struct vec4 {
	float x, y, z, w;

	vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
		: x(_x), y(_y), z(_z), w(_w)
	{ }

	vec4(const vec3& v, float _w = 0)
		: x(v.x), y(v.y), z(v.z), w(_w)
	{ }

	_VEC4_OPERATION(+)

	_VEC4_OPERATION(-)

	_VEC4_OPERATION(*)

	_VEC4_OPERATION(/ )

	vec4 operator*(float s) const {
		return vec4(x * s, y * s, z * s, w * s);
	}

	vec4 operator/(float s) const {
		return vec4(x / s, y / s, z / s, w / s);
	}
};

inline vec3::vec3(const vec4& v) {
	x = v.x; y = v.y; z = v.z;
}

}

inline graphics::vec4 operator*(float s, const graphics::vec4& v) {
	return graphics::vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

namespace graphics {

struct mat4 {
	vec4 rows[4];

	mat4(const vec4& it = vec4(), const vec4& jt = vec4(), const vec4& kt = vec4(), const vec4& ot = vec4())
		: rows{ it, jt, kt, ot }
	{ }

	vec4& operator[](int i) {
		return rows[i];
	}

	const vec4& operator[](int i) const { 
		return rows[i]; 
	}

	static mat4 translation(const vec3& t) {
		return mat4(
			vec4(1, 0, 0, 0),
			vec4(0, 1, 0, 0),
			vec4(0, 0, 1, 0),
			vec4(t.x, t.y, t.z, 1));
	}

	static mat4 inverseTranslation(const vec3& t) {
		return mat4(
			vec4(1, 0, 0, -t.x),
			vec4(0, 1, 0, -t.y),
			vec4(0, 0, 1, -t.z),
			vec4(0, 0, 0, 1));
	}

	static mat4 scale(const vec3& s) {
		return mat4(
			vec4(s.x, 0, 0, 0),
			vec4(0, s.y, 0, 0),
			vec4(0, 0, s.z, 0),
			vec4(0, 0, 0, 1));
	}

	static mat4 inverseScale(const vec3& s) {
		return mat4(
			vec4(1.f / s.x, 0, 0, 0),
			vec4(0, 1.f / s.y, 0, 0),
			vec4(0, 0, 1.f / s.z, 0),
			vec4(0, 0, 0, 1));
	}

	static mat4 rotate(vec3 r) {
		return mat4(
			vec4(cosf(r.x)*cosf(r.y), cosf(r.x)*sinf(r.y)*sinf(r.z) - sinf(r.x)*cosf(r.z), cosf(r.x)*sinf(r.y)*cosf(r.z) + sinf(r.x)*sinf(r.z)),
			vec4(sinf(r.x)*cosf(r.y), sinf(r.x)*sinf(r.y)*sinf(r.z) + cosf(r.x)*cosf(r.z), sinf(r.x)*sinf(r.y)*cosf(r.z) - cosf(r.x)*sinf(r.z)),
			vec4(-sinf(r.y), cosf(r.y)*sinf(r.z), cosf(r.y)*cosf(r.z)),
		    vec4(0, 0, 0, 1)
		);
	}

	static mat4 inverseRotation(const vec3& r) {
		return mat4(
			vec4(cosf(r.x) * cosf(r.y), sinf(r.x) * cosf(r.y), -sinf(r.y), 0),
			vec4(cosf(r.x) * sinf(r.y) * sinf(r.z) - sinf(r.x) * cosf(r.z), sinf(r.x) * sinf(r.y) * sinf(r.z) + cosf(r.x) * cosf(r.z), cosf(r.y) * sinf(r.z), 0),
			vec4(cosf(r.x) * sinf(r.y) * cosf(r.z) + sinf(r.x) * sinf(r.z), sinf(r.x) * sinf(r.y) * cosf(r.z) - cosf(r.x) * sinf(r.z), cosf(r.y) * cosf(r.z), 0),
			vec4(0, 0, 0, 1)
		);
	}

	static mat4 rotate(vec3 axis, float angle) {
		float c = cosf(angle);
		float s = sinf(angle);
		float t = 1.0 - c;
		vec3 norm_axis = normalize(axis);
		float x = norm_axis.x, y = norm_axis.y, z = norm_axis.z;
		return mat4(
			vec4(t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0),
			vec4(t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0),
			vec4(t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0),
			vec4(0, 0, 0, 1)
		);
	}
};

}

inline graphics::vec4 operator*(const graphics::vec4& v, const graphics::mat4& m) {
	return v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3];
}

inline graphics::mat4 operator*(const graphics::mat4& ml, const graphics::mat4& mr) {
	graphics::mat4 res;
	for (int i = 0; i < 4; i++) res.rows[i] = ml.rows[i] * mr;
	return res;
}

namespace graphics {

struct Color {
	unsigned char r = 0, g = 0, b = 0, a = 255;

	Color(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0, unsigned char _a = 255)
		: r(_r), g(_g), b(_b), a(_a)
	{ }

	struct FColor;

	Color copy() {
		return *this;
	}

	Color& reduceAlpha(float factor) {
		a *= factor; return *this;
	}

	Color& setAlpha(unsigned char value) {
		a = value; return *this;
	}

	operator vec4() const {
		return vec4(r, g, b, a);
	}

	static Color white() { return Color(255, 255, 255, 255); }
	static Color black() { return Color(0, 0, 0, 255); }
	static Color red() { return Color(255, 0, 0, 255); }
	static Color green() { return Color(0, 255, 0, 255); }
	static Color blue() { return Color(0, 0, 255, 255); }
	static Color lightBlue() { return Color(0, 128, 255, 255); }
};

struct Color::FColor {
	float r = 0.f, g = 0.f, b = 0.f, a = 1.f;

	FColor(const Color& color)
		: r(color.r / 255.f)
		, g(color.g / 255.f)
		, b(color.b / 255.f)
		, a(color.a / 255.f)
	{ }
};

struct Ray {
	vec3 origin;
	vec3 direction;

	struct Hit {
		vec3 position;
		vec3 normal;
		float t;

		static Hit noHit() {
			return { vec3(), vec3(), std::numeric_limits<float>::infinity() };
		}
	};

	vec3 at(float t) const {
		return origin + direction * t;
	}

	static Ray castTowards(const vec3& origin, const vec3& target) {
		return Ray{ origin, normalize(target - origin) };
	}

	// if t is negative the intersection is behind the origin
	Hit intersectPlane(const vec3& point, const vec3& normal) const {
		float denom = dot(direction, normal);

		if (abs(denom) < 1e-6)
			return Hit::noHit();// ray is paralell

		float t = dot(point - origin, normal) / denom;
		vec3 intersection = origin + direction * t;
		
		return Hit{ intersection, normal, t };
	}

	Hit intersectTrig(const vec3& v1, const vec3& v2, const vec3& v3) const {
		vec3 trigNormal = cross(v2 - v1, v3 - v1);

		if (dot(trigNormal, direction) > 0)
			return Hit::noHit();

		float t = dot((v1 - origin), trigNormal) / dot(direction, trigNormal);
		vec3 p = origin + direction * t;

		if (dot(cross(v2 - v1, p - v1), trigNormal) <= 0) return Hit::noHit();
		if (dot(cross(v3 - v2, p - v2), trigNormal) <= 0) return Hit::noHit();
		if (dot(cross(v1 - v3, p - v3), trigNormal) <= 0) return Hit::noHit();

		return Hit{ p, normalize(trigNormal), t };
	}
};

}
