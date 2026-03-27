#include "HelloGL.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "MeshLoader.h"




HelloGL::HelloGL(int argc, char* argv[])
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(std::time(0)));
    InitObjects();
    InitGL(argc, argv);
    GLUTCallbacks::Init(this);
    glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
   ;
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple OpenGL Program");

    // Register display callback
    glutDisplayFunc(GLUTCallbacks::Display);

    // Register timer callback
    glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

    glutKeyboardFunc(GLUTCallbacks::Keyboard);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 800, 800);
    gluPerspective(45.0f, 1.0f, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}



void HelloGL::InitObjects()
{
    Mesh* cubeMesh = MeshLoader::Load("cubeTexandCol.txt");
   

    Texture2D* texture = new Texture2D();
    bool success = texture->Load("Penguins.raw", 256, 256); 
    if (!success) {
        std::cout << "ERROR: Failed to load Penguins.raw!\n";
    }
    else {
        std::cout << "Texture loaded OK\n";
    }

    if (!cubeMesh) {
        std::cerr << "ERROR: cubeTexandCol.txt failed to load!\n";
    }

    Mesh* pyramidMesh = MeshLoader::Load("pyramid.txt");

    camera = new Camera();
    camera->eye = { 0.0f, 0.0f, 15.0f };
    camera->center = { 0.0f, 0.0f, 0.0f };
    camera->up = { 0.0f, 1.0f, 0.0f };

    // Create only 20 Cubes for testing
    for (int i = 0; i < 20; i++)
    {
        float x = ((rand() % 400) / 10.0f) - 20.0f;
        float y = ((rand() % 200) / 10.0f) - 10.0f;
        float z = -(20.0f + (rand() % 100) / 5.0f);

        objects[i] = new Cube(cubeMesh, texture, x, y, z, 2.0f, 0.0f);
    }

    // Create 20 Pyramids
    for (int i = 20; i < 40; i++)
    {
        float x = ((rand() % 400) / 10.0f) - 20.0f;
        float y = ((rand() % 200) / 10.0f) - 10.0f;
        float z = -(20.0f + (rand() % 100) / 5.0f);

        objects[i] = new Pyramid(pyramidMesh, x, y, z);
    }

    std::cout << "Test mode: 20 Cubes + 20 Pyramids created\n";
}



  
void HelloGL::Display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
        camera->center.x, camera->center.y, camera->center.z,
        camera->up.x, camera->up.y, camera->up.z);
    


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
            camera->center.y += moveSpeed; // Move the center point along with the camera

			break;
            case 'x':
                camera->eye.x -= moveSpeed;
                camera->center.y -= moveSpeed; // Move the center point along with the camera

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
   
    glutPostRedisplay();
   
}



HelloGL::~HelloGL(void)
{
    for (int i = 0; i < NUM_OBJ; i++) {
        delete objects[i];
        objects[i] = nullptr;
    }
    
}
