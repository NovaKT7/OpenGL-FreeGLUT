#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "Texture2D.h"

struct Vector3
{
    float x;
    float y;
    float z;
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
    Color* Colors;
    GLushort* Indices;
    TexCoord* TexCoords;

    int VertexCount, ColorCount, IndexCount, TexCoordCount;
};

