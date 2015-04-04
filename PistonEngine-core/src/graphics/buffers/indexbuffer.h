#pragma once

#include <GL/glew.h>

namespace PistonEngine { namespace graphics {

	class IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_Count;
	public:
		IndexBuffer(GLushort* data, GLsizei count);
		~IndexBuffer();
		inline GLuint getCount() const { return m_Count; };
		void bind() const;
		void unbind() const;

	};

} }