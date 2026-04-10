
#include "SceneObject.h"
SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;

	_material = new Material();
	_material->Ambient = { 0.8f, 0.05f, 0.05f, 1.0f };
	_material->Diffuse = { 0.8f, 0.05f, 0.05f, 1.0f };
	_material->Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	_material->Shininess = 100.0f;

}
SceneObject::~SceneObject()
{
	delete _material;
	_material = nullptr;
}
void SceneObject::Update()
{

}

void SceneObject::Draw()
{
	
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _material->Shininess);
}