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
			//��ȡ��������С��������ռ䣬��������С���ַ�����  
			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), nullptr, 0);
			TCHAR* buffer = new TCHAR[len + 1];
			//���ֽڱ���ת���ɿ��ֽڱ���  
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
			buffer[len] = '\0';             //����ַ�����β  
											//ɾ��������������ֵ  
			result.append(buffer);
			delete[] buffer;
			return result;
		}
		static std::string wstring2string(std::wstring wstr)
		{
			std::string result;
			//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
			int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
			char* buffer = new char[len + 1];
			//���ֽڱ���ת���ɶ��ֽڱ���  
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, nullptr, nullptr);
			buffer[len] = '\0';
			//ɾ��������������ֵ  
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


