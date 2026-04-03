#include "Cube.h"


Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotationSpeed, float movementSpeed) : SceneObject(mesh,texture)      // ← call parent constructor
{
 
    _position.x = x;
    _position.y = y;
    _position.z = z;
    _rotation = 0.0f;
    _rotationSpeed = rand() % 2 + 1;
    _movementSpeed = movementSpeed;
	_texture = texture;



}

Vertex* Cube::indexedVertices = nullptr;

Color* Cube::indexedColors = nullptr;

GLushort* Cube::indices = nullptr; 


int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numindicies = 0;



void Cube::Update()
{
    _rotation += _rotationSpeed;               
    if (_rotation >= 360.0f)
        _rotation -= 360.0f;
  
 
}
void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->TexCoords != nullptr && _mesh->Indices != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 1.0f, 0.0f);
		glRotatef(_rotation, 0.0f, 1.0f, 1.0f);
		glRotatef(_rotation, 1.0f, 0.0f, 1.0f);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _mesh->IndexCount; i++)
		{
			GLushort idx = _mesh->Indices[i];
			glTexCoord2f(_mesh->TexCoords[idx].u, _mesh->TexCoords[idx].v);
			glColor3f(_mesh->Colors[idx].r, _mesh->Colors[idx].g, _mesh->Colors[idx].b);
			glVertex3f(_mesh->Vertices[idx].x, _mesh->Vertices[idx].y, _mesh->Vertices[idx].z);
		}
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
}
Cube::~Cube()
{

}


