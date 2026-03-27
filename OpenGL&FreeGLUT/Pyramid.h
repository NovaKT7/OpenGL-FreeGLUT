#pragma once
#include "SceneObject.h"
#include "Structures.h"   // for Vector3

class Pyramid : public SceneObject
{
private:
    Vector3 _position;    // only needs position (no rotation or speed)

public:
    Pyramid(Mesh* mesh, float x, float y, float z);
    ~Pyramid();

    void Update() override;   // will be empty or very minimal
    void Draw()   override;
};