//GLBatchBase.h

#ifndef _GL_BATCH_H_
#define _GL_BATCH_H_

#include <memory>

#include "vgl.h"
#include "GLBatchBase.h"
#include "GLShaderBase.h"
namespace gpu
{
	class GLBatch : public GLBatchBase
	{
	public:
		GLBatch();
		virtual ~GLBatch();

		void Begin(GLenum primitive, GLuint numVertexs, GLuint numTextureUnit = 0);

		void CopyVertexData3f(GLfloat* vertexs);
		void CopyVertexData2f(GLfloat* vertexs);

		void CopyNormalData3f(GLfloat* normalData);

		void CopyColorData4f(GLfloat* colorData);

		void CopyTexCoordData2f(GLfloat* texCoords, GLuint textureUnit);

		void End();

		virtual void Draw()
		{
			if (!_batchDone)
				return;

			glBindVertexArray(_vertexArrayObject);
			glDrawArrays(_primitiveType, 0, _numVertexs);
			glBindVertexArray(0);
		}

	private:

		void copy_data(GLuint& id, GLfloat* data, GLuint components);

		GLenum _primitiveType;			// What am I drawing....

		GLuint _vertexBufferID = 0;
		GLuint _normalBufferID = 0;
		GLuint _colorBufferID = 0;
		std::unique_ptr<GLuint[]> _textureCoordBufferIDs = nullptr;

		GLuint _vertexArrayObject = 0;

		GLuint _numVertexs = 0;				// Number of verticies in this batch
		GLuint _numTextureUnit = 0;			// Number of texture coordinate sets

		GLuint _componentsPerVertex = 3;
		GLuint _componentsPerColor = 4;
		GLuint _componentsPerNormal = 3;
		GLuint _componentsPerTexCoord = 2;

		bool _batchDone = false;		//batch has been built
	};
}


#endif	//_GL_BATCHBASE_H_