// stdafx.cpp : 只包括标准包含文件的源文件
// SuperBible5.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
#ifdef _DEBUG
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3D.lib")
#pragma comment(lib,"log4cplusUD.lib")
#else
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"log4cplusU.lib")
#endif