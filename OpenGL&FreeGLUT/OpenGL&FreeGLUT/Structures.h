#pragma once
#include <Windows.h>
#include <gl/GL.h>

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

// FIXED Mesh struct
struct Mesh
{
    Vertex* Vertices;
    Color* Colors;
    GLushort* Indices;
    TexCoord* TexCoords;           // ? This line was causing problems

    int VertexCount;
    int ColorCount;
    int IndexCount;
    int TexCoordCount;

    Mesh()
        : Vertices(nullptr),
        Colors(nullptr),
        Indices(nullptr),
        TexCoords(nullptr),
        VertexCount(0),
        ColorCount(0),
        IndexCount(0),
        TexCoordCount(0)
    {}
};

struct TexturedMesh
{
    Mesh* Mesh;
    TexCoord* TexCoords;
    int TexCoordCount;

    TexturedMesh()
        : Mesh(nullptr), TexCoords(nullptr), TexCoordCount(0)
    {}
};