#include "Pyramid.h"
#include <gl/GL.h>   

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z)
    : SceneObject(mesh , nullptr)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}

Pyramid::~Pyramid()
{
    // nothing special — mesh is shared
}

void Pyramid::Update()
{
    // Static object ? do NOTHING here (no rotation, no movement)
    // You can leave it completely empty
}

void Pyramid::Draw()
{
    if (_mesh == nullptr) return;
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    // Only translate to its fixed position
    glTranslatef(_position.x, _position.y, _position.z);

    // No rotation ? that's the main difference from Cube

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < _mesh->IndexCount; ++i)
    {
        GLushort idx = _mesh->Indices[i];

        if (idx < static_cast<GLushort>(_mesh->ColorCount))
        {
            glColor3f(_mesh->Colors[idx].r, _mesh->Colors[idx].g, _mesh->Colors[idx].b);
        }

        if (idx < static_cast<GLushort>(_mesh->VertexCount))
        {
            glVertex3f(_mesh->Vertices[idx].x,
                _mesh->Vertices[idx].y,
                _mesh->Vertices[idx].z);
        }
    }
    glEnd();

    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}