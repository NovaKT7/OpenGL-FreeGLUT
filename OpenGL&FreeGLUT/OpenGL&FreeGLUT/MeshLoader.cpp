#include "MeshLoader.h"
#include <fstream>
#include <iostream>
#include <string> // Added for skipping labels

Mesh* MeshLoader::Load(const char* path)
{
    std::ifstream inFile(path);
    if (!inFile.good())
    {
        std::cerr << "Failed to load mesh: " << path << std::endl;
        return nullptr;
    }

    Mesh* mesh = new Mesh();

    // 1. Vertices
    inFile >> mesh->VertexCount;
    mesh->Vertices = new Vertex[mesh->VertexCount];
    for (int i = 0; i < mesh->VertexCount; i++) {
        inFile >> mesh->Vertices[i].x >> mesh->Vertices[i].y >> mesh->Vertices[i].z;
    }

    // 2. Texture Coordinates
    inFile >> mesh->TexCoordCount;
    mesh->TexCoords = new TexCoord[mesh->TexCoordCount];
    for (int i = 0; i < mesh->TexCoordCount; i++) {
        inFile >> mesh->TexCoords[i].u >> mesh->TexCoords[i].v;
    }

    // 3. Colors
    inFile >> mesh->ColorCount;
    mesh->Colors = new Color[mesh->ColorCount];
    for (int i = 0; i < mesh->ColorCount; i++) {
        inFile >> mesh->Colors[i].r >> mesh->Colors[i].g >> mesh->Colors[i].b;
    }

    // 4. Indices
    inFile >> mesh->IndexCount;
    mesh->Indices = new GLushort[mesh->IndexCount];
    for (int i = 0; i < mesh->IndexCount; i++) {
        unsigned int temp;
        inFile >> temp;
        mesh->Indices[i] = static_cast<GLushort>(temp);   // NO -1
    }

    inFile.close();

    std::cout << "Loaded " << path
        << " ? V:" << mesh->VertexCount
        << " T:" << mesh->TexCoordCount
        << " C:" << mesh->ColorCount
        << " I:" << mesh->IndexCount << std::endl;

    return mesh;
}