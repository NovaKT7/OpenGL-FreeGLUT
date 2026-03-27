#include "Cube.h"
#include <cstdlib>
#include <iostream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotationSpeed, float movementSpeed)
    : SceneObject(mesh,texture)      // ← call parent constructor
{
    // NO NEED for _mesh = mesh anymore
    _position.x = x;
    _position.y = y;
    _position.z = z;
    _rotation = 0.0f;
    _rotationSpeed = rotationSpeed;
    _movementSpeed = movementSpeed;
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
    if (_mesh == nullptr) return;

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation, 1.0f, 1.0f, 1.0f);

    if (_texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, _texture->GetID());
        glEnable(GL_TEXTURE_2D);

        // This is the key line that forces the texture to show
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < _mesh->IndexCount; ++i)
    {
        GLushort idx = _mesh->Indices[i];

        // Texture Coordinate
        if (idx < _mesh->TexCoordCount)
            glTexCoord2f(_mesh->TexCoords[idx].u, _mesh->TexCoords[idx].v);

        // Force white color so texture is not darkened
        glColor3f(1.0f, 1.0f, 1.0f);

        // Vertex Position
        if (idx < _mesh->VertexCount)
            glVertex3f(_mesh->Vertices[idx].x,
                _mesh->Vertices[idx].y,
                _mesh->Vertices[idx].z);
    }

    glEnd();

    if (_texture != nullptr)
    {
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
}
Cube::~Cube()
{

}


