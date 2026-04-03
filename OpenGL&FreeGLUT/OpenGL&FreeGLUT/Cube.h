#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Cube : public SceneObject
{
private:

	static int numVertices, numColors, numindicies;
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;
	GLfloat _rotation;
	Vector3 _position;
	float _rotationSpeed;
	float _movementSpeed;
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotationSpeed, float movementSpeed);
	~Cube();


	void Draw();
	void Update();
	
	
};

