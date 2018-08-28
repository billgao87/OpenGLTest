#ifndef _GL_SHADERBASE_H_
#define _GL_SHADERBASE_H_

namespace gpu
{
	// Maximum length of shader name
#define MAX_SHADER_NAME_LENGTH	64

	//��ɫ�����ԣ����嶨��Ϊ0��colorΪ1��normal = 2...���16������
	enum GLT_SHADER_ATTRIBUTE
	{
		GLT_ATTRIBUTE_VERTEX = 0,
		GLT_ATTRIBUTE_COLOR,
		GLT_ATTRIBUTE_NORMAL,
		GLT_ATTRIBUTE_TEXTURE0,
		GLT_ATTRIBUTE_TEXTURE1,
		GLT_ATTRIBUTE_TEXTURE2,
		GLT_ATTRIBUTE_TEXTURE3,
		GLT_ATTRIBUTE_LAST
	};


	class GLShaderBase
	{
	public:
		GLShaderBase();
		~GLShaderBase();
	};

}	//!namespace gpu

#endif	//_GL_SHADERBASE_H_