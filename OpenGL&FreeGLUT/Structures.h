#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "Texture2D.h"
#include <gl/GL.h>

struct Vector3
{
    float x;
    float y;
    float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct Camera
{
    Vector3 eye;
    Vector3 center;
    Vector3 up;
};

struct Color
{
    GLfloat r, g, b;
};

struct Vertex
{
    GLfloat x, y, z;
};

struct TexCoord
{
    GLfloat u;
    GLfloat v;
};

struct Mesh
{
    Vertex* Vertices;
    Vector3* Normals;
    GLushort* Indices;
    TexCoord* TexCoords;

    int VertexCount, NormalCount, IndexCount, TexCoordCount;
};

struct Lighting
{
Vector4 Ambient;
Vector4 Diffuse;
Vector4 Specular;
};

struct Material
{
Vector4 Ambient;
Vector4 Diffuse;
Vector4 Specular;
GLfloat Shininess;
};

struct Ray
{
	Vector3 Origin;
	Vector3 Direction;
};

struct AABB
    {
	Vector3 Min;
	Vector3 Max;
};
