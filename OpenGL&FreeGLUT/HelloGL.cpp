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

static bool RayIntersectsAABB(const Vector3& ro, const Vector3& rd, const AABB& box, float& tHit)
{
    float tmin = -1e30f;
    float tmax = 1e30f;

    auto slab = [&](float roC, float rdC, float minC, float maxC) -> bool
        {
            if (fabs(rdC) < 1e-8f)
                return (roC >= minC && roC <= maxC);

            float invD = 1.0f / rdC;
            float t1 = (minC - roC) * invD;
            float t2 = (maxC - roC) * invD;
            if (t1 > t2) std::swap(t1, t2);

            if (t1 > tmin) tmin = t1;
            if (t2 < tmax) tmax = t2;

            return (tmin <= tmax);
        };

    if (!slab(ro.x, rd.x, box.min.x, box.max.x)) return false;
    if (!slab(ro.y, rd.y, box.min.y, box.max.y)) return false;
    if (!slab(ro.z, rd.z, box.min.z, box.max.z)) return false;

    if (tmax < 0.0f) return false;

    tHit = (tmin >= 0.0f) ? tmin : tmax;
    return true;
}


struct AABB { Vector3 min; Vector3 max; };

static AABB ComputeMeshLocalAABB(Mesh* mesh)
{
    AABB b;
    b.min = { 1e30f,  1e30f,  1e30f };
    b.max = { -1e30f, -1e30f, -1e30f };

    for (int i = 0; i < mesh->VertexCount; i++)
    {
        float x = mesh->Vertices[i].x;
        float y = mesh->Vertices[i].y;
        float z = mesh->Vertices[i].z;

        if (x < b.min.x) b.min.x = x;
        if (y < b.min.y) b.min.y = y;
        if (z < b.min.z) b.min.z = z;

        if (x > b.max.x) b.max.x = x;
        if (y > b.max.y) b.max.y = y;
        if (z > b.max.z) b.max.z = z;
    }
    return b;
}

static AABB ToWorldAABB(const AABB& local, const Vector3& pos)
{
    AABB w;
    w.min = { local.min.x + pos.x, local.min.y + pos.y, local.min.z + pos.z };
    w.max = { local.max.x + pos.x, local.max.y + pos.y, local.max.z + pos.z };
    return w;
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
    glutMouseFunc(GLUTCallbacks::Mouse);

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
    for (int i = 0; i < 160; i++)
    {
        float x = ((rand() % 400) / 10.0f) - 20.0f;
        float y = ((rand() % 200) / 10.0f) - 10.0f;
        float z = -(20.0f + (rand() % 100) / 5.0f);

        objects[i] = new Cube(cubeMesh, cubeTexture, x, y, z, 2.0f, 0.0f);
    }

    /* Create 20 Pyramids*/
    for (int i = 160; i < 200; i++)
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

    if (_hasRay)
        UpdateRayFromMouse(_mouseX, _mouseY);

    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < NUM_OBJ; i++)
        if (objects[i]) objects[i]->Draw();

    // Optional: debug ray
    // DrawRay();

    // Text (your existing code)
    Vector3 v = { -1.4f, 2.7f, -1.0f };
    Color c = { 0.0f, 1.0f, 0.0f };
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    DrawString("HelloGL", &v, &c);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}



void HelloGL::Keyboard(unsigned char key, int x, int y)
{
    // If an object is selected, move it with IJKL
    if (selectedObject)
    {
        Vector3 p = selectedObject->GetPosition();
        float s = 0.3f;

        if (key == 'i') p.y += s;
        if (key == 'k') p.y -= s;
        if (key == 'j') p.x -= s;
        if (key == 'l') p.x += s;
        if (key == 'u') p.z += s;
        if (key == 'o') p.z -= s;

        selectedObject->SetPosition(p);
        glutPostRedisplay();
        return;
    }

    // Otherwise camera movement (your original logic)
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


void HelloGL::Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        _mouseX = x;
        _mouseY = y;
        _hasRay = true;
        _pickRequested = true;
        glutPostRedisplay();
    }
}

void HelloGL::UpdateRayFromMouse(int x, int y)
{
    GLdouble modelview[16], projection[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble winX = (GLdouble)x;
    GLdouble winY = (GLdouble)(viewport[3] - y);

    GLdouble ox, oy, oz;

    gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &ox, &oy, &oz);
    _rayStart = { (float)ox, (float)oy, (float)oz };

    gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &ox, &oy, &oz);
    _rayEnd = { (float)ox, (float)oy, (float)oz };

    _rayDir = { _rayEnd.x - _rayStart.x, _rayEnd.y - _rayStart.y, _rayEnd.z - _rayStart.z };
    float len = sqrtf(_rayDir.x * _rayDir.x + _rayDir.y * _rayDir.y + _rayDir.z * _rayDir.z);
    if (len > 1e-6f) { _rayDir.x /= len; _rayDir.y /= len; _rayDir.z /= len; }
}

void HelloGL::DrawRay()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glLineWidth(2.0f);
    glColor3f(1, 1, 0);

    glBegin(GL_LINES);
    glVertex3f(_rayStart.x, _rayStart.y, _rayStart.z);
    glVertex3f(_rayEnd.x, _rayEnd.y, _rayEnd.z);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}



void HelloGL::Update()
{
    // 1) Always update all objects (animation, rotation, etc.)
    for (int i = 0; i < NUM_OBJ; i++)
        if (objects[i]) objects[i]->Update();

    // 2) Picking only when click requested
    if (_pickRequested && _hasRay)
    {
        selectedObject = nullptr;
        selectedIndex = -1;
        float bestT = 1e30f;

        for (int i = 0; i < NUM_OBJ; i++)
        {
            if (!objects[i]) continue;

            Mesh* mesh = objects[i]->GetMesh();
            if (!mesh || !mesh->Vertices) continue; // mesh has Vertices/VertexCount 
            // Compute mesh local bounds (simple version: compute every time)
            // Later you can cache this per mesh pointer
            AABB local = ComputeMeshLocalAABB(mesh);

            Vector3 pos = objects[i]->GetPosition();
            AABB world = ToWorldAABB(local, pos);

            float tHit;
            if (RayIntersectsAABB(_rayStart, _rayDir, world, tHit))
            {
                if (tHit < bestT)
                {
                    bestT = tHit;
                    selectedObject = objects[i];
                    selectedIndex = i;
                }
            }
        }

        if (selectedObject)
            std::cout << "Object " << selectedIndex << " selected!\n";

        _pickRequested = false;
    }

    // 3) Light updates (your current code already does this)
    glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
    glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
    glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

    glutPostRedisplay();


}



void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
    glPushMatrix();
    glColor3f(color->r, color->g, color->b);
    glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
    glPopMatrix();
}



HelloGL::~HelloGL(void)
{
    for (int i = 0; i < NUM_OBJ; i++) {
        delete objects[i];
        objects[i] = nullptr;
    }
    
}

