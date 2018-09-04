// LearnOpenGL.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��ʼ��glfw
	if(!glfwInit())
	{
		std::cout << "glfw init failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//����opengl����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create glfwwindow!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//���õ�ǰopengl����Ϊwindow
	glfwMakeContextCurrent(window);

	//glad����opengl����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Failed to load glad!"<<std::endl;
	}

	//�����ӿ�
	glViewport(0, 0, 800, 600);

	//���ô��ڴ�С�仯��framebuffer�仯���ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		//����������
		process_input(window);

		//��Ⱦ

		//���������ɫ
		glClearColor(1.0, 0.0, 0.0, 1.0);
		//�����ɫ������
		glClear(GL_COLOR_BUFFER_BIT);

		//��ѯ�¼������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
		glfwPollEvents();

		//����������
		glfwSwapBuffers(window);
	}

	//���ٴ�����Դ������ʹ��
	//glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

