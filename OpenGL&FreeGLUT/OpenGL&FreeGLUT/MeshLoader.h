#pragma once
#include "Structures.h"
namespace MeshLoader
{
    
    Mesh* Load(const char* path);
    TexturedMesh* LoadTextured(const char* path);

}