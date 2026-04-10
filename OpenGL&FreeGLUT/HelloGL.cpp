#include "HelloGL.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "MeshLoader.h"




HelloGL::HelloGL(int argc, char* argv[])
{
    // 1. CLEAR THE ARRAY IMMEDIATELY
    for (int i = 0; i < NUM_OBJ; i++) {
        objects[i] = nullptr;
    }

    // Seed the random number generator
    srand(static_cast<unsigned int>(std::time(0)));
    InitGL(argc, argv);
    InitObjects();
	InitLighting();
    GLUTCallbacks::Init(this);
    glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
    GLUTCallbacks::Init(this);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple OpenGL Program");
    glutDisplayFunc(GLUTCallbacks::Display);
    glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
    glutKeyboardFunc(GLUTCallbacks::Keyboard);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 800, 800);
    gluPerspective(45, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_CULL_FACE);
   
    glCullFace(GL_BACK);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4{};
	_lightPosition->x = 0.0f;
	_lightPosition->y = 0.0f;
	_lightPosition->z = 1.0f;
	_lightPosition->w = 1.0f; // Positional light

	_lightData = new Lighting{};
	_lightData->Ambient.x = 0.2f;
	_lightData->Ambient.y = 0.2f;
	_lightData->Ambient.z = 0.2f;
	_lightData->Ambient.w = 1.0f;
	_lightData->Diffuse.x = 0.8f;
	_lightData->Diffuse.y = 0.8f;
	_lightData->Diffuse.z = 0.8f;
	_lightData->Diffuse.w = 1.0f;
	_lightData->Specular.x = 0.2f;
	_lightData->Specular.y = 0.2f;
	_lightData->Specular.z = 0.2f;
	_lightData->Specular.w = 1.0f;
}

void HelloGL::InitObjects()
{
    camera = new Camera();
    camera->eye = { 0.0f, 0.0f, 15.0f };
    camera->center = { 0.0f, 0.0f, 0.0f };
    camera->up = { 0.0f, 1.0f, 0.0f };

    Mesh* cubeMesh = MeshLoader::Load((char*)"cube2.txt");
    Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

    Texture2D* cubeTexture = new Texture2D();
    cubeTexture->Load((char*)"Diamonds.raw", 960, 960);
   
	Texture2D* pyramidTexture = new Texture2D();
	pyramidTexture->Load((char*)"Penguins.raw", 512, 512);
 
  


    // Create only 20 Cubes for testing
    for (int i = 0; i < 200; i++)
    {
        float x = ((rand() % 400) / 10.0f) - 20.0f;
        float y = ((rand() % 200) / 10.0f) - 10.0f;
        float z = -(20.0f + (rand() % 100) / 5.0f);

        objects[i] = new Cube(cubeMesh, cubeTexture, x, y, z, 2.0f, 0.0f);
    }

    /* Create 20 Pyramids*/
    for (int i = 0; i < 40; i++)
    {
        float x = ((rand() % 400) / 10.0f) - 20.0f;
        float y = ((rand() % 200) / 10.0f) - 10.0f;
        float z = -(20.0f + (rand() % 100) / 5.0f);

        objects[i] = new Pyramid(pyramidMesh, pyramidTexture, x, y, z);
    }

    std::cout << "Test mode: 20 Cubes + 20 Pyramids created\n";
}



  
void HelloGL::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
        camera->center.x, camera->center.y, camera->center.z,
        camera->up.x, camera->up.y, camera->up.z);

    glEnable(GL_TEXTURE_2D);     // Start with texture enabled

    for (int i = 0; i < NUM_OBJ; i++)
    {
        if (objects[i])
            objects[i]->Draw();
    }

    glutSwapBuffers();
}



void HelloGL::Keyboard(unsigned char key, int x, int y)
{
    if (key == 'z')
        rotation += 5.0f;
    if (key == 'x')
        rotation -= 5.0f;

    // Camera movement keys
    if (key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'q' || key == 'e')
    {
        MoveCamera(key);
        glutPostRedisplay();
    }
}

void HelloGL::MoveCamera(char key)
{
    float moveSpeed = 0.1f;
    switch (key)
    {
    case 'w':
        camera->eye.z -= moveSpeed;
        camera->center.z-= moveSpeed; // Move the center point along with the camera
        
        
        break;
    case 's':
        camera->eye.z += moveSpeed;
        camera->center.z += moveSpeed; // Move the center point along with the camera
        break;
    case 'a':
        camera->eye.x -= moveSpeed;
        camera->center.x -= moveSpeed; // Move the center point along with the camera
        break;
    case 'd':
        camera->eye.x += moveSpeed;
        camera->center.x += moveSpeed; // Move the center point along with the camera
        break;
    case 'q':
        camera->eye.y += moveSpeed;
        camera->center.y += moveSpeed; // Move the center point along with the camera
        break;
    case 'e':
        camera->eye.y -= moveSpeed;
        camera->center.y -= moveSpeed; // Move the center point along with the camera
        break;
        case 'z':
            camera->eye.x += moveSpeed;
            camera->eye.z += moveSpeed;
            camera->center.z -= moveSpeed;// Move the center point along with the camera
            camera->center.x -= moveSpeed; // Move the center point along with the camera

			break;
            case 'x':
                camera->eye.x -= moveSpeed;
                camera->eye.z -= moveSpeed;
                camera->center.z += moveSpeed;// Move the center point along with the camera
                camera->center.x += moveSpeed;
                break;
    default:
        break;
    }
}

void HelloGL::Update()
{
    for (int i = 0; i < NUM_OBJ; i++)
    {
        if (objects[i])
            objects[i]->Update();
     
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
    glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
    glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

    glutPostRedisplay();
   
	
  
}



HelloGL::~HelloGL(void)
{
    for (int i = 0; i < NUM_OBJ; i++) {
        delete objects[i];
        objects[i] = nullptr;
    }
    
}

