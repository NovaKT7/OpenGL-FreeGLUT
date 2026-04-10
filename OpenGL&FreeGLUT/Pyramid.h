#pragma once
#include "SceneObject.h"
#include "Structures.h"   // for Vector3
#include "Texture2D.h"

class Pyramid : public SceneObject
{
private:
    Vector3 _position;    // only needs position (no rotation or speed)

public:
    Pyramid(Mesh* mesh, Texture2D *texture, float x, float y, float z);
    ~Pyramid();

    void Update() override;   // will be empty or very minimal
    void Draw()   override;
    Vector3 GetPosition() const override { return _position; }
    void SetPosition(const Vector3& p) override { _position = p; }
};