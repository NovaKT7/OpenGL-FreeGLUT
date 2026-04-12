#pragma once
#include "Structures.h"
#include "Texture2D.h"
class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
	Material* _material;

	bool _selected = false; 
	bool _touching = false;
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();
	virtual void Update();
	virtual void Draw();
	Mesh* GetMesh() const { return _mesh; } //needed for picking and moving objects
	virtual Vector3 GetPosition() const = 0;
	virtual void SetPosition(const Vector3& p) = 0;

	void SetSelected(bool s) { _selected = s; }
	void SetTouching(bool t) { _touching = t; }
	bool IsSelected() const { return _selected; }
	bool _IsTouching() const { return _touching; }

	
};

