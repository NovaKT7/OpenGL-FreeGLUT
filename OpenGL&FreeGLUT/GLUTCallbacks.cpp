#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		//initialize to null pointer
		HelloGL* helloGL = nullptr;
	}
	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			// Call member function of HelloGL
			 helloGL->Display(); 
		}
	}
	void Timer(int preferredRefresh)
	{
		if (helloGL != nullptr)
		{
			// Call member function of HelloGL
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			helloGL->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
		}

	}

	void Keyboard(unsigned char key, int x, int y)
	{
		
			// Call member function of HelloGL
			helloGL->Keyboard(key, x, y);
			helloGL ->MoveCamera(key);

	
	}

	void Mouse(int button, int state, int x, int y)
	{
		// Handle mouse input if needed
		helloGL->Mouse(button, state, x, y);

	}


	void PassiveMotion(int x, int y)
	{
		if (helloGL != nullptr)
			helloGL->PassiveMotion(x, y);
	}

}
