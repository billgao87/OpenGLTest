#pragma once
#include <string>
#include <Shlwapi.h> 

#pragma comment(lib,"shlwapi.lib")


namespace pathutil
{
	class PathUtil
	{
	public:
		static std::wstring string2wstring(std::string str)
		{
			std::wstring result;
			//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), nullptr, 0);
			TCHAR* buffer = new TCHAR[len + 1];
			//多字节编码转换成宽字节编码  
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
			buffer[len] = '\0';             //添加字符串结尾  
											//删除缓冲区并返回值  
			result.append(buffer);
			delete[] buffer;
			return result;
		}
		static std::string wstring2string(std::wstring wstr)
		{
			std::string result;
			//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
			int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
			char* buffer = new char[len + 1];
			//宽字节编码转换成多字节编码  
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, nullptr, nullptr);
			buffer[len] = '\0';
			//删除缓冲区并返回值  
			result.append(buffer);
			delete[] buffer;
			return result;
		}

		static std::wstring GetExeDirW()
		{
			wchar_t szExePath[MAX_PATH] = { 0 };
			::GetModuleFileNameW(nullptr, szExePath, sizeof(szExePath));
			::PathRemoveFileSpecW(szExePath);
			std::wstring result(szExePath);
			result.append(L"\\");
			return result;
		}

		static std::string GetExeDir()
		{
			return wstring2string(std::wstring(GetExeDirW()));
		}
	};


}


