// LearnOpenGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	//初始化glfw
	if(!glfwInit())
	{
		std::cout << "glfw init failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//创建opengl窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create glfwwindow!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//设置当前opengl环境为window
	glfwMakeContextCurrent(window);

	//glad加载opengl函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Failed to load glad!"<<std::endl;
	}

	//设置视口
	glViewport(0, 0, 800, 600);

	//设置窗口大小变化（framebuffer变化）回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		//处理按键输入
		process_input(window);

		//渲染

		//设置清空颜色
		glClearColor(1.0, 0.0, 0.0, 1.0);
		//清空颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT);

		//轮询事件检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
		glfwPollEvents();

		//交换缓冲区
		glfwSwapBuffers(window);
	}

	//销毁窗口资源，或者使用
	//glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

