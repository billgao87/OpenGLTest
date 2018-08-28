#ifndef _GL_BATCHBASE_H_
#define _GL_BATCHBASE_H_

namespace gpu
{
	class GLBatchBase
	{
	public:
		virtual ~GLBatchBase()
		{
		}

		virtual void Draw() = 0;
	};

}	//!gpu

#endif	// _GL_BATCHBASE_H_