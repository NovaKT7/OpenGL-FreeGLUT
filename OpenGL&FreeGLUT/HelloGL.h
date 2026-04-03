#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "OBJLoader.h"
#include "Pyramid.h"
#define REFRESHRATE 16 //approx 60 FPS
#define NUM_OBJ 200 // number of cubes



class HelloGL
{
	Camera* camera;

	public:
		
	HelloGL(int argc, char* argv[]);
	
	void Update();
	
	//detructor
	~HelloGL(void);

	//display function
	void Display();

	//keyboard function
	void Keyboard(unsigned char key, int x, int y);

	void MoveCamera(char key);

	SceneObject* objects[NUM_OBJ];
	

	void InitObjects();
	void InitGL(int arc, char* argv[]);
	

private:
	float rotation;
	static Vertex vertices[];
	static Color colors[];
};




