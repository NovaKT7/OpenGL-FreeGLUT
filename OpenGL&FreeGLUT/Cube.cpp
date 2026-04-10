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
	SceneObject::Draw(); // Call the base class Draw to set material properties
    if (!_mesh || !_mesh->Vertices || !_mesh->Indices || _mesh->IndexCount <= 0) return;

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation, 1.0f, 1.0f, 1.0f);
	//texture binding
	bool hasTexture = (_texture != nullptr);
    if (hasTexture)
    {
        glBindTexture(GL_TEXTURE_2D, _texture->GetID());
        glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Better lighting with textures
    }
    else
    {
		glDisable(GL_TEXTURE_2D); // Ensure texturing is disabled if no texture is present
    }

    // Enable the arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
   
    if (_mesh->TexCoordCount > 0)
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Set the pointers
    glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
    glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
    if (_mesh->TexCoordCount > 0)
        glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

    // Draw using indices
    glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);

    // Disable the arrays
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    if (_mesh->TexCoordCount > 0)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    if (_texture != nullptr)
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
Cube::~Cube()
{

}


