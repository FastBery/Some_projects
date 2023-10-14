#pragma once

struct vec3{
	float x, y, z;
	float &operator[](unsigned int const i)       {return *(&x + i);}
    float  operator[](unsigned int const i) const {return *(&x + i);}
};

struct vec2{
	float x, y;
};

struct color{
    unsigned char r, g, b;
};

struct triangle
{
        vec3 a, b, c;
        vec3 n1, n2, n3;
        vec2 d1, d2, d3;
};

struct intersection{
	triangle tr;
	vec3 norm;
	vec2 d1, d2, d3;
    vec3 albedo;
    vec3 position;
};

inline vec3 operator*(vec3 const &v, float const f)
{
    return
    {
        v.x * f,
        v.y * f,
        v.z * f,
    };
}

inline vec3 operator+(vec3 const &v1, vec3 const &v2)
{
    return
    {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
    };
}

struct Ray
{ 
    vec3 origin;
    vec3 direction;
    vec3 point(float const t) const {return origin + direction * t;}
};

struct RayTriangleIntersection
{
    float t, p, q;
};