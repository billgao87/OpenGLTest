#pragma once

#include "vgl.h"
#include <iostream>

namespace hellotriangle
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void process_input(GLFWwindow *window);

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 vVertex;"
		"void main()"
		"{"
		"	gl_Position = vec4(vVertex.x, vVertex.y, vVertex.z, 1.0);"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;"
		"void main()"
		"{"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
		"}";

	int process_in_main()
	{
		//初始化glfw
		if (!glfwInit())
		{
			std::cout << "glfw init failed!" << std::endl;
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

															 //创建opengl窗口
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);

		//窗口全屏显示在主显示器上
		//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", glfwGetPrimaryMonitor(), nullptr);

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
			std::cout << "Failed to load glad!" << std::endl;
		}

		//设置视口
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		//设置窗口大小变化（framebuffer变化）回调函数
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


		// build and compile our shader program
		// ------------------------------------
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		int sucess;
		char infolog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infolog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
			return -1;
		}


		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(fragShader, 512, nullptr, infolog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
			return -1;
		}

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);

		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infolog);
			std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infolog << std::endl;
			return -1;
		}

		//link完毕删除着色器
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);


		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------

		GLfloat vertices[] =
		{
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		};


		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			// input
			// -----
			process_input(window);

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// glBindVertexArray(0); // no need to unbind it every time 

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
		return 0;
	}
	

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void process_input(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
