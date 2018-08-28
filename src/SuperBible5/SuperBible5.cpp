// SuperBible5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PathUtil.h"
#include "EasyLogging/EasyLogging.h"
#include "vgl.h"
#include "Block.h"
#include "Triangle.h"

using namespace pathutil;

//using namespace Block;
using namespace Triangle;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	log_init(PathUtil::GetExeDir() + "configs/logconfig.cfg");

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, ChangeSize);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return -1;
	}

	SetupRC();
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		KeyPressFunc(window);

		RenderScene();

		// Perform the buffer swap to display back buffer
		glfwSwapBuffers(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwPollEvents();
	}

	Finalized();
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	log_uinit();
    return 0;
}













