// SuperBible5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "PathUtil.h"

#include "EasyLogging/EasyLogging.h"

using namespace pathutil;

int main()
{
	log_init(PathUtil::GetExeDir() + "configs/logconfig.cfg");


	log_uinit();
    return 0;
}

