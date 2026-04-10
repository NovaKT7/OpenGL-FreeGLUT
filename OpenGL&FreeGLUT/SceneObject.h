#pragma once
#include "Structures.h"
#include "Texture2D.h"
class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
	Material* _material;
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();
	virtual void Update();
	virtual void Draw();
	virtual Vector3 GetPosition() const = 0;
	virtual void SetPosition(const Vector3& p) = 0;
	Mesh* GetMesh() const { return _mesh; }
};

