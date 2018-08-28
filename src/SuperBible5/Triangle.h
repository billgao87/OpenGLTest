#pragma once

#include "vgl.h"
#include "GLBatch.h"
#include "GLShaderManager.h"

namespace Triangle
{
	GLBatch triangleBatch;
	GLShaderManager shaderManager;

	///////////////////////////////////////////////////////////////////////////////
	// Window has changed size, or has just been created. In either case, we need
	// to use the window dimensions to set the viewport and the projection matrix.
	void ChangeSize(GLFWwindow* window, int w, int  h)
	{
		glViewport(0, 0, w, h);
	}

	///////////////////////////////////////////////////////////////////////////////
	// This function does any needed initialization on the rendering context. 
	// This is the first opportunity to do any OpenGL related tasks.
	void SetupRC()
	{
		// Blue background
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		shaderManager.InitializeStockShaders();

		// Load up a triangle
		GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f };

		triangleBatch.Begin(GL_TRIANGLES, 3);
		triangleBatch.CopyVertexData3f(vVerts);
		triangleBatch.End();
	}

	//////////////////////////////////////////////////////////////////////////////
	// Called to draw scene
	void RenderScene()
	{
		// Clear the window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
		triangleBatch.Draw();
	}

	///////////////////////////////////////////////////////////////////////////////
	// A normal ASCII key has been pressed.
	// In this case, advance the scene when the space bar is pressed
	void KeyPressFunc(GLFWwindow *window)
	{
		auto key = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (key == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void Finalized()
	{
	}
}
