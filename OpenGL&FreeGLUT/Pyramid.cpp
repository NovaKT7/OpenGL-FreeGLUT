#include "Pyramid.h"
#include <gl/GL.h>   

Pyramid::Pyramid(Mesh* mesh, Texture2D *texture, float x, float y, float z)
    : SceneObject(mesh, texture)
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
    SceneObject::Draw(); // Call the base class Draw to set material properties
    // If the mesh failed to load, this line saves your program from crashing
    if (!_mesh || !_mesh->Vertices || !_mesh->Indices)
    {
        return; 
    }

    glPushMatrix();
        glTranslatef(_position.x, _position.y, _position.z);
       
        if (_texture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _texture->GetID());
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
        else
		{
			glDisable(GL_TEXTURE_2D); 
        }
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < _mesh->IndexCount; i++)
        {
            GLushort idx = _mesh->Indices[i];
            //Draw UV
            if (_mesh->TexCoordCount > 0 && idx < _mesh->TexCoordCount)
				glTexCoord2f(_mesh->TexCoords[idx].u, _mesh->TexCoords[idx].v);

			//Draw Normal
            if (_mesh->NormalCount > 0 && idx < _mesh->NormalCount)
				glNormal3f(_mesh->Normals[idx].x, _mesh->Normals[idx].y, _mesh->Normals[idx].z);


            // Draw vertex
            if (idx < _mesh->VertexCount)
                glVertex3f(_mesh->Vertices[idx].x, _mesh->Vertices[idx].y, _mesh->Vertices[idx].z);
        }
        glEnd();
    glPopMatrix();
}