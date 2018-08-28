#include "stdafx.h"
#include "GLBatch.h"

namespace gpu
{
	GLBatch::GLBatch()
	{
	}


	GLBatch::~GLBatch()
	{
		//删除坐标
		if (_vertexBufferID != 0)
			glDeleteBuffers(1, &_vertexBufferID);

		if (_normalBufferID != 0)
			glDeleteBuffers(1, &_normalBufferID);

		if (_colorBufferID != 0)
			glDeleteBuffers(1, &_colorBufferID);

		for (int i = 0;i<_numTextureUnit;++i)
		{
			if (_textureCoordBufferIDs&& _textureCoordBufferIDs[i] != 0)
			{
				glDeleteBuffers(1, &_textureCoordBufferIDs[i]);
			}
		}

		//删除vao
		if (_vertexArrayObject != 0)
			glDeleteVertexArrays(1, &_vertexArrayObject);
	}

	void GLBatch::Begin(GLenum primitive, GLuint numVertexs, GLuint numTextureUnit)
	{
		_primitiveType = primitive;
		_numVertexs = numVertexs;

		_numTextureUnit = numTextureUnit > 4 ? 4 : numTextureUnit; // Limit to four texture units	

		if (numTextureUnit != 0)
		{
			_textureCoordBufferIDs.reset(new GLuint[numTextureUnit]);

			for (int i = 0; i < _numTextureUnit; ++i)
			{
				_textureCoordBufferIDs[i] = 0;
			}
		}

		//绑定vao，准备填充数据
		glGenVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);
	}

	void GLBatch::CopyVertexData3f(GLfloat* vertexs)
	{
		_componentsPerVertex = 3;
		copy_data(_vertexBufferID, vertexs, _componentsPerVertex);
	}

	void GLBatch::CopyVertexData2f(GLfloat* vertexs)
	{
		_componentsPerVertex = 2;
		copy_data(_vertexBufferID, vertexs, _componentsPerVertex);
	}

	void GLBatch::CopyNormalData3f(GLfloat* normalData)
	{
		_componentsPerNormal = 3;
		copy_data(_normalBufferID, normalData, _componentsPerNormal);
	}

	void GLBatch::CopyColorData4f(GLfloat* colorData)
	{
		_componentsPerColor = 4;
		copy_data(_colorBufferID, colorData, _componentsPerColor);
	}

	void GLBatch::CopyTexCoordData2f(GLfloat* texCoords, GLuint textureUnit)
	{
		_componentsPerTexCoord = 2;
		copy_data(_textureCoordBufferIDs[textureUnit], texCoords, _componentsPerTexCoord);
	}

	void GLBatch::End()
	{
		glBindVertexArray(_vertexArrayObject);

		if (_vertexBufferID != 0)
		{
			glEnableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
			glVertexAttribPointer(GLT_ATTRIBUTE_VERTEX, _componentsPerVertex, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		}
		if (_colorBufferID != 0)
		{
			glEnableVertexAttribArray(GLT_ATTRIBUTE_COLOR);
			glBindBuffer(GL_ARRAY_BUFFER, _colorBufferID);
			glVertexAttribPointer(GLT_ATTRIBUTE_COLOR, _componentsPerColor, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		}
		if (_normalBufferID != 0)
		{
			glEnableVertexAttribArray(GLT_ATTRIBUTE_NORMAL);
			glBindBuffer(GL_ARRAY_BUFFER, _normalBufferID);
			glVertexAttribPointer(GLT_ATTRIBUTE_NORMAL, _componentsPerNormal, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		}

		for (int i = 0; i < _numTextureUnit; ++i)
		{
			if (_textureCoordBufferIDs[i] != 0)
			{
				glEnableVertexAttribArray(GLT_ATTRIBUTE_TEXTURE0 + i);
				glBindBuffer(GL_ARRAY_BUFFER, _textureCoordBufferIDs[i]);
				glVertexAttribPointer(GLT_ATTRIBUTE_TEXTURE0 + i, _componentsPerTexCoord, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			}
		}


		_batchDone = true;

		glBindVertexArray(0);
	}

	void GLBatch::copy_data(GLuint& id, GLfloat* data, GLuint components)
	{
		int size = sizeof(GLfloat) * components * _numVertexs;
		if (id == 0)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}
	}
}
