#pragma once
#include "vgl.h"
class OpenGLTestBase
{
public:
	OpenGLTestBase();
	virtual ~OpenGLTestBase();

	///////////////////////////////////////////////////////////////////////////////
	// Window has changed size, or has just been created. In either case, we need
	// to use the window dimensions to set the viewport and the projection matrix.
	virtual void ChangeSize(GLFWwindow* window, int width, int height) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// A normal ASCII key has been pressed.
	// In this case, advance the scene when the space bar is pressed
	virtual void KeyPressFunc(GLFWwindow *window) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// This function does any needed initialization on the rendering context. 
	// This is the first opportunity to do any OpenGL related tasks.
	virtual void SetupRC() = 0;

	// Called to draw scene
	virtual void RenderScene(void) = 0;
};

