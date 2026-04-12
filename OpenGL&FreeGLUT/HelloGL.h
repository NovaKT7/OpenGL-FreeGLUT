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

	//mouse function
	void Mouse(int button, int state, int x, int y);

	void UpdateRayFromMouse(int x, int y);

	void DrawRay();

	SceneObject* objects[NUM_OBJ];
	

	void InitObjects();
	void InitGL(int arc, char* argv[]);

	void InitLighting();
	void DrawString(const char* text, Vector3* position, Color* color);
	
	Vector3 _rayStart{};
	Vector3 _rayEnd{};
	Vector3 _rayDir{};

	bool _hasRay{};
	bool _pickRequested = false;

	int _mouseX = 0;
	int _mouseY = 0;

	
	
	SceneObject* selectedObject = nullptr;
	int selectedIndex = -1;


private:
	float rotation;
	static Vertex vertices[];
	static Color colors[];
	Vector4* _lightPosition;
	Lighting* _lightData;
};




