#include "Pyramid.h"
#include <gl/GL.h>   

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z)
    : SceneObject(mesh ,nullptr)
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
    // If the mesh failed to load, this line saves your program from crashing
    if (!_mesh || !_mesh->Vertices || !_mesh->Indices)
    {
        return; 
    }

    glPushMatrix();
        glTranslatef(_position.x, _position.y, _position.z);
        glDisable(GL_TEXTURE_2D); 

        glBegin(GL_TRIANGLES);
        for (int i = 0; i < _mesh->IndexCount; i++)
        {
            GLushort idx = _mesh->Indices[i];
            
            // Draw color if index is valid
            if (idx < _mesh->ColorCount)
                glColor3f(_mesh->Colors[idx].r, _mesh->Colors[idx].g, _mesh->Colors[idx].b);

            // Draw vertex
            if (idx < _mesh->VertexCount)
                glVertex3f(_mesh->Vertices[idx].x, _mesh->Vertices[idx].y, _mesh->Vertices[idx].z);
        }
        glEnd();

        glEnable(GL_TEXTURE_2D); 
    glPopMatrix();
}