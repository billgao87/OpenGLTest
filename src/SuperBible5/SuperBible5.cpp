// SuperBible5.cpp : �������̨Ӧ�ó������ڵ㡣
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

